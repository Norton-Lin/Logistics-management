#include "UserWindow.h"
UserWindow::UserWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::UserWindow)
{
	ui->setupUi(this);
	ui->widget->setFixedSize(2000, 1200);
	ui->widget->removeEventFilter(ui->pushButton);
	loginWindow = new UserLoginWindow();
	loginWindow->show();
	item_t = new QTreeWidgetItem;
	database = new Database();//连接数据库
	database->connectDatabase();
	database->findUser(userList);//读取用户名列表
	//lamda表达式m
	auto f = [&]() {
		this->show();
		loginWindow->hide();
	};
	connect(loginWindow, &UserLoginWindow::sendLoginSuccess, this, f);
	connect(ui->pushButton, &QPushButton::clicked, this, &UserWindow::on_returnbotton_clicked);//退出按钮槽连接
	connect(ui->search, &QPushButton::clicked, this, &UserWindow::on_findAllMessage_clicked);//搜索按钮槽连接
	connect(ui->sendExpress, &QPushButton::clicked, this, &UserWindow::on_sendExpress_clicked);//发送快递按钮槽连接
	connect(ui->changeMessage, &QPushButton::clicked, this, &UserWindow::on_changeMessage_clicked);//修改信息按钮槽连接
	connect(ui->recharge, &QPushButton::clicked, this, &UserWindow::on_recharge_clicked);//充值按钮槽连接
	connect(ui->sign, &QPushButton::clicked, this, &UserWindow::on_signExpress_clicked);//签收按钮槽连接
	ui->treeWidget->setColumnCount(1);//一列
	ui->treeWidget->clear();
	//界面初始化代码块（树表）
	{
		QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget);
		topItem1->setText(0, "1.查询所有快递信息");
		topItem1->setText(1, "1");
		topItem1->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem1);

		QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget);
		topItem2->setText(0, "2. 查询指定快递信息");
		topItem2->setText(1, "2");
		ui->treeWidget->addTopLevelItem(topItem2);

		QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
		item21->setText(0, "2.1 根据快递编号查询");
		item21->setCheckState(0, Qt::Unchecked);
		item21->setText(1, "3");

		QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
		item22->setText(0, "2.2 根据快递时间查询");
		item22->setText(1, "4");

		QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
		item221->setText(0, "2.2.1 根据寄件时间查询");
		item221->setCheckState(0, Qt::Unchecked);
		item221->setText(1, "5");

		QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
		item222->setText(0, "2.2.2 根据揽收时间查询");
		item222->setCheckState(0, Qt::Unchecked);
		item222->setText(1, "6");

		QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
		item223->setText(0, "2.2.3根据收件时间查询");
		item223->setCheckState(0, Qt::Unchecked);
		item223->setText(1, "7");
		
		QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
		item23->setText(0, "2.3 根据用户查询");
		item23->setText(1, "8");
		
		QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
		item231->setText(0, "2.3.1根据寄件人查询");
		item231->setCheckState(0, Qt::Unchecked);
		item231->setText(1, "9");

		QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
		item232->setText(0, "2.3.2根据快递员查询");
		item232->setCheckState(0, Qt::Unchecked);
		item232->setText(1, "10");

		QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
		item233->setText(0, "2.3.3根据收件人查询");
		item233->setCheckState(0, Qt::Unchecked);
		item233->setText(1, "11");

		QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget);
		topItem3->setText(0, "3. 查询所有未签收快递信息");
		topItem3->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem3);
		topItem3->setText(1, "12");

		QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
		topItem4->setText(0, "4. 查询用户信息");
		topItem4->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem4);
		topItem4->setText(1, "13");

		QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget);
		topItem5->setText(0, "5. 查询余额");
		topItem5->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem5);
		topItem5->setText(1, "14");
		connect(ui->treeWidget, &QTreeWidget::itemClicked, this,
			&UserWindow::on_check_Clicked);
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

