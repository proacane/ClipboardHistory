/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QKeySequenceEdit *short_open;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QCheckBox *chk_auto_run;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *image_count;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpinBox *total_count;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(400, 300);
        horizontalLayout_2 = new QHBoxLayout(SettingDialog);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        scrollArea = new QScrollArea(SettingDialog);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 280));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        short_open = new QKeySequenceEdit(scrollAreaWidgetContents);
        short_open->setObjectName("short_open");

        horizontalLayout->addWidget(short_open);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        chk_auto_run = new QCheckBox(scrollAreaWidgetContents);
        chk_auto_run->setObjectName("chk_auto_run");

        horizontalLayout_3->addWidget(chk_auto_run);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        image_count = new QSpinBox(scrollAreaWidgetContents);
        image_count->setObjectName("image_count");
        image_count->setMinimum(10);
        image_count->setMaximum(100);
        image_count->setValue(10);

        horizontalLayout_4->addWidget(image_count);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName("label_4");

        horizontalLayout_5->addWidget(label_4);

        total_count = new QSpinBox(scrollAreaWidgetContents);
        total_count->setObjectName("total_count");
        total_count->setMinimum(50);
        total_count->setMaximum(500);

        horizontalLayout_5->addWidget(total_count);


        verticalLayout->addLayout(horizontalLayout_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);


        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "\346\211\223\345\274\200\350\275\257\344\273\266", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "\346\230\257\345\220\246\345\274\200\346\234\272\345\220\257\345\212\250", nullptr));
        chk_auto_run->setText(QString());
        label_3->setText(QCoreApplication::translate("SettingDialog", "\345\233\276\347\211\207\346\234\200\345\244\247\347\274\223\345\255\230\346\225\260", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "\346\234\200\345\244\232\346\230\276\347\244\272\350\256\260\345\275\225\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
