#include "QtWidgetsApplication1.h"
/*
* 初始窗口初始化
*/
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_userLogin_clicked);//用户登录按钮槽连接
	connect(ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsApplication1::on_courierLogin_clicked);//快递员登录按钮槽连接
	connect(ui.pushButton_3, &QPushButton::clicked, this, &QtWidgetsApplication1::on_managerLogin_clicked);//管理员登录按钮槽连接
	connect(ui.pushButton_4, &QPushButton::clicked, this, &QtWidgetsApplication1::on_userRegister_clicked);//用户注册按钮槽连接
	connect(ui.pushButton_5, &QPushButton::clicked, this, &QtWidgetsApplication1::on_courierRegister_clicked);//快递员注册按钮槽连接
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
/*
* 用户登录窗口
*/
void QtWidgetsApplication1::on_userLogin_clicked()
{
	userWindow = new UserWindow;
	this->hide();
}
/*
* 管理员登录窗口
*/
void QtWidgetsApplication1::on_managerLogin_clicked()
{
	managerWindow = new ManagerWindow;;
	this->hide();
}
/*
* 快递员登录窗口
*/
void QtWidgetsApplication1::on_courierLogin_clicked()
{
	courierWindow = new CourierWindow;
	this -> hide();
}
/*
* 用户注册窗口
*/
void QtWidgetsApplication1::on_userRegister_clicked()
{
	userRegisterWindow = new UserRegisterWindow;
	userRegisterWindow->show();
	this->hide();
}
/*
* 快递员注册窗口
*/
void QtWidgetsApplication1::on_courierRegister_clicked()
{
	courierRegisterWindow = new CourierRegisterWindow;
	courierRegisterWindow->show();
	this->hide();
}
/*
* 用户登录界面退出窗口
*/
void UserLoginWindow::on_returnbotton_clicked()
{
	QMessageBox message(QMessageBox::NoIcon, "Tip", "退出成功！ ");
	message.exec();
	QtWidgetsApplication1* temp = new QtWidgetsApplication1;
	temp->show();//program窗口显示
	close();
	//this->hide();//本窗口隐藏
}
/*
* 管理员登录界面退出窗口
*/
void ManagerLoginWindow::on_returnbotton_clicked()
{
	QMessageBox message(QMessageBox::NoIcon, "Tip", "退出成功！ ");
	message.exec();
	QtWidgetsApplication1* temp = new QtWidgetsApplication1;
	temp->show();//program窗口显示
	close();
	//this->hide();//本窗口隐藏
}
/*
* 快递员登录界面退出窗口
*/
void CourierLoginWindow::on_returnbotton_clicked()
{
	QMessageBox message(QMessageBox::NoIcon, "Tip", "退出成功！ ");
	message.exec();
	QtWidgetsApplication1* temp = new QtWidgetsApplication1;
	temp->show();//program窗口显示
	close();
	//this->hide();//本窗口隐藏
}
/*
* 用户注册界面退出
*/
void UserRegisterWindow::on_returnbotton_clicked() {
	QMessageBox message(QMessageBox::NoIcon, "Tip", "退出成功！ ");
	message.exec();
	QtWidgetsApplication1* temp = new QtWidgetsApplication1;
	temp->show();//program窗口显示
	close();
}
/*
* 用户确认注册函数
*/
void UserRegisterWindow::confirm_clicked()
{
	if (ui->tip1->text().isEmpty() && ui->tip2->text().isEmpty() && ui->tip3->text().isEmpty() &&
		ui->tip4->text().isEmpty() && ui->tip5->text().isEmpty() && ui->tip6->text().isEmpty()&& 
		!ui->username->text().isDetached() &&!ui->name->text().isEmpty() 
		&& !ui->password->text().isEmpty() && !ui->confirmPassword->text().isEmpty() &&
		!ui->number->text().isEmpty()&&!ui->address->text().isEmpty())
	{
		user->registerAccount(Account::qTos(ui->username->text()), Account::qTos(ui->name->text()), Account::qTos(ui->number->text()),
			Account::qTos(ui->password->text()), Account::qTos(ui->address->text()), 0);
		user->saveUser();//保存用户信息
		user->saveUserList(user->getUserName());
		QMessageBox message(QMessageBox::NoIcon, "Tip", "注册成功！！");
		message.exec();
		QtWidgetsApplication1* temp = new QtWidgetsApplication1;
		temp->show();//program窗口显示
		close();
	}
	else {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "注册失败，请修改注册信息！！");
		message.exec();
	}
}
/*
* 快递员注册界面退出
*/
void CourierRegisterWindow::on_returnbotton_clicked() {
	QMessageBox message(QMessageBox::NoIcon, "Tip", "退出成功！ ");
	message.exec();
	QtWidgetsApplication1* temp = new QtWidgetsApplication1;
	temp->show();//program窗口显示
	close();
}
/*
* 快递员确认注册函数
*/
void CourierRegisterWindow::confirm_clicked()
{
	if (ui->tip1->text().isEmpty() && ui->tip2->text().isEmpty() && ui->tip3->text().isEmpty() &&
		ui->tip4->text().isEmpty() && ui->tip5->text().isEmpty()&& !ui->username->text().isDetached()&&
		!ui->name->text().isEmpty()&&!ui->password->text().isEmpty()&& !ui->confirmPassword->text().isEmpty()&&
		!ui->number->text().isEmpty())
	{
		courier->registerAccount(Account::qTos(ui->username->text()), Account::qTos(ui->name->text()), 
			Account::qTos(ui->number->text()),Account::qTos(ui->password->text()), 0);
		courier->setCompany("0");
		courier->saveCourier();//保存快递员信息
		courier->saveCourierToList();//保存快递员信息到列表中
		QMessageBox message(QMessageBox::NoIcon, "Tip", "注册成功！！");
		message.exec();
		QtWidgetsApplication1* temp = new QtWidgetsApplication1;
		temp->show();//program窗口显示
		close();
	}
	else {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "注册失败，请修改注册信息！！");
		message.exec();
	}
}

