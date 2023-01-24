#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_UserLoginWindow.h"
#include"head.h"
#include<Account.h>
#include <QMessageBox>
/**
* 用户登录界面
*/
class UserLoginWindow : public QWidget
{
	Q_OBJECT

public:
	bool tag = false;//初始化检测
	UserLoginWindow(QWidget *parent = Q_NULLPTR);
	string getUsername();//获取用户名
	string getPassword();//获取密码
	User* getUser();//获取用户对象
	void setUser(User* user);//修改用户对象
	~UserLoginWindow();
	
private:
	Ui::UserLoginWindow *ui;//本界面ui
	string username;//用户名
	string password;//密码
	User* user;//用户对象
public slots:
	void on_returnbotton_clicked();//退出
private slots:
	void login_clicked();//登录

signals :
	void sendLoginSuccess();//登录成功信号
};

