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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourierRegisterWindow
{
public:

    void setupUi(QWidget *CourierRegisterWindow)
    {
        if (CourierRegisterWindow->objectName().isEmpty())
            CourierRegisterWindow->setObjectName(QString::fromUtf8("CourierRegisterWindow"));
        CourierRegisterWindow->resize(400, 300);

        retranslateUi(CourierRegisterWindow);

        QMetaObject::connectSlotsByName(CourierRegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *CourierRegisterWindow)
    {
        CourierRegisterWindow->setWindowTitle(QApplication::translate("CourierRegisterWindow", "CourierRegisterWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourierRegisterWindow: public Ui_CourierRegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERREGISTERWINDOW_H
