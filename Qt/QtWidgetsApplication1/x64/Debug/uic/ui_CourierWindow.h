/********************************************************************************
** Form generated from reading UI file 'CourierWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURIERWINDOW_H
#define UI_COURIERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourierWindow
{
public:
    QWidget *widget;
    QLabel *label_3;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *username;
    QPushButton *search;
    QPushButton *collect;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QPushButton *changeMessage;
    QTreeWidget *treeWidget;
    QWidget *widget_2;
    QLabel *label_2;
    QSpinBox *year;
    QLabel *label_4;
    QSpinBox *month;
    QLabel *label_5;
    QSpinBox *day;
    QLabel *label_6;

    void setupUi(QWidget *CourierWindow)
    {
        if (CourierWindow->objectName().isEmpty())
            CourierWindow->setObjectName(QString::fromUtf8("CourierWindow"));
        CourierWindow->resize(1662, 926);
        widget = new QWidget(CourierWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1661, 1031));
        widget->setStyleSheet(QString::fromUtf8("background-color:#e1d9cc;"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(340, 30, 291, 81));
        label_3->setStyleSheet(QString::fromUtf8("font: 18pt \"\346\245\267\344\275\223\";"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1450, 130, 111, 28));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1390, 10, 91, 71));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";CCCC66"));
        username = new QLabel(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(1470, 25, 131, 41));
        username->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        search = new QPushButton(widget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setGeometry(QRect(520, 150, 111, 28));
        search->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
        collect = new QPushButton(widget);
        collect->setObjectName(QString::fromUtf8("collect"));
        collect->setGeometry(QRect(700, 150, 91, 28));
        collect->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 150, 281, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        tableWidget = new QTableWidget(widget);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(440, 190, 1191, 651));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        changeMessage = new QPushButton(widget);
        changeMessage->setObjectName(QString::fromUtf8("changeMessage"));
        changeMessage->setGeometry(QRect(840, 150, 93, 28));
        changeMessage->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
        treeWidget = new QTreeWidget(widget);
        treeWidget->headerItem()->setText(0, QString());
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(30, 320, 331, 511));
        treeWidget->setTabletTracking(false);
        treeWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"font: 12pt \"\345\271\274\345\234\206\";"));
        treeWidget->header()->setProperty("showSortIndicator", QVariant(false));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(40, 200, 371, 61));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 31, 31));
        label_2->setStyleSheet(QString::fromUtf8("\n"
"font: 12pt \"\351\232\266\344\271\246\";"));
        year = new QSpinBox(widget_2);
        year->setObjectName(QString::fromUtf8("year"));
        year->setGeometry(QRect(40, 20, 71, 31));
        year->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        year->setMinimum(1970);
        year->setMaximum(2030);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(130, 20, 31, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\232\266\344\271\246\";"));
        month = new QSpinBox(widget_2);
        month->setObjectName(QString::fromUtf8("month"));
        month->setGeometry(QRect(160, 20, 71, 31));
        month->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        month->setMinimum(1);
        month->setMaximum(12);
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(250, 20, 31, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\232\266\344\271\246\";"));
        day = new QSpinBox(widget_2);
        day->setObjectName(QString::fromUtf8("day"));
        day->setGeometry(QRect(290, 20, 61, 31));
        day->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        day->setMinimum(1);
        day->setMaximum(31);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 140, 151, 51));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\232\266\344\271\246\";"));
        widget_2->raise();
        label_3->raise();
        pushButton->raise();
        label->raise();
        username->raise();
        search->raise();
        collect->raise();
        lineEdit->raise();
        tableWidget->raise();
        changeMessage->raise();
        treeWidget->raise();
        label_6->raise();

        retranslateUi(CourierWindow);

        QMetaObject::connectSlotsByName(CourierWindow);
    } // setupUi

    void retranslateUi(QWidget *CourierWindow)
    {
        CourierWindow->setWindowTitle(QApplication::translate("CourierWindow", "\345\277\253\351\200\222\345\221\230\346\223\215\344\275\234\347\225\214\351\235\242", nullptr));
        label_3->setText(QApplication::translate("CourierWindow", "<html><head/><body><p><span style=\" font-size:24pt;\">\347\224\250\346\210\267\347\256\241\347\220\206\347\263\273\347\273\237</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("CourierWindow", "\351\200\200\345\207\272", nullptr));
        label->setText(QApplication::translate("CourierWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        username->setText(QApplication::translate("CourierWindow", "TextLabel", nullptr));
        search->setText(QApplication::translate("CourierWindow", "\346\220\234\347\264\242", nullptr));
        collect->setText(QApplication::translate("CourierWindow", "\346\217\275\346\224\266\345\277\253\351\200\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CourierWindow", "1", nullptr));
        changeMessage->setText(QApplication::translate("CourierWindow", "\344\277\256\346\224\271\350\264\246\345\217\267\344\277\241\346\201\257", nullptr));
        label_2->setText(QApplication::translate("CourierWindow", "\345\271\264\357\274\232", nullptr));
        label_4->setText(QApplication::translate("CourierWindow", "\346\234\210\357\274\232", nullptr));
        label_5->setText(QApplication::translate("CourierWindow", "\346\227\245\357\274\232", nullptr));
        label_6->setText(QApplication::translate("CourierWindow", "\350\257\267\350\276\223\345\205\245\346\237\245\350\257\242\344\277\241\346\201\257\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourierWindow: public Ui_CourierWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERWINDOW_H
