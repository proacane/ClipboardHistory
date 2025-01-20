#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H
/*****************************************************************************
 * @file         databasehandler.h
 * @brief
 * @description  创建、查询、插入剪切板记录
 * @author       ACA
 * @date         2024/09/17
 * @history
 *****************************************************************************/
#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "const.h"
class DatabaseHandler : public QObject {
    Q_OBJECT
  public:
    DatabaseHandler( QObject* parent = nullptr);

    void createTable();

    void insertRecord(Type type, const QString& content);

    QSqlQuery getHistory();
    QSqlQuery getHistory(Type type);
    bool clearHistory(const QRect& mainWindowGeometry);
    // 获取存储的图片数量
    int getImageRecordCount();
    /**
     * @brief getOldestImagePaths 获取指定存储的图片的指定条数
     * @param limit 记录条数
     * @return
     */
    QStringList getOldestImagePaths(int limit);
    void deleteRecord(const QString& content);

  private:
    QSqlDatabase db;
};

class CleanUpWorker : public QObject {
    Q_OBJECT
  public:
    explicit CleanUpWorker(const QString& dbName, QObject* parent = nullptr) : QObject(parent), dbName(dbName) {}

  public slots:
    void cleanDatabase();

  signals:
    void finished();

  private:
    QString dbName;  // 用于存储数据库名称
};

#endif  // DATABASEHANDLER_H
