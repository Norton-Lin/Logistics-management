#pragma once

#include <QtWidgets/QWidget>
#include "ui_client.h"
#include <qtcpsocket.h>
#include<head.h>
#include<Account.h>
#include"Goods.h"
#include<qmessagebox.h>
#include<qcombobox.h>
#include <QtWidgets/QApplication>
#include <QFile>
#include <QHostAddress>
#include <QPushButton>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QInputDialog>
#include<qdesktopservices.h>
class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget* parent = 0);
    ~client();
    void messageClear();
private slots:
    void init_UserWindow();//初始化用户界面
    void init_CourierWindow();//初始化快递员界面
    void init_ManagerWindow();//初始化管理员窗口界面
    void init_CourierRegister();//初始化快递员注册界面
    void init_UserRegister();//初始化用户注册界面
    void username_finished();//用户名输入结束
    void password_finished();//密码输入结束
    void confirmPassword();//二次确认密码结束
    void name_finished();//姓名输入结束
    void number_finished();//电话号码输入结束
    void address_finished();//地址输入结束
    void confirm_clicked();//确认注册
    void on_Userlogin_clicked();//用户登录
    void on_Managerlogin_clicked();//管理员登录
    void on_Courierlogin_clicked();//快递员登录
    void on_UserRegister_clicked();//用户注册
    void on_CourierRegister_clicked();//快递员注册
    void on_returnChooseWindow_clicked();//返回初始界面
    void slotReadyRead();//数据接收
    void on_UserLoginWindow_login();//用户登录
    void on_findAllMessage_user();//用户窗口搜索
    void on_userWindowcheck_clicked(QTreeWidgetItem* item, int column);//用户窗口树表选择
    void on_userWindowChangeMessage_clicked(); //用户窗口 修改账号信息
    void on_sendExpress_clicked();//发送快递
    void on_signExpress_clicked();//签收快递
    void on_recharge_clicked();//账户充值
    void on_ManagerLoginWindow_login();//管理员登录
    void on_findAllMessage_manager();//管理员窗口搜索
    void on_managerWindowcheck_clicked(QTreeWidgetItem* item, int column);//管理员窗口树表选择
    void on_addCourier_clicked();//快递员添加
    void on_deleteCourier_clicked();//快递员删除
    void on_distributionExpress_clicked();//快递分配
    void on_CourierLoginWindow_login();//快递员登录
    void on_findAllMessage_courier();//快递员窗口搜索
    void on_courierWindowcheck_clicked(QTreeWidgetItem* item, int column);//快递员窗口树表选择
    void on_courierWindowChangeMessage_clicked(); //快递员窗口 修改账号信息
    void on_collectExpress_clicked();//快递揽收
    //账号充值
private:
    Ui::clientClass *ui;//本界面ui对象指针
    QTcpSocket* tcp;//数据通信socket
    QTreeWidgetItem* item_t;//树表指针
    bool tag = false;//登录状态
    int windowChoice = 0;//选择进入窗口
    int showChoice = 0;//数据栏展示窗口
    double Balance = 0;//当前账号余额
    User* user = nullptr;//当前用户
    Manager* manager = nullptr;//当前管理员
    Courier* courier = nullptr;//当前快递员
    QList<Goods> LGoods;//快递列表
    QList<User> LUsers;//用户列表
    QList<Courier> LCourier;//快递员列表
};
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif



