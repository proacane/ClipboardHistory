#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    QApplication::setStyle("Fusion");  // 或者其他可用的样式
    MainWindow w;
    w.show();
    return a.exec();
}
