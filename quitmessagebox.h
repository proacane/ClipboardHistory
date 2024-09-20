#ifndef QUITMESSAGEBOX_H
#define QUITMESSAGEBOX_H

#include <QDialog>

namespace Ui {
    class QuitMessageBox;
}

class QuitMessageBox : public QDialog {
    Q_OBJECT

  public:
    explicit QuitMessageBox(QWidget* parent = nullptr);
    ~QuitMessageBox();

  private slots:
    void on_btn_ok_clicked();

  private:
    Ui::QuitMessageBox* ui;
  signals:
    void minimized();
    void quit();
};

#endif  // QUITMESSAGEBOX_H
