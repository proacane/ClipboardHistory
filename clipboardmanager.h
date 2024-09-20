#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H
/*****************************************************************************
 * @file         clipboardmanager.h
 * @brief
 * @description  监听剪切板内容变化并存储数据
 * @author       ACA
 * @date         2024/09/17
 * @history
 *****************************************************************************/
#include <QApplication>
#include <QClipboard>

#include "databaseHandler.h"

class ClipboardManager : public QObject {
    Q_OBJECT
  public:
    ClipboardManager(QClipboard* clipboard, DatabaseHandler* dbHandler, QObject* parent = nullptr);
      // 加载剪切板历史记录
      void loadClipboardHistory();
    void setContext(Type t,const QString& content);
  private slots:
      void onClipboardDataChanged();
  private:
    QString saveImageToFile(const QImage& image);
      // 是否为从界面点击复制的内容
      bool _suppress_dataChangedSignal;
    QClipboard* m_clipboard;
    DatabaseHandler* m_dbHandler;
    // 保存当前剪切板内容到数据库
    void saveCurrentClipboardContent();
    void cleanupOldImages();
signals:
    void clipboardHistoryUpdated();
};

#endif  // CLIPBOARDMANAGER_H
