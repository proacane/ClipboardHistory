#include "databasehandler.h"

#include <QCoreApplication>
#include <QMessageBox>

#include "configmgr.h"
#include "logmanager.h"
DatabaseHandler::DatabaseHandler(const QString& dbPath, QObject* parent) : QObject(parent) {
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
}

QSqlQuery DatabaseHandler::getHistory() {
    QSqlQuery query;
    query.prepare("SELECT * FROM clipboard_history ORDER BY timestamp DESC LIMIT :total");
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
        QDir dir(QCoreApplication::applicationDirPath()+"/images");

        // 检查目录是否存在
        if (!dir.exists()) {
            qWarning() << "Directory does not exist:" << dir;
        }

        // 获取目录下的所有文件
        QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

        // 遍历文件列表并删除文件
        for (const QFileInfo& fileInfo : fileList) {
            if (!QFile::remove(fileInfo.absoluteFilePath())) {
                qWarning() << "Failed to remove file:" << fileInfo.absoluteFilePath();
            } else {
                qDebug() << "Removed file:" << fileInfo.absoluteFilePath();
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
    QSqlQuery query("SELECT COUNT(*) FROM clipboard_history WHERE type = 2");
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
