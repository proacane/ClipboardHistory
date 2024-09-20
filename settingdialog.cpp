#include "settingdialog.h"

#include <QKeyEvent>
#include <QMap>
#include <QSettings>

#include "configmgr.h"
#include "ui_settingdialog.h"
SettingDialog::SettingDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SettingDialog) {
    ui->setupUi(this);
    QString openShort = ConfigMgr::getInstance().value(ConfigGroup::Shortcuts, "open");
    ui->short_open->setKeySequence(openShort);
    QString is_auto_run = ConfigMgr::getInstance().value(ConfigGroup::AutoRun, "flag");
    if (is_auto_run == "true") {
        ui->chk_auto_run->setChecked(true);
    } else {
        ui->chk_auto_run->setChecked(false);
    }
    setModal(true);
    QString image_count = ConfigMgr::getInstance().value(ConfigGroup::RecordCount, "imageCount");
    bool ok;
    ui->image_count->setValue(image_count.toInt(&ok));
    if (!ok) {
        qDebug() << "Failed to parse QString to int when reading image count: " << image_count;
    }
    QString total_count = ConfigMgr::getInstance().value(ConfigGroup::RecordCount, "totalCount");
    ui->total_count->setValue(total_count.toInt(&ok));
    if (!ok) {
        qDebug() << "Failed to parse QString to int when reading total count: " << image_count;
    }
}

SettingDialog::~SettingDialog() {
    delete ui;
}

void SettingDialog::on_short_open_editingFinished() {
    auto newOpenShort = ui->short_open->keySequence();
    ConfigMgr::getInstance().setValue(ConfigGroup::Shortcuts, "open", newOpenShort.toString());
    emit updateShortCutInfo();
}

void SettingDialog::on_chk_auto_run_stateChanged(int flag) {
    if (flag) {
        // 选中就自启
        qDebug() << "Auto run";
        ConfigMgr::getInstance().setValue(ConfigGroup::AutoRun, "flag", "true");
    } else {
        qDebug() << "Remove auto run";
        ConfigMgr::getInstance().setValue(ConfigGroup::AutoRun, "flag", "false");
    }
    emit autoRun(flag);
}

void SettingDialog::on_image_count_valueChanged(int value) {
    qDebug() << "Set image count to " << value;
    ConfigMgr::getInstance().setValue(ConfigGroup::RecordCount, "imageCount", QString::number(value));
}

void SettingDialog::on_total_count_valueChanged(int value) {
    qDebug() << "Set total count to " << value;
    ConfigMgr::getInstance().setValue(ConfigGroup::RecordCount, "totalCount", QString::number(value));
    emit limitTotal();
}
