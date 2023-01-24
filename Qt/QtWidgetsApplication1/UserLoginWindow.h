#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_UserLoginWindow.h"
#include"head.h"
#include<Account.h>
#include <QMessageBox>
/**
* �û���¼����
*/
class UserLoginWindow : public QWidget
{
	Q_OBJECT

public:
	bool tag = false;//��ʼ�����
	UserLoginWindow(QWidget *parent = Q_NULLPTR);
	string getUsername();//��ȡ�û���
	string getPassword();//��ȡ����
	User* getUser();//��ȡ�û�����
	void setUser(User* user);//�޸��û�����
	~UserLoginWindow();
	
private:
	Ui::UserLoginWindow *ui;//������ui
	string username;//�û���
	string password;//����
	User* user;//�û�����
public slots:
	void on_returnbotton_clicked();//�˳�
private slots:
	void login_clicked();//��¼

signals :
	void sendLoginSuccess();//��¼�ɹ��ź�
};

