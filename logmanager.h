#ifndef LOGMANAGER_H
#define LOGMANAGER_H
/*****************************************************************************
 * @file         logmanager.h
 * @brief
 * @description  日志管理类
 * @author       ACA
 * @date         2024/09/19
 * @history
 *****************************************************************************/
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QTextStream>

class LogManager {
  public:
    enum class LogType { Info, Warning, Error };

    // 获取单例实例
    static LogManager& getInstance() {
        static LogManager instance;
        return instance;
    }

    // 禁用拷贝构造函数和赋值运算符
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;
    // 写入日志
    void writeLog(LogType type, const QString& message);

  private:
    // 构造函数为私有，用于创建log文件夹
    LogManager();
    ~LogManager();
    // 返回日志文件名，基于日志类型
    QString getLogFileName(LogType type);

    // 用于同步写入日志的互斥锁
    QMutex mutex;
    QString logDirectory;  // 日志文件夹路径
};

#endif  // LOGMANAGER_H
