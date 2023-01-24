/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverClass
{
public:

    void setupUi(QWidget *serverClass)
    {
        if (serverClass->objectName().isEmpty())
            serverClass->setObjectName(QString::fromUtf8("serverClass"));
        serverClass->resize(600, 400);

        retranslateUi(serverClass);

        QMetaObject::connectSlotsByName(serverClass);
    } // setupUi

    void retranslateUi(QWidget *serverClass)
    {
        serverClass->setWindowTitle(QApplication::translate("serverClass", "server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serverClass: public Ui_serverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
