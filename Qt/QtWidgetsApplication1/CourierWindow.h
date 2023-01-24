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
	//UserLoginWindow* loginWindow;//��¼����
	CourierLoginWindow *loginWindow;//��¼����
	QTreeWidgetItem* item_t;//������
	Courier* courier;
	Database* database;//���ݿ�
	QList<Goods> LGoods;//����б�
	void init_Courier();//���Ա��Ϣ��ʼ��
	void init_GoodWindow();//��ʾ����б�
	void init_CourierWindow();//��ʾ���Ա��Ϣ�б�
private slots:
	void on_returnbotton_clicked();//�˳�
	void on_findAllMessage_clicked();//��ѯ��Ϣ
	void on_changeMessage_clicked();//�޸��˺���Ϣ
	void on_check_Clicked(QTreeWidgetItem* item, int column);//ѡ���ѯ�����Ϣ
	void on_collectExpress_clicked();//���տ��
};