UserWindow::~UserWindow()
{
}
/*
* 用户信息初始化
*/
void UserWindow::init_User()
{
	user = loginWindow->getUser();//获得用户信息
	user->setSend(database->findPackageByName(user->getUserName(), 1));//读取用户寄件信息
	user->setReceive(database->findPackageByName(user->getUserName(), 2));//读取用户收件信息
	loginWindow->tag = false;
	ui->username->setText( Account::sToq(user->getUserName()));
}
/*
* tableWidget 快递显示界面初始化
*/
void UserWindow::init_GoodWindow()
{
	ui->tableWidget->setRowCount(1); //设置行数
	ui->tableWidget->setColumnCount(12); //设置列数
	QStringList header;
	header << "快递单号" << "快递类型" << "快递状态" << "数量（kg/本）" << "发送时间" << "揽收时间"
		<< "签收时间" << "寄件人" << "快递员" << "收件人" << "快递描述" << "承运公司";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*
* tableWidget 用户信息显示界面初始化
*/
void UserWindow::init_UserWindow()
{
	ui->tableWidget->setRowCount(1); //设置行数
	ui->tableWidget->setColumnCount(6); //设置列数
	QStringList header;
	header << "用户名" << "密码" << "姓名" << "电话号码" << "地址" << "余额";
	ui->tableWidget->setHorizontalHeaderLabels(header);
} 
/*
* 查询所有信息
* 支持查询 快递信息，账号信息，余额
*/
void UserWindow::on_findAllMessage_clicked()
{
	if (loginWindow->tag)
		init_User();
	if (item_t->checkState(0) == Qt::Checked)
	{
		if (item_t->text(1) == "13") {
			init_UserWindow();
			ui->tableWidget->setItem(0, 0, new QTableWidgetItem(Account::sToq(user->getUserName())));
			ui->tableWidget->setItem(0, 1, new QTableWidgetItem(Account::sToq(user->getPassword())));
			ui->tableWidget->setItem(0, 2, new QTableWidgetItem(Account::sToq(user->getName())));
			ui->tableWidget->setItem(0, 3, new QTableWidgetItem(Account::sToq(user->getNumber())));
			ui->tableWidget->setItem(0, 4, new QTableWidgetItem(Account::sToq(user->getBalance(1))));
			ui->tableWidget->setItem(0, 5, new QTableWidgetItem(Account::sToq(user->getAddress())));
		}
		else if (item_t->text(1) == "14") {
			QMessageBox message(QMessageBox::NoIcon, "Tip", "当前余额： " + Account::sToq(to_string(user->getBalance())) + "元");
			message.exec();
		}
		else {
			init_GoodWindow();
			ui->tableWidget->setRowCount(LGoods.size());
			if (LGoods.empty())
			{
				QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递信息！ ");
				message.exec();
			}
			else
			{
				for (int i = 0; i < LGoods.size(); i++)
				{
					ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Account::sToq(LGoods[i].getExpressNumber())));
					ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Account::sToq(LGoods[i].getType(2))));
					ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Account::sToq(LGoods[i].getState(2))));
					ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(LGoods[i].getNumber())));
					ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Account::sToq(LGoods[i].getSendTime(1))));
					ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Account::sToq(LGoods[i].getCollectTime(1))));
					ui->tableWidget->setItem(i, 6, new QTableWidgetItem(Account::sToq(LGoods[i].getReceiveTime(1))));
					ui->tableWidget->setItem(i, 7, new QTableWidgetItem(Account::sToq(LGoods[i].getSender())));
					ui->tableWidget->setItem(i, 8, new QTableWidgetItem(Account::sToq(LGoods[i].getCourier())));
					ui->tableWidget->setItem(i, 9, new QTableWidgetItem(Account::sToq(LGoods[i].getRecipient())));
					ui->tableWidget->setItem(i, 10, new QTableWidgetItem(Account::sToq(LGoods[i].getDescribtion())));
					ui->tableWidget->setItem(i, 11, new QTableWidgetItem(Account::sToq(LGoods[i].getCompany())));
				}
			}
		}
		item_t->setCheckState(0, Qt::Unchecked);
	}
}
/*
* 账号充值
*/
void UserWindow::on_recharge_clicked()
{
	if (loginWindow->tag)
		init_User();
	// 输入对话框
	bool judge;
	// 获取整数
	double value = QInputDialog::getDouble(this, tr("充值栏"), tr("请充值："), 100,0, 1000, 10, &judge);
	if (judge)
		user->setBalance(user->getBalance() + value);
}
/*
* 修改账号信息
*/
void UserWindow::on_changeMessage_clicked()
{
	if (loginWindow->tag)
		init_User();
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("请输入:"));
	// 修改密码
	QString password = QString("新密码（8~16位）: ");
	QLineEdit* lineEdit1 = new QLineEdit(&dialog);
	lineEdit1->setEchoMode(QLineEdit::Password);
	lineEdit1->setText(Account::sToq(user->getPassword()));
	form.addRow(password, lineEdit1);
	//请确认新密码
	QLineEdit* lineEdit5 = new QLineEdit(&dialog);
	lineEdit5->setEchoMode(QLineEdit::Password);
	lineEdit5->setText(Account::sToq(user->getPassword()));
	form.addRow(password, lineEdit5);
	// 修改姓名
	QString name = QString("新姓名: ");
	QLineEdit* lineEdit2 = new QLineEdit(&dialog);
	lineEdit2->setText(Account::sToq(user->getName()));
	form.addRow(name, lineEdit2);
	//修改电话号码
	QString number = QString("新电话号码（11位）: ");
	QLineEdit* lineEdit3 = new QLineEdit(&dialog);
	lineEdit3->setText(Account::sToq(user->getNumber()));
	form.addRow(number, lineEdit3);
	//修改地址
	QString address = QString("新地址: ");
	QLineEdit* lineEdit4 = new QLineEdit(&dialog);
	lineEdit4->setText(Account::sToq(user->getAddress()));
	form.addRow(address, lineEdit4);
	// 添加OK键和Cancel键
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	// 当OK键被按下
	if (dialog.exec() == QDialog::Accepted) {
		if (lineEdit1->text() != lineEdit5->text())
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "两次密码不一致！！ ");
			message.exec();
		}
		else if (lineEdit1->text().size() > 16 || lineEdit1->text().size() < 8)
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "密码长度不符合规范 ！！");
			message.exec();
		}
		else if (11 != lineEdit3->text().size())
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "电话号码长度不符合规范 ！！");
			message.exec();
		}
		else {
			user->setPassword(Account::qTos(lineEdit1->text()));
			user->setName(Account::qTos(lineEdit2->text()));
			user->setNumber(Account::qTos(lineEdit3->text()));
			user->setAddress(Account::qTos(lineEdit4->text()));
			QMessageBox message(QMessageBox::NoIcon, "Tip", "修改成功！");
			message.exec();
		}
	}
}
/*
* 快递查询
*/
void UserWindow::on_check_Clicked(QTreeWidgetItem* item, int column)
{
	if (loginWindow->tag)
		init_User();
	if (item_t != item)
		item_t->setCheckState(0, Qt::Unchecked);//取消上个按钮的选中（避免多选）
	stringstream stream;
	int num;
	vector<Goods> goods;
	if (item->checkState(0) == Qt::Checked)
	{
		LGoods.clear();
		stream << Account::qTos(item->text(1));
		stream >> num;
		switch (num)
		{
		case 1://查询所有快递
		{
			for (auto s : user->getSend())
				LGoods.push_back(s);
			for (auto s : user->getReceive())
				LGoods.push_back(s);
		} break;
		case 3://根据快递编号查询快递
		{
			if (user->checkPacket(good, Account::qTos(ui->lineEdit->text()), user->getSend()) ||
				user->checkPacket(good, Account::qTos(ui->lineEdit->text()), user->getReceive()))
				LGoods.push_back(good);
		} break;
		case 5://根据寄件时间查询快递
		{
			goods.clear();
			array<int, 6> day = { 0 };
			day[0] = ui->year->value();
			day[1] = ui->month->value();
			day[2] = ui->day->value();
			if (user->checkPacket(goods, day, 1, user->getSend()) || user->checkPacket(goods, day, 1, user->getReceive()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 6: //根据揽收时间查询快递
		{
			goods.clear();
			array<int, 6> day = { 0 };
			day[0] = ui->year->value();
			day[1] = ui->month->value();
			day[2] = ui->day->value();
			if (user->checkPacket(goods, day, 3, user->getSend()) || user->checkPacket(goods, day, 3, user->getReceive()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 7://根据收件时间查询快递
		{
			goods.clear();
			array<int, 6> day = { 0 };
			day[0] = ui->year->value();
			day[1] = ui->month->value();
			day[2] = ui->day->value();
			if (user->checkPacket(goods, day, 2, user->getSend()) || user->checkPacket(goods, day, 2, user->getReceive()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 9://根据寄件人查询快递
		{
			goods.clear();
			if (user->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 1, user->getReceive()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 10: //根据快递员查询快递
		{
			goods.clear();
			if (user->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 3, user->getSend())||
				user->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 3, user->getReceive()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		}break;
		case 11: //根据收件人查询快递
		{
			goods.clear();
			if (user->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 2, user->getSend()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 12://查询未签收快递
		{
			goods.clear();
			if (user->checkPacket(goods, State::Unsign, user->getReceive()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		}
	}
	item_t = item;
}
/*
* 快递发送
*/
void UserWindow::on_sendExpress_clicked()
{
	if (loginWindow->tag)
		init_User();
	bool judge = false;//判断变量，检查收件人是否存在
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("请输入:"));
	// 设置快递类型
	QString type = QString("快递类型： ");
	QComboBox* combox1 = new QComboBox(&dialog);
	combox1->addItem("普通快递");
	combox1->addItem("书本");
	combox1->addItem("易碎品");
	form.addRow(type, combox1);
	//请输入物品描述
	QString description = QString("物品描述: ");
	QLineEdit* lineEdit1 = new QLineEdit(&dialog);
	form.addRow(description, lineEdit1);
	//修改电话号码
	QString name = QString("收件人用户名: ");
	QLineEdit* lineEdit2 = new QLineEdit(&dialog);
	form.addRow(name, lineEdit2);
	// 设置快递类型
	QString company = QString("快递公司： ");
	QComboBox* combox2 = new QComboBox(&dialog);
	combox2->addItem("顺丰");
	combox2->addItem("邮政");
	combox2->addItem("京东");
	combox2->addItem("韵达");
	combox2->addItem("申通");
	combox2->addItem("圆通");
	form.addRow(company, combox2);
	//输入商品量（本/kg)
	QString num = QString("快递重量/数量（不足1kg按1kg计算）： ");
	QLineEdit* lineEdit3 = new QLineEdit(&dialog);
	lineEdit3->setValidator(new QIntValidator(1, 100, this));
	form.addRow(num, lineEdit3);
	// 添加OK键和Cancel键
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	// 当OK键被按下
	if (dialog.exec() == QDialog::Accepted) 
	{
		for (int i = 0; i < userList.size(); i++)
			if (Account::qTos(lineEdit2 ->text())== userList[i])
			{
				judge = true;
				break;
			}
		if (!judge)
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "用户名不存在 ！！");
			message.exec();
		}
		else {
			Goods* good;
			string name;
			time_t currentTime = time(0);//获取当前系统时间
			stringstream stream;
			bool judge = false;
			int num = 0;
			switch (combox1->currentIndex())
			{
			case 0:
			{
				good = new Common(0);
			}break;
			case 1:
			{
				good = new Book(0);
			}break;
			case 2:
			{
				good = new Common(0);
			}break;
			}
			good->setSendTime(&currentTime);//根据系统时间确定快递编码
			good->setDecription(Account::qTos(lineEdit1->text()));//设置快递描述
			good->setRecipient(Account::qTos(lineEdit2->text()));//设置收件人
			good->setCompany(Account::qTos(combox2->currentText()));//设置承运公司
			stream << Account::qTos(lineEdit3->text());
			stream >> num;
			good->setNumber(num);//设置快递量
			good->setState(State::Uncollect);
			good->setSender(user->getUserName());
			good->setReceiveTime("0-0-0 0:0:0");
			good->setCollectTime("0-0-0 0:0:0");
			good->setCourier(" ");
			good->setExpressNumber(&currentTime);
			if (user->getBalance() < good->getPiece())
			{
				QMessageBox message(QMessageBox::NoIcon, "Tip", "余额不足 ！！");
				message.exec();
			}
			else
			{
				user->addSend(good);
				database->insertPackage(*good);
				database->addBalance(good->getCompany(), good->getPiece());//基类指针指向派生类对象调用函数
			}
		}
			
	}
}
/*
* 快递签收
*/
void UserWindow::on_signExpress_clicked()
{
	if (loginWindow->tag)
		init_User();
	if (user->checkPacket(good, Account::qTos(ui->lineEdit->text()), user->getReceive()))
	{
		if (good.getState() == State::Sign)
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "该快递已签收 ！！");
			message.exec();
		}
		else if (good.getState() == State::Uncollect)
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "该快递未揽收 ！！");
			message.exec();
		}
		else {
			good.signExpress();
			for (int i = 0; i < user->getReceive().size(); i++)
			{
				if (user->getReceive()[i].getExpressNumber() == good.getExpressNumber())//找到该快递在列表中的位置
				{
					user->setReceive(good, i);
				}
			}
			database->updatetPackage(good);
			QMessageBox message(QMessageBox::NoIcon, "Tip", "签收成功 ！！");
			message.exec();
		}
	}
	else {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "快递不存在 ！！");
		message.exec();
	}
}
/*
* 退出用户主界面
*/
void UserWindow::on_returnbotton_clicked()
{
	//this->hide();
	if (loginWindow->tag)
		init_User();
	user->saveUser();
	close();
	loginWindow->on_returnbotton_clicked();
}