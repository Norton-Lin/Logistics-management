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
	string getUsername();//��ȡ�û���
	string getPassword();//��ȡ����
	Manager* getManager();//��ȡ����Ա����
	void setUser(Manager* manager);//�޸Ĺ���Ա����

private:
	Ui::ManagerLoginWindow* ui;
	string username;
	string password;
	Manager* manager;
public slots:
	void on_returnbotton_clicked();//�˳�
private slots:
	void login_clicked();//��¼
signals:
	void sendLoginSuccess();//��¼�ɹ��ź�

};
