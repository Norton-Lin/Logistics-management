 #include "UserLoginWindow.h"


UserLoginWindow::UserLoginWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::UserLoginWindow)
{
	ui->setupUi(this);
	this->setFixedSize(600, 500);//�̶����ڴ�С
	connect(ui->login, &QPushButton::clicked, this, &UserLoginWindow::login_clicked);//��¼��ť������
	connect(ui->back, &QPushButton::clicked, this, &UserLoginWindow::on_returnbotton_clicked);//�˳���ť������
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
/*
* ��ȡ�û���
*/
string UserLoginWindow::getUsername()
{
	return username;
}
/*
* ��ȡ����
*/
string UserLoginWindow::getPassword()
{
	return password;
}
/*
* ��ȡ�û���Ϣ
*/
User* UserLoginWindow::getUser()
{
	return user;
}

void UserLoginWindow::setUser(User *user)
{
	this->user = user;
}

UserLoginWindow::~UserLoginWindow()
{

}
/*
* �����û���������
*/
void UserLoginWindow::login_clicked()
{
	//�����ļ��в����û���������
	username = Account::qTos(ui->username->text());
	password = Account::qTos(ui->password->text());
	user = new User(username, password);
	if (user->readUser())//�ɹ��ͽ���������
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


