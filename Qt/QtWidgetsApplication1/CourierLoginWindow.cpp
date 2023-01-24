#include "CourierLoginWindow.h"

CourierLoginWindow::CourierLoginWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CourierLoginWindow)
{
	ui->setupUi(this);
	this->setFixedSize(600, 500);//固定窗口大小
	connect(ui->login, &QPushButton::clicked, this, &CourierLoginWindow::login_clicked);//登录按钮槽连接
	connect(ui->back, &QPushButton::clicked, this, &CourierLoginWindow::on_returnbotton_clicked);//退出按钮槽连接
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
	//进入文件夹查找用户名和密码
	username = Account::qTos(ui->username->text());
	password = Account::qTos(ui->password->text());
	courier = new Courier(username, password);
	if (courier->readCourier())//成功就进入主界面
	{
		tag = true;
		emit sendLoginSuccess();
	}
	else//失败提示
	{
		QMessageBox message(QMessageBox::NoIcon, "Tip", "账号或密码错误！ ");
		message.exec();
	}
}