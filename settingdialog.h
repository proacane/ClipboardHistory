#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QShortcut>
namespace Ui {
    class SettingDialog;
}

class SettingDialog : public QDialog {
    Q_OBJECT

  public:
    explicit SettingDialog(QWidget* parent = nullptr);
    ~SettingDialog();

  private slots:
    void on_short_open_editingFinished();

    void on_chk_auto_run_stateChanged(int arg1);

    void on_image_count_valueChanged(int arg1);

    void on_total_count_valueChanged(int arg1);

  private:
    Ui::SettingDialog* ui;
  signals:
    // 更新快捷键信息
    void updateShortCutInfo();
    // 是否开机自启
    void autoRun(bool flag);
    // 限制总条数
    void limitTotal();
};

#endif  // SETTINGDIALOG_H
