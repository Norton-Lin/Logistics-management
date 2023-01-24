#include "ManagerLoginWindow.h"
#include <Database.h>

ManagerLoginWindow::ManagerLoginWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ManagerLoginWindow)
{
	ui->setupUi(this);
	this->setFixedSize(600, 500);//�̶����ڴ�С
	connect(ui->login, &QPushButton::clicked, this, &ManagerLoginWindow::login_clicked);//�˳���ť������
	connect(ui->back, &QPushButton::clicked, this, &ManagerLoginWindow::on_returnbotton_clicked);//�˳���ť������
	QString qss;
	QFile file(":/qss/lightblue.css");
	if (file.open(QFile::ReadOnly))
	{
		//��readAll��ȡĬ��֧�ֵ���ANSI��ʽ,�����С����creator�򿪱༭���˺ܿ��ܴ򲻿�
		qss = QLatin1String(file.readAll());
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		file.close();
	}
}

ManagerLoginWindow::~ManagerLoginWindow()
{
}
/*
* ��ȡ�û���
*/
string ManagerLoginWindow::getUsername()
{
	return username;
}
/*
* ��ȡ����
*/
string ManagerLoginWindow::getPassword()
{
	return password;
}
/*
* ��ȡ����Ա����
*/
Manager* ManagerLoginWindow::getManager()
{
	return manager;
}
/*
* ���ù���Ա����
*/
void ManagerLoginWindow::setUser(Manager* manager)
{
	this->manager = manager;
}
void ManagerLoginWindow::login_clicked()
{
	//�������ݿ�����û���������
	username = Account::qTos(ui->username->text());
	password = Account::qTos(ui->password->text());
	Database database;
	database.connectDatabase();
	manager = new Manager(username,password);
	if(database.findManger(*manager))//�ɹ��ͽ���������
	{
		tag = true;
		emit sendLoginSuccess();
	}
	else//ʧ����ʾ
	{
		QMessageBox message(QMessageBox::NoIcon, "Tip", "�˺Ż�������� ");
		message.exec();
	}
	database.FreeConnect();
}