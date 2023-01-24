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
	UserLoginWindow* loginWindow;//��¼����
	QTreeWidgetItem* item_t;//������
	User *user;
	Database* database;
	vector<string> userList;//�û����б�
	QList<Goods> LGoods;//����б�
	Goods good;//�������
	void init_User();
	void init_GoodWindow();//��ʾ����б�
	void init_UserWindow();//��ʾ�û���Ϣ�б�
private slots:
	void on_returnbotton_clicked();//�˳�
	void on_findAllMessage_clicked();//��ѯ��Ϣ
	void on_recharge_clicked();//�˺ų�ֵ
	void on_changeMessage_clicked();//�޸��˺���Ϣ
	void on_check_Clicked(QTreeWidgetItem* item, int column);//ѡ���ѯ�����Ϣ
	void on_sendExpress_clicked();//���Ϳ��
	void on_signExpress_clicked();//ǩ�տ��
};
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif