#pragma once

#include <QWidget>
#include "ui_CourierLoginWindow.h"
#include <head.h>
#include <Account.h>
#include <QMessageBox>
#include <QDialog>
class CourierLoginWindow : public QWidget
{
	Q_OBJECT

public:
	bool tag = false;
	CourierLoginWindow(QWidget *parent = Q_NULLPTR);
	string getUsername();//获取用户名
	string getPassword();//获取密码
	Courier* getCourier();//获取用户对象
	void setCourier(Courier* courier);//修改用户对象
	~CourierLoginWindow();

private:
	Ui::CourierLoginWindow *ui;
	string username;
	string password;
	Courier* courier;

public slots:
	void on_returnbotton_clicked();//退出
private slots:
	void login_clicked();//登录
signals:
	void sendLoginSuccess();//登录成功信号
};
