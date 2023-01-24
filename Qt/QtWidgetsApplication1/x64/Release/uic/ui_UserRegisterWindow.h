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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserRegisterWindow
{
public:

    void setupUi(QWidget *UserRegisterWindow)
    {
        if (UserRegisterWindow->objectName().isEmpty())
            UserRegisterWindow->setObjectName(QString::fromUtf8("UserRegisterWindow"));
        UserRegisterWindow->resize(400, 300);

        retranslateUi(UserRegisterWindow);

        QMetaObject::connectSlotsByName(UserRegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *UserRegisterWindow)
    {
        UserRegisterWindow->setWindowTitle(QApplication::translate("UserRegisterWindow", "UserRegisterWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserRegisterWindow: public Ui_UserRegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERREGISTERWINDOW_H
