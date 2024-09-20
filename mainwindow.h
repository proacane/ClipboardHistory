#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QSqlQueryModel>
#include <QSystemTrayIcon>
#include <QTableView>
#include <QHotkey>
#include "ClipboardManager.h"
#include "databaseHandler.h"
#include "settingdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow* ui;
  private slots:
    void updateClipboardHistoryUI( );
    void updateShortCut();
    void clipboardHistoryTableClicked(const QModelIndex &index);
    void clearHistory();
    void setProcessAutoRun(bool flag);


    void on_btn_all_toggled(bool checked);

    void on_btn_text_toggled(bool checked);

    void on_btn_image_toggled(bool checked);

    void on_btn_file_toggled(bool checked);

private:
    DatabaseHandler* dbHandler;
    ClipboardManager* clipboardManager;
    QSqlQueryModel* model;
    // 托管图标
    QSystemTrayIcon* systemIcon;
    SettingDialog* _settings_dialog;
    QHotkey *_open_shortcut;
    bool _is_open;
    Type _cur_type;
    // QWidget interface
  protected:
    virtual void closeEvent(QCloseEvent* event) override;


    // QWidget interface
protected:
    virtual void changeEvent(QEvent *) override;


};
#endif  // MAINWINDOW_H
