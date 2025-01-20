/********************************************************************************
** Form generated from reading UI file 'quitmessagebox.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUITMESSAGEBOX_H
#define UI_QUITMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QuitMessageBox
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radio_min_size;
    QRadioButton *radio_quit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_ok;

    void setupUi(QDialog *QuitMessageBox)
    {
        if (QuitMessageBox->objectName().isEmpty())
            QuitMessageBox->setObjectName("QuitMessageBox");
        QuitMessageBox->resize(200, 100);
        QuitMessageBox->setMinimumSize(QSize(200, 100));
        QuitMessageBox->setMaximumSize(QSize(200, 100));
        verticalLayout = new QVBoxLayout(QuitMessageBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radio_min_size = new QRadioButton(QuitMessageBox);
        radio_min_size->setObjectName("radio_min_size");
        radio_min_size->setChecked(true);

        horizontalLayout_2->addWidget(radio_min_size);

        radio_quit = new QRadioButton(QuitMessageBox);
        radio_quit->setObjectName("radio_quit");

        horizontalLayout_2->addWidget(radio_quit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_ok = new QPushButton(QuitMessageBox);
        btn_ok->setObjectName("btn_ok");

        horizontalLayout->addWidget(btn_ok);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QuitMessageBox);

        QMetaObject::connectSlotsByName(QuitMessageBox);
    } // setupUi

    void retranslateUi(QDialog *QuitMessageBox)
    {
        QuitMessageBox->setWindowTitle(QCoreApplication::translate("QuitMessageBox", "\351\200\200\345\207\272", nullptr));
        radio_min_size->setText(QCoreApplication::translate("QuitMessageBox", "\346\234\200\345\260\217\345\214\226", nullptr));
        radio_quit->setText(QCoreApplication::translate("QuitMessageBox", "\351\200\200\345\207\272\350\275\257\344\273\266", nullptr));
        btn_ok->setText(QCoreApplication::translate("QuitMessageBox", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuitMessageBox: public Ui_QuitMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUITMESSAGEBOX_H
