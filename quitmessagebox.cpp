#include "quitmessagebox.h"

#include "ui_quitmessagebox.h"

QuitMessageBox::QuitMessageBox(QWidget* parent) : QDialog(parent), ui(new Ui::QuitMessageBox) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint);
}

QuitMessageBox::~QuitMessageBox() {
    delete ui;
}

void QuitMessageBox::on_btn_ok_clicked() {
    if (ui->radio_min_size->isChecked()) {

        emit minimized();  // 发出最小化信号
    } else if (ui->radio_quit->isChecked()) {
        // 退出程序
        emit quit();  // 发出退出信号
    }
    close();  // 关闭对话框
}
