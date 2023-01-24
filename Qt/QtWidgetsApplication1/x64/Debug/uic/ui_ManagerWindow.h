/********************************************************************************
** Form generated from reading UI file 'ManagerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGERWINDOW_H
#define UI_MANAGERWINDOW_H

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

class Ui_ManagerWindow
{
public:
    QWidget *widget;
    QLabel *label_3;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *username;
    QPushButton *search;
    QPushButton *addCourier;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QPushButton *distribution;
    QPushButton *deleteCourier;
    QTreeWidget *treeWidget;
    QWidget *widget_2;
    QLabel *label_2;
    QSpinBox *year;
    QLabel *label_4;
    QSpinBox *month;
    QLabel *label_5;
    QSpinBox *day;
    QLabel *label_6;

    void setupUi(QWidget *ManagerWindow)
    {
        if (ManagerWindow->objectName().isEmpty())
            ManagerWindow->setObjectName(QString::fromUtf8("ManagerWindow"));
        ManagerWindow->resize(1660, 950);
        widget = new QWidget(ManagerWindow);
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
        username->setGeometry(QRect(1480, 25, 121, 41));
        username->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        search = new QPushButton(widget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setGeometry(QRect(520, 150, 111, 28));
        search->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
        addCourier = new QPushButton(widget);
        addCourier->setObjectName(QString::fromUtf8("addCourier"));
        addCourier->setGeometry(QRect(820, 150, 91, 28));
        addCourier->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
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
        distribution = new QPushButton(widget);
        distribution->setObjectName(QString::fromUtf8("distribution"));
        distribution->setGeometry(QRect(680, 150, 93, 28));
        distribution->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
        deleteCourier = new QPushButton(widget);
        deleteCourier->setObjectName(QString::fromUtf8("deleteCourier"));
        deleteCourier->setGeometry(QRect(950, 150, 93, 28));
        deleteCourier->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 200, 205)"));
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
        addCourier->raise();
        lineEdit->raise();
        tableWidget->raise();
        distribution->raise();
        deleteCourier->raise();
        treeWidget->raise();
        label_6->raise();

        retranslateUi(ManagerWindow);

        QMetaObject::connectSlotsByName(ManagerWindow);
    } // setupUi

    void retranslateUi(QWidget *ManagerWindow)
    {
        ManagerWindow->setWindowTitle(QApplication::translate("ManagerWindow", "\347\256\241\347\220\206\345\221\230\346\223\215\344\275\234\347\225\214\351\235\242", nullptr));
        label_3->setText(QApplication::translate("ManagerWindow", "<html><head/><body><p><span style=\" font-size:24pt;\">\347\211\251\346\265\201\347\256\241\347\220\206\347\263\273\347\273\237</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("ManagerWindow", "\351\200\200\345\207\272", nullptr));
        label->setText(QApplication::translate("ManagerWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        username->setText(QApplication::translate("ManagerWindow", "TextLabel", nullptr));
        search->setText(QApplication::translate("ManagerWindow", "\346\220\234\347\264\242", nullptr));
        addCourier->setText(QApplication::translate("ManagerWindow", "\345\277\253\351\200\222\345\221\230\346\267\273\345\212\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ManagerWindow", "1", nullptr));
        distribution->setText(QApplication::translate("ManagerWindow", "\345\277\253\351\200\222\345\210\206\351\205\215", nullptr));
        deleteCourier->setText(QApplication::translate("ManagerWindow", "\345\277\253\351\200\222\345\221\230\345\210\240\351\231\244", nullptr));
        label_2->setText(QApplication::translate("ManagerWindow", "\345\271\264\357\274\232", nullptr));
        label_4->setText(QApplication::translate("ManagerWindow", "\346\234\210\357\274\232", nullptr));
        label_5->setText(QApplication::translate("ManagerWindow", "\346\227\245\357\274\232", nullptr));
        label_6->setText(QApplication::translate("ManagerWindow", "\350\257\267\350\276\223\345\205\245\346\237\245\350\257\242\344\277\241\346\201\257\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManagerWindow: public Ui_ManagerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGERWINDOW_H
