#include "databasehandler.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include "configmgr.h"
#include "logmanager.h"
DatabaseHandler::DatabaseHandler( QObject* parent) : QObject(parent) {
    QString configPath = ConfigMgr::getInstance().value(ConfigGroup::DataPath,"path");

     QString dbPath = configPath + "/clipboard_history.db";

    qDebug()<<"Database path: " <<dbPath;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    } else {
        createTable();
    }
}

void DatabaseHandler::createTable() {
    QSqlQuery query;
    QString createTableQuery = R"(
            CREATE TABLE IF NOT EXISTS clipboard_history (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                type TEXT,
                content TEXT UNIQUE ,
                timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
            )
        )";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        LogManager::getInstance().writeLog(LogManager::LogType::Error,
                                           "Failed to create table: " + query.lastError().text());
    }
}

void DatabaseHandler::insertRecord(Type type, const QString& content) {
    QSqlQuery query;
    query.prepare("INSERT INTO clipboard_history (type, content) VALUES (:type, :content)");
    query.bindValue(":type", type);
    query.bindValue(":content", content);
    if (!query.exec()) {
        if (query.lastError().nativeErrorCode() == "19") {  // 错误代码 19 表示违反唯一约束
            qDebug() << "Duplicate content detected. Record not inserted.";
        } else {
            qDebug() << "Failed to insert record:" << query.lastError().text();
            LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                               "Failed to insert record: " + query.lastError().text());
        }
    }
    // 创建一个后台线程执行数据库清理
    QThread* thread = new QThread;
    CleanUpWorker* worker = new CleanUpWorker("clipboard_history.db");
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &CleanUpWorker::cleanDatabase);
    connect(worker, &CleanUpWorker::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}

QSqlQuery DatabaseHandler::getHistory() {
    QSqlQuery query;
    query.prepare("SELECT type,content FROM clipboard_history ORDER BY timestamp DESC LIMIT :total");
    query.bindValue(":total", ConfigMgr::getInstance().value(ConfigGroup::RecordCount, "totalCount").toInt());

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
    }

    return query;
}

QSqlQuery DatabaseHandler::getHistory(Type type) {
    QSqlQuery query;
    query.prepare("SELECT type,content FROM clipboard_history WHERE type = :type ORDER BY timestamp DESC LIMIT :total");
    query.bindValue(":type", type);
    query.bindValue(":total", ConfigMgr::getInstance().value(ConfigGroup::RecordCount, "totalCount").toInt());

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
    }

    return query;
}

bool DatabaseHandler::clearHistory(const QRect& mainWindowGeometry) {
    QMessageBox msg_box;
    msg_box.setWindowTitle("提示");
    msg_box.setText("确定清除历史记录吗？");
    msg_box.setIcon(QMessageBox::Question);
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.resize(150, 50);
    int x = mainWindowGeometry.x() + (mainWindowGeometry.width() - msg_box.width()) / 2;
    int y = mainWindowGeometry.y() + (mainWindowGeometry.height() - msg_box.height()) / 2;
    msg_box.move(x, y);
    // 显示消息框并获取用户的选择
    int ret = msg_box.exec();

    if (ret == QMessageBox::Yes) {
        // 用户选择了“是”，执行清除历史记录的逻辑
        QSqlQuery delete_all("DELETE FROM clipboard_history");
        delete_all.exec();
        // 清除图片目录
        QDir dir(ConfigPath + "/images");

        // 检查目录是否存在
        if (!dir.exists()) {
            qWarning() << "Directory does not exist:" << dir;
        }

        // 获取目录下的所有图片
        QFileInfoList imageList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

        // 遍历图片列表并删除图片
        for (const QFileInfo& imageInfo : imageList) {
            if (!QFile::remove(imageInfo.absoluteFilePath())) {
                qWarning() << "Failed to remove file:" << imageInfo.absoluteFilePath();
            } else {
                qDebug() << "Removed file:" << imageInfo.absoluteFilePath();
            }
        }
        // 刷新界面
        return true;
    } else {
        // 用户选择了“否”或关闭了对话框
        return false;
    }
}

int DatabaseHandler::getImageRecordCount() {
    QSqlQuery query("SELECT COUNT(content) FROM clipboard_history WHERE type = 2");
    int rowCount = 0;
    if (query.exec() && query.next()) {
        rowCount = query.value(0).toInt();
        qDebug() << "Image count:" << rowCount;
        return rowCount;
    } else {
        qDebug() << "Query failed:" << query.lastError();
        LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                           "Failed to query record: " + query.lastError().text());
    }
    return -1;
}

QStringList DatabaseHandler::getOldestImagePaths(int limit) {
    QStringList imagePaths;

    // 查询最旧的图片记录
    QSqlQuery query;
    query.prepare("SELECT content FROM clipboard_history WHERE type = :type ORDER BY timestamp ASC LIMIT :limit");
    query.bindValue(":type", Type::_IMAGE);  // 假设 type 为 2 表示图片
    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            QString imagePath = query.value(0).toString();
            imagePaths.append(imagePath);
        }
    } else {
        qDebug() << "Failed to get oldest image paths:" << query.lastError();
        LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                           "Failed to query record: " + query.lastError().text());
    }

    return imagePaths;
}

void DatabaseHandler::deleteRecord(const QString& content) {
    QSqlQuery query;
    query.prepare("DELETE FROM clipboard_history WHERE content = :content");
    query.bindValue(":content", content);

    if (!query.exec()) {
        qDebug() << "Failed to delete record:" << query.lastError();
        LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                           "Failed to delete record: " + query.lastError().text());
    } else {
        qDebug() << "Record deleted for content:" << content;
    }
}

void CleanUpWorker::cleanDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "cleaner");
    db.setDatabaseName(dbName);  // 这里设置数据库文件路径
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError();
        emit finished();
        return;
    }

    QSqlQuery query(db);  // 使用新打开的数据库连接
    query.prepare("SELECT COUNT(*) FROM clipboard_history");

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to count records: " << query.lastError();
        LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                           "Failed to count records:" + query.lastError().text());
        emit finished();  // 操作完成，发出信号
        return;
    }

    int totalRows = query.value(0).toInt();
    int recordLimit = ConfigMgr::getInstance().value(ConfigGroup::RecordCount, "totalCount").toInt();

    while (totalRows > recordLimit) {
        // 删除最早的一条数据
        query.prepare("DELETE FROM clipboard_history WHERE timestamp = (SELECT MIN(timestamp) FROM clipboard_history)");
        if (!query.exec()) {
            qDebug() << "Failed to delete oldest record: " << query.lastError();
            LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                               "Failed to delete oldest record:" + query.lastError().text());
        } else {
            qDebug() << "Oldest record deleted to maintain record limit.";
            LogManager::getInstance().writeLog(LogManager::LogType::Warning,
                                               "Oldest record deleted to maintain record limit.");
        }
        totalRows--;
    }

    db.close();  // 清理数据库连接
    QSqlDatabase::removeDatabase("clean");
    emit finished();  // 操作完成，发出信号
}
