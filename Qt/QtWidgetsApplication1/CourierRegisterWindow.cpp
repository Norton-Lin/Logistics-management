#include "CourierRegisterWindow.h"

CourierRegisterWindow::CourierRegisterWindow(QWidget* parent)
	: QWidget(parent),
	ui(new Ui::CourierRegisterWindow)
{
	ui->setupUi(this);
	this->setFixedSize(900, 800);//�̶����ڴ�С
	courier = new Courier();
	{
		connect(ui->username, &QLineEdit::editingFinished, this, &CourierRegisterWindow::username_finished);//У���û���
		connect(ui->password, &QLineEdit::editingFinished, this, &CourierRegisterWindow::password_finished);//У������
		connect(ui->confirmPassword, &QLineEdit::editingFinished, this, &CourierRegisterWindow::confirmPassword);//������κ˶�
		connect(ui->name, &QLineEdit::editingFinished, this, &CourierRegisterWindow::name_finished);//У������
		connect(ui->number, &QLineEdit::editingFinished, this, &CourierRegisterWindow::number_finished);//У��绰����
		connect(ui->confirm, &QPushButton::clicked, this, &CourierRegisterWindow::confirm_clicked);//ע�ᰴť������
		connect(ui->back, &QPushButton::clicked, this, &CourierRegisterWindow::on_returnbotton_clicked);//�˳���ť������
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

CourierRegisterWindow::~CourierRegisterWindow()
{
}

void CourierRegisterWindow::username_finished()
{
	if (ui->username->text().isEmpty())
		ui->tip1->setText("�û�������Ϊ�գ�");
	else if (Account::checkUsername(Account::qTos(ui->username->text()), 2))
		ui->tip1->setText("���û����Ѵ��ڣ�");
	else
		ui->tip1->setText("");
}

void CourierRegisterWindow::password_finished()
{
	if (!Account::checkPassword(Account::qTos(ui->password->text())))
		ui->tip2->setText("���볤��ӦΪ8~16λ��");
	else
		ui->tip2->setText("");
}

void CourierRegisterWindow::confirmPassword()
{
	if (ui->password->text() != ui->confirmPassword->text())
		ui->tip3->setText("�������벻һ�£�");
	else
		ui->tip3->setText("");

}

void CourierRegisterWindow::name_finished()
{
	if (ui->name->text().isEmpty())
		ui->tip4->setText("�û�������Ϊ�գ�");
	else
		ui->tip4->setText("");

}

void CourierRegisterWindow::number_finished()
{
	if (!Account::checkNumber(Account::qTos(ui->number->text())))
		ui->tip5->setText("�绰���볤��ӦΪ11λ�����֣�");
	else
		ui->tip5->setText("");
}