#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include"UserWindow.h"
#include"CourierWindow.h"
#include"ManagerWindow.h"
#include"CourierRegisterWindow.h"
#include"UserRegisterWindow.h"
#include <QtWidgets/qmessagebox.h>
/*
* 初始窗口
*/
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1Class ui;//本界面ui对象
    UserWindow* userWindow;//用户操作界面
    ManagerWindow* managerWindow;//管理员操作界面
    CourierWindow* courierWindow;//快递员操作界面
    UserRegisterWindow* userRegisterWindow;//用户注册界面
    CourierRegisterWindow* courierRegisterWindow;//快递员注册界面
private slots:
    void on_userLogin_clicked();//用户登录按钮点击信号
    void on_managerLogin_clicked();//管理员登录按钮点击信号
    void on_courierLogin_clicked();//快递员登录按钮点击信号
    void on_userRegister_clicked();//用户注册按钮点击信号
    void on_courierRegister_clicked();//快递员注册按钮点击信号

};
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif