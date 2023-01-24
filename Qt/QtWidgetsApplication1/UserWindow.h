#pragma once

#include <QWidget>
#include "ui_UserWindow.h"
#include <UserLoginWindow.h>
#include <QTreeWidget>
#include <head.h>
#include<Account.h>
#include<Database.h>

class UserWindow : public QWidget
{
	Q_OBJECT

public:
	UserWindow(QWidget *parent = Q_NULLPTR);
	~UserWindow();

private:
	Ui::UserWindow *ui;
	UserLoginWindow* loginWindow;//登录界面
	QTreeWidgetItem* item_t;//树表结点
	User *user;
	Database* database;
	vector<string> userList;//用户名列表
	QList<Goods> LGoods;//快递列表
	Goods good;//单个快递
	void init_User();
	void init_GoodWindow();//显示快递列表
	void init_UserWindow();//显示用户信息列表
private slots:
	void on_returnbotton_clicked();//退出
	void on_findAllMessage_clicked();//查询信息
	void on_recharge_clicked();//账号充值
	void on_changeMessage_clicked();//修改账号信息
	void on_check_Clicked(QTreeWidgetItem* item, int column);//选择查询快递信息
	void on_sendExpress_clicked();//发送快递
	void on_signExpress_clicked();//签收快递
};
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif