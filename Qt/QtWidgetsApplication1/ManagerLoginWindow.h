#pragma once

#include <QWidget>
#include <QDialog>
#include"head.h"
#include "ui_ManagerLoginWindow.h"
#include<Account.h>
#include <QMessageBox>
class ManagerLoginWindow : public QWidget
{
	Q_OBJECT

public:
	bool tag = false;
	ManagerLoginWindow(QWidget *parent = Q_NULLPTR);
	~ManagerLoginWindow();
	string getUsername();//获取用户名
	string getPassword();//获取密码
	Manager* getManager();//获取管理员对象
	void setUser(Manager* manager);//修改管理员对象

private:
	Ui::ManagerLoginWindow* ui;
	string username;
	string password;
	Manager* manager;
public slots:
	void on_returnbotton_clicked();//退出
private slots:
	void login_clicked();//登录
signals:
	void sendLoginSuccess();//登录成功信号

};
