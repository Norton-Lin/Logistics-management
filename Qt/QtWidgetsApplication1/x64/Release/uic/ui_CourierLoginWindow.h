/********************************************************************************
** Form generated from reading UI file 'CourierLoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURIERLOGINWINDOW_H
#define UI_COURIERLOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourierLoginWindow
{
public:
    QLabel *label;
    QPushButton *login;
    QPushButton *back;
    QWidget *widget;
    QLineEdit *password;
    QLineEdit *username;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *CourierLoginWindow)
    {
        if (CourierLoginWindow->objectName().isEmpty())
            CourierLoginWindow->setObjectName(QString::fromUtf8("CourierLoginWindow"));
        CourierLoginWindow->resize(600, 500);
        label = new QLabel(CourierLoginWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 60, 151, 71));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        login = new QPushButton(CourierLoginWindow);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(260, 330, 93, 28));
        login->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));
        back = new QPushButton(CourierLoginWindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(260, 390, 93, 28));
        back->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:#34495e;"));
        widget = new QWidget(CourierLoginWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(110, 160, 341, 141));
        password = new QLineEdit(widget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(100, 90, 221, 31));
        password->setMaxLength(16);
        password->setEchoMode(QLineEdit::Password);
        username = new QLineEdit(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(100, 30, 221, 31));
        username->setMaxLength(16);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 30, 71, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 61, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));

        retranslateUi(CourierLoginWindow);

        QMetaObject::connectSlotsByName(CourierLoginWindow);
    } // setupUi

    void retranslateUi(QWidget *CourierLoginWindow)
    {
        CourierLoginWindow->setWindowTitle(QApplication::translate("CourierLoginWindow", "CourierLoginWindow", nullptr));
        label->setText(QApplication::translate("CourierLoginWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        login->setText(QApplication::translate("CourierLoginWindow", "\347\231\273\345\275\225", nullptr));
        back->setText(QApplication::translate("CourierLoginWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
        label_2->setText(QApplication::translate("CourierLoginWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_3->setText(QApplication::translate("CourierLoginWindow", "\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourierLoginWindow: public Ui_CourierLoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERLOGINWINDOW_H
