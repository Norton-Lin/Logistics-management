#pragma once

#include <QWidget>
#include "ui_ManagerWindow.h"
#include <ManagerLoginWindow.h>
#include <QTreeWidget>
#include <head.h>
#include<Account.h>
#include<Database.h>
class ManagerWindow : public QWidget
{
	Q_OBJECT

public:
	ManagerWindow(QWidget* parent = Q_NULLPTR);
	~ManagerWindow();

private:
	Ui::ManagerWindow* ui;
	ManagerLoginWindow* loginWindow;//登录界面
	QTreeWidgetItem* item_t;//树表结点
	Manager* manager;
	Database* database;
	vector<string> tempList;//账号姓名列表
	vector<User> userList;
	vector<Courier> courierList;//无属快递员列表
	QList<Goods> LGoods;//快递列表
	QList<Courier> LCourier;//快递员列表
	QList<User> LUser;//用户列表
	void init_Manager();//管理员信息初始化
	void init_GoodWindow();//显示快递列表
	void init_UserWindow();//显示用户信息列表
	void init_ManagerWindow();//显示管理员信息列表
private slots:
	void on_returnbotton_clicked();//退出
	void on_findAllMessage_clicked();//查询信息
	void on_distribute_clicked();//快递分配
	void on_check_Clicked(QTreeWidgetItem* item, int column);//选择查询快递信息
	void on_addCourier_clicked();//发送快递
	void on_deleteCourier_clicked();//签收快递
};

