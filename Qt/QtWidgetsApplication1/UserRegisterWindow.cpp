#include "UserRegisterWindow.h"

UserRegisterWindow::UserRegisterWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::UserRegisterWindow)
{
	ui->setupUi(this);
	this->setFixedSize(900, 800);//�̶����ڴ�С
	user = new User();
	{
		connect(ui->username, &QLineEdit::editingFinished, this, &UserRegisterWindow::username_finished);//У���û���
		connect(ui->password, &QLineEdit::editingFinished, this, &UserRegisterWindow::password_finished);//У������
		connect(ui->confirmPassword, &QLineEdit::editingFinished, this, &UserRegisterWindow::confirmPassword);//������κ˶�
		connect(ui->name, &QLineEdit::editingFinished, this, &UserRegisterWindow::name_finished);//У������
		connect(ui->number, &QLineEdit::editingFinished, this, &UserRegisterWindow::number_finished);//У��绰����
		connect(ui->address, &QLineEdit::editingFinished, this, &UserRegisterWindow::address_finished);//У���ַ
		connect(ui->confirm, &QPushButton::clicked, this, &UserRegisterWindow::confirm_clicked);//�˳���ť������
		connect(ui->back, &QPushButton::clicked, this, &UserRegisterWindow::on_returnbotton_clicked);//�˳���ť������
	}
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

UserRegisterWindow::~UserRegisterWindow()
{
}

void UserRegisterWindow::username_finished()
{
	if (ui->username->text().isEmpty())
		ui->tip1->setText("�û�������Ϊ�գ�");
	else if (Account::checkUsername(Account::qTos(ui->username->text()), 1))
		ui->tip1->setText("���û����Ѵ��ڣ�");
	else
		ui->tip1->setText("");
}

void UserRegisterWindow::password_finished()
{
	if (!Account::checkPassword(Account::qTos(ui->password->text())))
		ui->tip2->setText("���볤��ӦΪ8~16λ��");
	else
		ui->tip2->setText("");
}

void UserRegisterWindow::confirmPassword()
{
	if (ui->password->text() != ui->confirmPassword->text())
		ui->tip3->setText("�������벻һ�£�");
	else
		ui->tip3->setText("");

}

void UserRegisterWindow::name_finished()
{
	if (ui->name->text().isEmpty())
		ui->tip4->setText("�û�������Ϊ�գ�");
	else
		ui->tip4->setText("");

}

void UserRegisterWindow::number_finished()
{
	if (!Account::checkNumber(Account::qTos(ui->number->text())))
		ui->tip5->setText("�绰���볤��ӦΪ11λ��");
	else
		ui->tip5->setText("");
}

void UserRegisterWindow::address_finished()
{
	if (ui->address->text().isEmpty())
		ui->tip6->setText("��ַ����Ϊ�գ�");
	else
		ui->tip6->setText("");
}

