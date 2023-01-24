/********************************************************************************
** Form generated from reading UI file 'CourierRegister.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURIERREGISTER_H
#define UI_COURIERREGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourierRegister
{
public:

    void setupUi(QWidget *CourierRegister)
    {
        if (CourierRegister->objectName().isEmpty())
            CourierRegister->setObjectName(QString::fromUtf8("CourierRegister"));
        CourierRegister->resize(400, 300);

        retranslateUi(CourierRegister);

        QMetaObject::connectSlotsByName(CourierRegister);
    } // setupUi

    void retranslateUi(QWidget *CourierRegister)
    {
        CourierRegister->setWindowTitle(QApplication::translate("CourierRegister", "CourierRegister", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourierRegister: public Ui_CourierRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERREGISTER_H
