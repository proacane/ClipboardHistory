#include "logmanager.h"
#include"const.h"

LogManager::LogManager() {
    // 确保日志目录存在
    logDirectory = ConfigPath + "/log";
    QDir dir(logDirectory);
    if (!dir.exists()) {
        if(!dir.mkpath(logDirectory)){
            qCritical()<<"Log folder create failed";
        }
    }
    qDebug()<<"LogManager init succeed";
}

LogManager::~LogManager() {
    // 析构函数，不需要特殊操作
}

QString LogManager::getLogFileName(LogType type) {
    QString fileName;
    switch (type) {
        case LogType::Info: fileName = "info.log"; break;
        case LogType::Warning: fileName = "warning.log"; break;
        case LogType::Error: fileName = "error.log"; break;
    }
    return logDirectory + "/" + fileName;
}

void LogManager::writeLog(LogType type, const QString& message) {
    QMutexLocker locker(&mutex);  // 确保线程安全

    // 获取日志文件路径
    QString logFileName = getLogFileName(type);
    QFile file(logFileName);

    qDebug()<<logFileName;
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug()<<"Writing ..";
        QTextStream out(&file);

        // 写入时间戳和日志信息
        QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        out<<"[" << timeStamp << "] : " << message << "\n";

        file.close();
    }
}
