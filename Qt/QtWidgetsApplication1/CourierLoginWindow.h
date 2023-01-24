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
	string getUsername();//��ȡ�û���
	string getPassword();//��ȡ����
	Courier* getCourier();//��ȡ�û�����
	void setCourier(Courier* courier);//�޸��û�����
	~CourierLoginWindow();

private:
	Ui::CourierLoginWindow *ui;
	string username;
	string password;
	Courier* courier;

public slots:
	void on_returnbotton_clicked();//�˳�
private slots:
	void login_clicked();//��¼
signals:
	void sendLoginSuccess();//��¼�ɹ��ź�
};
