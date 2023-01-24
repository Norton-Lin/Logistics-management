/********************************************************************************
** Form generated from reading UI file 'CourierRegisterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURIERREGISTERWINDOW_H
#define UI_COURIERREGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourierRegisterWindow
{
public:
    QPushButton *confirm;
    QWidget *widget;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *tip1;
    QLabel *tip2;
    QLabel *tip3;
    QLabel *tip4;
    QLabel *tip5;
    QLineEdit *username;
    QLineEdit *password;
    QLineEdit *confirmPassword;
    QLineEdit *name;
    QLineEdit *number;
    QPushButton *back;
    QLabel *label;

    void setupUi(QWidget *CourierRegisterWindow)
    {
        if (CourierRegisterWindow->objectName().isEmpty())
            CourierRegisterWindow->setObjectName(QString::fromUtf8("CourierRegisterWindow"));
        CourierRegisterWindow->resize(736, 618);
        confirm = new QPushButton(CourierRegisterWindow);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setGeometry(QRect(300, 480, 93, 28));
        confirm->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));
        widget = new QWidget(CourierRegisterWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(110, 120, 531, 321));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 30, 72, 15));
        label_15 = new QLabel(widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 80, 72, 15));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 130, 72, 15));
        label_17 = new QLabel(widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 180, 72, 15));
        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 230, 72, 15));
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
        back = new QPushButton(CourierRegisterWindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(300, 540, 93, 28));
        back->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));
        label = new QLabel(CourierRegisterWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 50, 161, 81));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\346\245\267\344\275\223\";"));

        retranslateUi(CourierRegisterWindow);

        QMetaObject::connectSlotsByName(CourierRegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *CourierRegisterWindow)
    {
        CourierRegisterWindow->setWindowTitle(QApplication::translate("CourierRegisterWindow", "\345\277\253\351\200\222\345\221\230\346\263\250\345\206\214", nullptr));
        confirm->setText(QApplication::translate("CourierRegisterWindow", "\346\263\250\345\206\214", nullptr));
        label_14->setText(QApplication::translate("CourierRegisterWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_15->setText(QApplication::translate("CourierRegisterWindow", "\345\257\206\347\240\201", nullptr));
        label_16->setText(QApplication::translate("CourierRegisterWindow", "\350\257\267\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_17->setText(QApplication::translate("CourierRegisterWindow", "\345\247\223\345\220\215", nullptr));
        label_18->setText(QApplication::translate("CourierRegisterWindow", "\347\224\265\350\257\235\345\217\267\347\240\201", nullptr));
        tip1->setText(QString());
        tip2->setText(QString());
        tip3->setText(QString());
        tip4->setText(QString());
        tip5->setText(QString());
        back->setText(QApplication::translate("CourierRegisterWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
        label->setText(QApplication::translate("CourierRegisterWindow", "\347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourierRegisterWindow: public Ui_CourierRegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERREGISTERWINDOW_H
