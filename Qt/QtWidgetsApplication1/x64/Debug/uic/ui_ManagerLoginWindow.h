/********************************************************************************
** Form generated from reading UI file 'ManagerLoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGERLOGINWINDOW_H
#define UI_MANAGERLOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManagerLoginWindow
{
public:
    QWidget *widget;
    QLineEdit *password;
    QLineEdit *username;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *login;
    QLabel *label;
    QPushButton *back;

    void setupUi(QWidget *ManagerLoginWindow)
    {
        if (ManagerLoginWindow->objectName().isEmpty())
            ManagerLoginWindow->setObjectName(QString::fromUtf8("ManagerLoginWindow"));
        ManagerLoginWindow->resize(600, 500);
        widget = new QWidget(ManagerLoginWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(120, 140, 341, 141));
        password = new QLineEdit(widget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(100, 90, 221, 31));
        password->setMaxLength(16);
        password->setEchoMode(QLineEdit::Password);
        username = new QLineEdit(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(100, 30, 221, 31));
        username->setMaxLength(16);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 30, 71, 31));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 90, 61, 31));
        label_7->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        login = new QPushButton(ManagerLoginWindow);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(250, 320, 93, 28));
        login->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));
        label = new QLabel(ManagerLoginWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 50, 151, 71));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        back = new QPushButton(ManagerLoginWindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(250, 380, 93, 28));
        back->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));

        retranslateUi(ManagerLoginWindow);

        QMetaObject::connectSlotsByName(ManagerLoginWindow);
    } // setupUi

    void retranslateUi(QWidget *ManagerLoginWindow)
    {
        ManagerLoginWindow->setWindowTitle(QApplication::translate("ManagerLoginWindow", "\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225", nullptr));
        label_6->setText(QApplication::translate("ManagerLoginWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_7->setText(QApplication::translate("ManagerLoginWindow", "\345\257\206\347\240\201", nullptr));
        login->setText(QApplication::translate("ManagerLoginWindow", "\347\231\273\345\275\225", nullptr));
        label->setText(QApplication::translate("ManagerLoginWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        back->setText(QApplication::translate("ManagerLoginWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManagerLoginWindow: public Ui_ManagerLoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGERLOGINWINDOW_H
