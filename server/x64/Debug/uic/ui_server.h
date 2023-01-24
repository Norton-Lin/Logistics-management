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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverClass
{
public:
    QTextEdit *textEdit_receiver;
    QTextEdit *textEdit_send;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *serverClass)
    {
        if (serverClass->objectName().isEmpty())
            serverClass->setObjectName(QString::fromUtf8("serverClass"));
        serverClass->resize(600, 400);
        textEdit_receiver = new QTextEdit(serverClass);
        textEdit_receiver->setObjectName(QString::fromUtf8("textEdit_receiver"));
        textEdit_receiver->setGeometry(QRect(260, 120, 104, 87));
        textEdit_send = new QTextEdit(serverClass);
        textEdit_send->setObjectName(QString::fromUtf8("textEdit_send"));
        textEdit_send->setGeometry(QRect(250, 260, 104, 87));
        label = new QLabel(serverClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 150, 72, 20));
        pushButton = new QPushButton(serverClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 290, 93, 28));

        retranslateUi(serverClass);

        QMetaObject::connectSlotsByName(serverClass);
    } // setupUi

    void retranslateUi(QWidget *serverClass)
    {
        serverClass->setWindowTitle(QApplication::translate("serverClass", "server", nullptr));
        label->setText(QApplication::translate("serverClass", "\346\216\245\345\217\227", nullptr));
        pushButton->setText(QApplication::translate("serverClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serverClass: public Ui_serverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
