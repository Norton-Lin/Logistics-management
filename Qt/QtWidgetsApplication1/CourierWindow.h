#pragma once

#include <QWidget>
#include "ui_CourierWindow.h"
#include <CourierLoginWindow.h>
#include <QTreeWidget>
#include <head.h>
#include<Account.h>
#include<Database.h>

class CourierWindow : public QWidget
{
	Q_OBJECT

public:
	CourierWindow(QWidget *parent = Q_NULLPTR);
	~CourierWindow();

private:
	Ui::CourierWindow *ui;
	//UserLoginWindow* loginWindow;//登录界面
	CourierLoginWindow *loginWindow;//登录界面
	QTreeWidgetItem* item_t;//树表结点
	Courier* courier;
	Database* database;//数据库
	QList<Goods> LGoods;//快递列表
	void init_Courier();//快递员信息初始化
	void init_GoodWindow();//显示快递列表
	void init_CourierWindow();//显示快递员信息列表
private slots:
	void on_returnbotton_clicked();//退出
	void on_findAllMessage_clicked();//查询信息
	void on_changeMessage_clicked();//修改账号信息
	void on_check_Clicked(QTreeWidgetItem* item, int column);//选择查询快递信息
	void on_collectExpress_clicked();//揽收快递
};
