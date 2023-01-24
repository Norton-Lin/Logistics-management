#include "CourierLoginWindow.h"

CourierLoginWindow::CourierLoginWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CourierLoginWindow)
{
	ui->setupUi(this);
	this->setFixedSize(600, 500);//�̶����ڴ�С
	connect(ui->login, &QPushButton::clicked, this, &CourierLoginWindow::login_clicked);//��¼��ť������
	connect(ui->back, &QPushButton::clicked, this, &CourierLoginWindow::on_returnbotton_clicked);//�˳���ť������
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

string CourierLoginWindow::getUsername()
{
	return username;
}

string CourierLoginWindow::getPassword()
{
	return password;
}

Courier* CourierLoginWindow::getCourier()
{
	return courier;
}

void CourierLoginWindow::setCourier(Courier* courier)
{
	this->courier = courier;
}

CourierLoginWindow::~CourierLoginWindow()
{
}
void CourierLoginWindow::login_clicked()
{
	//�����ļ��в����û���������
	username = Account::qTos(ui->username->text());
	password = Account::qTos(ui->password->text());
	courier = new Courier(username, password);
	if (courier->readCourier())//�ɹ��ͽ���������
	{
		tag = true;
		emit sendLoginSuccess();
	}
	else//ʧ����ʾ
	{
		QMessageBox message(QMessageBox::NoIcon, "Tip", "�˺Ż�������� ");
		message.exec();
	}
}