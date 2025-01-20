/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_all;
    QPushButton *btn_text;
    QPushButton *btn_image;
    QPushButton *btn_file;
    QTableView *clipboardHistoryTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(650, 500);
        MainWindow->setMinimumSize(QSize(650, 500));
        MainWindow->setMaximumSize(QSize(650, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(650, 500));
        centralwidget->setMaximumSize(QSize(650, 500));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btn_all = new QPushButton(centralwidget);
        btn_all->setObjectName("btn_all");
        btn_all->setMaximumSize(QSize(60, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/all_normal.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/res/all_selected.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_all->setIcon(icon1);
        btn_all->setIconSize(QSize(20, 20));
        btn_all->setCheckable(true);
        btn_all->setChecked(true);
        btn_all->setAutoExclusive(true);

        horizontalLayout_3->addWidget(btn_all);

        btn_text = new QPushButton(centralwidget);
        btn_text->setObjectName("btn_text");
        btn_text->setMaximumSize(QSize(60, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/text_normal.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/res/text_selected.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_text->setIcon(icon2);
        btn_text->setIconSize(QSize(20, 20));
        btn_text->setCheckable(true);
        btn_text->setAutoExclusive(true);

        horizontalLayout_3->addWidget(btn_text);

        btn_image = new QPushButton(centralwidget);
        btn_image->setObjectName("btn_image");
        btn_image->setMaximumSize(QSize(60, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/image_normal.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/res/image_selected.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_image->setIcon(icon3);
        btn_image->setIconSize(QSize(20, 20));
        btn_image->setCheckable(true);
        btn_image->setAutoExclusive(true);

        horizontalLayout_3->addWidget(btn_image);

        btn_file = new QPushButton(centralwidget);
        btn_file->setObjectName("btn_file");
        btn_file->setMaximumSize(QSize(60, 16777215));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/file_normal.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/res/file_selected.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_file->setIcon(icon4);
        btn_file->setIconSize(QSize(20, 20));
        btn_file->setCheckable(true);
        btn_file->setAutoExclusive(true);

        horizontalLayout_3->addWidget(btn_file);


        verticalLayout->addLayout(horizontalLayout_3);

        clipboardHistoryTable = new QTableView(centralwidget);
        clipboardHistoryTable->setObjectName("clipboardHistoryTable");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(clipboardHistoryTable->sizePolicy().hasHeightForWidth());
        clipboardHistoryTable->setSizePolicy(sizePolicy);
        clipboardHistoryTable->setMaximumSize(QSize(650, 500));
        clipboardHistoryTable->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        clipboardHistoryTable->setAutoFillBackground(true);
        clipboardHistoryTable->setStyleSheet(QString::fromUtf8("QTableView { background-color: #1e1e1e; color: #f0f0f0;font-size:13px;gridline-color: gray; }"));
        clipboardHistoryTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        clipboardHistoryTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        clipboardHistoryTable->setShowGrid(true);

        verticalLayout->addWidget(clipboardHistoryTable);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_all->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250", nullptr));
        btn_text->setText(QCoreApplication::translate("MainWindow", "\346\226\207\346\234\254", nullptr));
        btn_image->setText(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217", nullptr));
        btn_file->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        clipboardHistoryTable->setToolTip(QCoreApplication::translate("MainWindow", "\345\215\225\345\207\273\345\267\246\351\224\256\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
