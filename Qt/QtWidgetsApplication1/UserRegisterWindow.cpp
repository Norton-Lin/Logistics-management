#include "UserRegisterWindow.h"

UserRegisterWindow::UserRegisterWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::UserRegisterWindow)
{
	ui->setupUi(this);
	this->setFixedSize(900, 800);//固定窗口大小
	user = new User();
	{
		connect(ui->username, &QLineEdit::editingFinished, this, &UserRegisterWindow::username_finished);//校验用户名
		connect(ui->password, &QLineEdit::editingFinished, this, &UserRegisterWindow::password_finished);//校验密码
		connect(ui->confirmPassword, &QLineEdit::editingFinished, this, &UserRegisterWindow::confirmPassword);//密码二次核对
		connect(ui->name, &QLineEdit::editingFinished, this, &UserRegisterWindow::name_finished);//校验姓名
		connect(ui->number, &QLineEdit::editingFinished, this, &UserRegisterWindow::number_finished);//校验电话号码
		connect(ui->address, &QLineEdit::editingFinished, this, &UserRegisterWindow::address_finished);//校验地址
		connect(ui->confirm, &QPushButton::clicked, this, &UserRegisterWindow::confirm_clicked);//退出按钮槽连接
		connect(ui->back, &QPushButton::clicked, this, &UserRegisterWindow::on_returnbotton_clicked);//退出按钮槽连接
	}
	QString qss;
	QFile file(":/qss/lightblue.css");
	if (file.open(QFile::ReadOnly))
	{
		//用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
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
		ui->tip1->setText("用户名不可为空！");
	else if (Account::checkUsername(Account::qTos(ui->username->text()), 1))
		ui->tip1->setText("该用户名已存在！");
	else
		ui->tip1->setText("");
}

void UserRegisterWindow::password_finished()
{
	if (!Account::checkPassword(Account::qTos(ui->password->text())))
		ui->tip2->setText("密码长度应为8~16位！");
	else
		ui->tip2->setText("");
}

void UserRegisterWindow::confirmPassword()
{
	if (ui->password->text() != ui->confirmPassword->text())
		ui->tip3->setText("两次密码不一致！");
	else
		ui->tip3->setText("");

}

void UserRegisterWindow::name_finished()
{
	if (ui->name->text().isEmpty())
		ui->tip4->setText("用户名不可为空！");
	else
		ui->tip4->setText("");

}

void UserRegisterWindow::number_finished()
{
	if (!Account::checkNumber(Account::qTos(ui->number->text())))
		ui->tip5->setText("电话号码长度应为11位！");
	else
		ui->tip5->setText("");
}

void UserRegisterWindow::address_finished()
{
	if (ui->address->text().isEmpty())
		ui->tip6->setText("地址不可为空！");
	else
		ui->tip6->setText("");
}

