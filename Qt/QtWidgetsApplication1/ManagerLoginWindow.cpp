#include "ManagerLoginWindow.h"
#include <Database.h>

ManagerLoginWindow::ManagerLoginWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ManagerLoginWindow)
{
	ui->setupUi(this);
	this->setFixedSize(600, 500);//固定窗口大小
	connect(ui->login, &QPushButton::clicked, this, &ManagerLoginWindow::login_clicked);//退出按钮槽连接
	connect(ui->back, &QPushButton::clicked, this, &ManagerLoginWindow::on_returnbotton_clicked);//退出按钮槽连接
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

ManagerLoginWindow::~ManagerLoginWindow()
{
}
/*
* 获取用户名
*/
string ManagerLoginWindow::getUsername()
{
	return username;
}
/*
* 获取密码
*/
string ManagerLoginWindow::getPassword()
{
	return password;
}
/*
* 获取管理员对象
*/
Manager* ManagerLoginWindow::getManager()
{
	return manager;
}
/*
* 设置管理员对象
*/
void ManagerLoginWindow::setUser(Manager* manager)
{
	this->manager = manager;
}
void ManagerLoginWindow::login_clicked()
{
	//进入数据库查找用户名和密码
	username = Account::qTos(ui->username->text());
	password = Account::qTos(ui->password->text());
	Database database;
	database.connectDatabase();
	manager = new Manager(username,password);
	if(database.findManger(*manager))//成功就进入主界面
	{
		tag = true;
		emit sendLoginSuccess();
	}
	else//失败提示
	{
		QMessageBox message(QMessageBox::NoIcon, "Tip", "账号或密码错误！ ");
		message.exec();
	}
	database.FreeConnect();
}