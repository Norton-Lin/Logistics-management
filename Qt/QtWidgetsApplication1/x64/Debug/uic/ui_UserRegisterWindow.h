/********************************************************************************
** Form generated from reading UI file 'UserRegisterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERREGISTERWINDOW_H
#define UI_USERREGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserRegisterWindow
{
public:
    QLabel *label;
    QWidget *widget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *tip1;
    QLabel *tip2;
    QLabel *tip3;
    QLabel *tip4;
    QLabel *tip5;
    QLabel *tip6;
    QLineEdit *username;
    QLineEdit *password;
    QLineEdit *confirmPassword;
    QLineEdit *name;
    QLineEdit *number;
    QLineEdit *address;
    QPushButton *confirm;
    QPushButton *back;

    void setupUi(QWidget *UserRegisterWindow)
    {
        if (UserRegisterWindow->objectName().isEmpty())
            UserRegisterWindow->setObjectName(QString::fromUtf8("UserRegisterWindow"));
        UserRegisterWindow->resize(845, 601);
        label = new QLabel(UserRegisterWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(340, 50, 161, 81));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\346\245\267\344\275\223\";"));
        widget = new QWidget(UserRegisterWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(170, 120, 531, 321));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 30, 72, 15));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 80, 72, 15));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 130, 72, 15));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 180, 72, 15));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 230, 72, 15));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 290, 72, 15));
        tip1 = new QLabel(widget);
        tip1->setObjectName(QString::fromUtf8("tip1"));
        tip1->setGeometry(QRect(401, 35, 131, 21));
        tip1->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"color:rgb(255, 0, 0)"));
        tip2 = new QLabel(widget);
        tip2->setObjectName(QString::fromUtf8("tip2"));
        tip2->setGeometry(QRect(400, 91, 131, 21));
        tip2->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"color:rgb(255, 0, 0)"));
        tip3 = new QLabel(widget);
        tip3->setObjectName(QString::fromUtf8("tip3"));
        tip3->setGeometry(QRect(400, 140, 131, 21));
        tip3->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"color:rgb(255, 0, 0)"));
        tip4 = new QLabel(widget);
        tip4->setObjectName(QString::fromUtf8("tip4"));
        tip4->setGeometry(QRect(400, 191, 131, 20));
        tip4->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"color:rgb(255, 0, 0)"));
        tip5 = new QLabel(widget);
        tip5->setObjectName(QString::fromUtf8("tip5"));
        tip5->setGeometry(QRect(400, 240, 131, 21));
        tip5->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"color:rgb(255, 0, 0)"));
        tip6 = new QLabel(widget);
        tip6->setObjectName(QString::fromUtf8("tip6"));
        tip6->setGeometry(QRect(400, 285, 131, 21));
        tip6->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"color:rgb(255, 0, 0)"));
        username = new QLineEdit(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(170, 30, 161, 31));
        password = new QLineEdit(widget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(170, 80, 161, 31));
        confirmPassword = new QLineEdit(widget);
        confirmPassword->setObjectName(QString::fromUtf8("confirmPassword"));
        confirmPassword->setGeometry(QRect(170, 130, 161, 31));
        name = new QLineEdit(widget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(170, 180, 161, 31));
        number = new QLineEdit(widget);
        number->setObjectName(QString::fromUtf8("number"));
        number->setGeometry(QRect(170, 230, 161, 31));
        address = new QLineEdit(widget);
        address->setObjectName(QString::fromUtf8("address"));
        address->setGeometry(QRect(170, 280, 161, 31));
        confirm = new QPushButton(UserRegisterWindow);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setGeometry(QRect(360, 480, 93, 28));
        confirm->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));
        back = new QPushButton(UserRegisterWindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(360, 540, 93, 28));
        back->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));

        retranslateUi(UserRegisterWindow);

        QMetaObject::connectSlotsByName(UserRegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *UserRegisterWindow)
    {
        UserRegisterWindow->setWindowTitle(QApplication::translate("UserRegisterWindow", "\347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
        label->setText(QApplication::translate("UserRegisterWindow", "\347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
        label_2->setText(QApplication::translate("UserRegisterWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_3->setText(QApplication::translate("UserRegisterWindow", "\345\257\206\347\240\201", nullptr));
        label_4->setText(QApplication::translate("UserRegisterWindow", "\350\257\267\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_5->setText(QApplication::translate("UserRegisterWindow", "\345\247\223\345\220\215", nullptr));
        label_6->setText(QApplication::translate("UserRegisterWindow", "\347\224\265\350\257\235\345\217\267\347\240\201", nullptr));
        label_7->setText(QApplication::translate("UserRegisterWindow", "\345\234\260\345\235\200", nullptr));
        tip1->setText(QString());
        tip2->setText(QString());
        tip3->setText(QString());
        tip4->setText(QString());
        tip5->setText(QString());
        tip6->setText(QString());
        confirm->setText(QApplication::translate("UserRegisterWindow", "\346\263\250\345\206\214", nullptr));
        back->setText(QApplication::translate("UserRegisterWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserRegisterWindow: public Ui_UserRegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERREGISTERWINDOW_H
