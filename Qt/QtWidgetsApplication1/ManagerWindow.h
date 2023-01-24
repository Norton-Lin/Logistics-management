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
	ManagerLoginWindow* loginWindow;//��¼����
	QTreeWidgetItem* item_t;//������
	Manager* manager;
	Database* database;
	vector<string> tempList;//�˺������б�
	vector<User> userList;
	vector<Courier> courierList;//�������Ա�б�
	QList<Goods> LGoods;//����б�
	QList<Courier> LCourier;//���Ա�б�
	QList<User> LUser;//�û��б�
	void init_Manager();//����Ա��Ϣ��ʼ��
	void init_GoodWindow();//��ʾ����б�
	void init_UserWindow();//��ʾ�û���Ϣ�б�
	void init_ManagerWindow();//��ʾ����Ա��Ϣ�б�
private slots:
	void on_returnbotton_clicked();//�˳�
	void on_findAllMessage_clicked();//��ѯ��Ϣ
	void on_distribute_clicked();//��ݷ���
	void on_check_Clicked(QTreeWidgetItem* item, int column);//ѡ���ѯ�����Ϣ
	void on_addCourier_clicked();//���Ϳ��
	void on_deleteCourier_clicked();//ǩ�տ��
};

