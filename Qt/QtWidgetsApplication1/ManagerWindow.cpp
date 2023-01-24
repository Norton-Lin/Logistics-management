#include "ManagerWindow.h"

ManagerWindow::ManagerWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ManagerWindow)
{
	ui->setupUi(this);
	loginWindow = new ManagerLoginWindow();
	loginWindow->show();
	item_t = new QTreeWidgetItem;
	database = new Database();//连接数据库
	database->connectDatabase();
	manager->readAllUserName(tempList);//读取用户名列表
	for (auto s : tempList)
		userList.emplace_back(manager->readUser(s));//读取所有用户信息
	tempList.clear();
	manager->readAllCourier(tempList, "0");
	for (auto s : tempList)//读取无归属快递员列表
		courierList.emplace_back(manager->readCourier(s));
	auto f = [&]() {
		this->show();
		loginWindow->hide();
	};
	connect(loginWindow, &ManagerLoginWindow::sendLoginSuccess, this, f);
	connect(ui->pushButton, &QPushButton::clicked, this, &ManagerWindow::on_returnbotton_clicked);//退出按钮槽连接
	connect(ui->search, &QPushButton::clicked, this, &ManagerWindow::on_findAllMessage_clicked);//搜索按钮槽连接
	connect(ui->distribution, &QPushButton::clicked, this, &ManagerWindow::on_distribute_clicked);//快递分配按钮槽连接
	connect(ui->addCourier, SIGNAL(clicked()), this, SLOT(on_addCourier_clicked), Qt::UniqueConnection);//添加快递员按钮，第五个参数用于限制，避免单击触发两次
	connect(ui->deleteCourier, SIGNAL(clicked()), this, SLOT(on_deleteCourier_clicked), Qt::UniqueConnection);//删除快递员按钮，第五个参数用于限制，避免单击触发两次
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

		QTreeWidgetItem* item24 = new QTreeWidgetItem(topItem2);
		item24->setText(0, "2.4 根据快递状态查询");
		item24->setText(1, "12");

		QTreeWidgetItem* item241 = new QTreeWidgetItem(item24);
		item241->setText(0, "2.4.1 查询所有未揽收快递");
		item241->setCheckState(0, Qt::Unchecked);
		item241->setText(1, "13");

		QTreeWidgetItem* item242 = new QTreeWidgetItem(item24);
		item242->setText(0, "2.4.2 查询所有未签收快递");
		item242->setCheckState(0, Qt::Unchecked);
		item242->setText(1, "14");

		QTreeWidgetItem* item243 = new QTreeWidgetItem(item24);
		item243->setText(0, "2.4.3 查询所有已签收快递");
		item243->setCheckState(0, Qt::Unchecked);
		item243->setText(1, "15");
		QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget);

		topItem3->setText(0, "3. 查询所有用户信息");
		topItem3->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem3);
		topItem3->setText(1, "16");

		QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
		topItem4->setText(0, "4. 查询指定用户信息");
		topItem4->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem4);
		topItem4->setText(1, "17");

		QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget);
		topItem5->setText(0, "5. 查询所有快递员信息");
		topItem5->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem5);
		topItem5->setText(1, "18");
		
		QTreeWidgetItem* topItem6 = new QTreeWidgetItem(ui->treeWidget);
		topItem6->setText(0, "6. 查询指定快递员信息");
		topItem6->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem6);
		topItem6->setText(1, "19");
		
		QTreeWidgetItem* topItem7 = new QTreeWidgetItem(ui->treeWidget);
		topItem7->setText(0, "7. 查询所有可添加快递员信息");
		topItem7->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem7);
		topItem7->setText(1, "20");

		QTreeWidgetItem* topItem8 = new QTreeWidgetItem(ui->treeWidget);
		topItem8->setText(0, "8. 查询管理员信息");
		topItem8->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem8);
		topItem8->setText(1, "21");

		QTreeWidgetItem* topItem9 = new QTreeWidgetItem(ui->treeWidget);
		topItem9->setText(0, "9. 查询余额");
		topItem9->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem9);
		topItem9->setText(1, "22");
		connect(ui->treeWidget, &QTreeWidget::itemClicked, this,
			&ManagerWindow::on_check_Clicked);
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

ManagerWindow::~ManagerWindow()
{
}

void ManagerWindow::init_Manager()
{
	vector<Courier> temp;
	manager = loginWindow->getManager();//获得用户信息
	manager->setPacket(database->findPackageByName(manager->getCompany(), 4));//读取物流公司快递信息
	tempList.clear();
	manager->readAllCourier(tempList, manager->getCompany());
	for (auto s : tempList)//读取公司名下快递员列表
		temp.emplace_back(manager->readCourier(s));
	manager->setCourier(temp);
	loginWindow->tag = false;
	ui->username->setText(Account::sToq(manager->getUserName()));
}
/*
* tableWidget 快递显示界面初始化
*/
void ManagerWindow::init_GoodWindow()
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
void ManagerWindow::init_UserWindow()
{
	ui->tableWidget->setRowCount(1); //设置行数
	ui->tableWidget->setColumnCount(6); //设置列数
	QStringList header;
	header << "用户名" << "密码" << "姓名" << "电话号码" << "地址" << "余额";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*
* 管理员信息显示界面初始化
*/
void ManagerWindow::init_ManagerWindow()
{
	ui->tableWidget->setRowCount(1); //设置行数
	ui->tableWidget->setColumnCount(6); //设置列数
	QStringList header;
	header << "用户名" << "密码" << "姓名" << "电话号码" << "公司" << "余额";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*
* 输出查询信息
*/
void ManagerWindow::on_findAllMessage_clicked()
{
	if (loginWindow->tag)
		init_Manager();
	if (item_t->checkState(0) == Qt::Checked)
	{
		stringstream stream;
		int choice;//选择
		stream << Account::qTos(item_t->text(1));
		stream >> choice;

		if (choice <= 15)
		{
			init_GoodWindow();
			ui->tableWidget->setRowCount(LGoods.size());
			if (LGoods.empty())
			{
				QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递信息！ ");
				message.exec();
			}
			else {
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
		else if (choice <= 17) {
			init_UserWindow();
			ui->tableWidget->setRowCount(LUser.size());
			if (LUser.empty()) {
				QMessageBox message(QMessageBox::NoIcon, "Tip", "无用户信息！ ");
				message.exec();
			}
			else {
				for (int i = 0; i < LUser.size(); i++) {
					ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Account::sToq(LUser[i].getUserName())));
					ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Account::sToq(LUser[i].getPassword())));
					ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Account::sToq(LUser[i].getName())));
					ui->tableWidget->setItem(i, 3, new QTableWidgetItem(Account::sToq(LUser[i].getNumber())));
					ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Account::sToq(LUser[i].getAddress())));
					ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Account::sToq(LUser[i].getBalance(1))));
				}
			}
		}
		else if (choice <= 20) {
			init_ManagerWindow();
			ui->tableWidget->setRowCount(LCourier.size());
			if (LCourier.empty()) {
				QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递员信息！ ");
				message.exec();
			}
			else {
				for (int i = 0; i < LCourier.size(); i++) {
					ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Account::sToq(LCourier[i].getUserName())));
					ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Account::sToq(LCourier[i].getPassword())));
					ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Account::sToq(LCourier[i].getName())));
					ui->tableWidget->setItem(i, 3, new QTableWidgetItem(Account::sToq(LCourier[i].getNumber())));
					ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Account::sToq(LCourier[i].getCompany())));
					ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Account::sToq(LCourier[i].getBalance(1))));
				}
			}
		}
		else if (choice == 21) {
			init_ManagerWindow();
			ui->tableWidget->setItem(0, 0, new QTableWidgetItem(Account::sToq(manager->getUserName())));
			ui->tableWidget->setItem(0, 1, new QTableWidgetItem(Account::sToq(manager->getPassword())));
			ui->tableWidget->setItem(0, 2, new QTableWidgetItem(Account::sToq(manager->getName())));
			ui->tableWidget->setItem(0, 3, new QTableWidgetItem(Account::sToq(manager->getNumber())));
			ui->tableWidget->setItem(0, 4, new QTableWidgetItem(Account::sToq(manager->getCompany())));
			ui->tableWidget->setItem(0, 5, new QTableWidgetItem(Account::sToq(manager->getBalance(1))));
		}
		else {
			QMessageBox message(QMessageBox::NoIcon, "Tip", "当前余额： " + Account::sToq(to_string(manager->getBalance())) + "元");
			message.exec();
		}
		item_t->setCheckState(0, Qt::Unchecked);
	}
}
/*
* 快递任务分配
*/
void ManagerWindow::on_distribute_clicked()
{
	if (loginWindow->tag)
		init_Manager();
	
}
/*
* 查询所有信息
* 支持查询 快递信息，用户信息，快递员信息，账号信息，余额
*/
void ManagerWindow::on_check_Clicked(QTreeWidgetItem* item, int column)
{
	if (loginWindow->tag)
		init_Manager();
	if (item_t != item)
		item_t->setCheckState(0, Qt::Unchecked);//取消上个按钮的选中（避免多选）
	stringstream stream;
	int num;
	vector<Goods> goods;
	if (item->checkState(0) == Qt::Checked)
	{
		LGoods.clear();
		LUser.clear();
		LCourier.clear();
		stream << Account::qTos(item->text(1));
		stream >> num;
		switch (num)
		{
		case 1://查询所有快递
		{
			for (auto s : manager->getPacket())
				LGoods.push_back(s);
		} break;
		case 3://根据快递编号查询快递
		{
			Goods good;
			if (manager->checkPacket(good, Account::qTos(ui->lineEdit->text()), manager->getPacket()))
				LGoods.push_back(good);
		} break;
		case 5://根据寄件时间查询快递
		{
			goods.clear();
			array<int, 6> day = { 0 };
			day[0] = ui->year->value();
			day[1] = ui->month->value();
			day[2] = ui->day->value();
			if (manager->checkPacket(goods, day, 1, manager->getPacket()))
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
			if (manager->checkPacket(goods, day, 3, manager->getPacket()))
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
			if (manager->checkPacket(goods, day, 2, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 9://根据寄件人查询快递
		{
			goods.clear();
			if (manager->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 1, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 10: //根据快递员查询快递
		{
			goods.clear();
			if (manager->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 3, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		}break;
		case 11: //根据收件人查询快递
		{
			goods.clear();
			if (manager->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 2, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 13://查询未揽收快递
		{
			goods.clear();
			if (manager->checkPacket(goods, State::Uncollect, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		case 14://查询未签收快递
		{
			goods.clear();
			if (manager->checkPacket(goods, State::Unsign, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		case 15://查询已签收快递
		{
			goods.clear();
			if (manager->checkPacket(goods, State::Sign, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		case 16://查询所有用户
		{
			LUser.clear();
			for (auto s : userList)
				LUser.push_back(s);
		}break;
		case 17://查询指定用户
		{
			LUser.clear();
			for (auto s : userList)
			{
				if(Account::sToq(s.getUserName())==ui->lineEdit->text())
				      LUser.push_back(s);
			}
		}break;
		case 18://查询名下所有快递员
		{
			LCourier.clear();
			for (auto s : manager->getCourier())
				LCourier.push_back(s);
		}break;	
		case 19://查询指定快递员
		{
			LCourier.clear();
			for (auto s : manager->getCourier())
			{
				if(Account::sToq(s.getUserName()) == ui->lineEdit->text())
				LCourier.push_back(s);
			}
			for (auto s : courierList)
			{
				if (Account::sToq(s.getUserName()) == ui->lineEdit->text())
				LCourier.push_back(s);
			}
		}break;
		case 20://查询所有无属快递员
		{
			LCourier.clear();
			for (auto s : courierList)
				LCourier.push_back(s);
		}break;
		}
	}
	item_t = item;
}
/*
* 添加快递员
*/
void ManagerWindow::on_addCourier_clicked()
{
	bool judge = false;
	for (int i = 0; i < courierList.size(); i++)
	{
		if (Account::qTos(ui->lineEdit->text()) == courierList[i].getUserName())
		{
			manager->addCourier(courierList[i]);//添加入公司名下快递员
			courierList.erase(courierList.begin() + i);//从无属列表中删除
			judge = true;
			break;
		}
	}
	if (judge) {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "快递员添加成功！！");
		message.exec();
	}
	else{
		QMessageBox message(QMessageBox::NoIcon, "Tip", "快递员不存在 ！！");
		message.exec();
	}
}
/*
* 删除快递员
*/
void ManagerWindow::on_deleteCourier_clicked()
{
	bool judge = false;
	for (int i = 0; i < manager->getCourier().size(); i++)
	{
		if (Account::qTos(ui->lineEdit->text()) == manager->getCourier()[i].getUserName())
		{
			courierList.emplace_back(manager->decCourier(i));//添加入无属快递员,从公司快递员列表中删除
			judge = true;
			break;
		}
	}
	if (judge) {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "快递员删除成功！！");
		message.exec();
	}
	else {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "快递员不存在 ！！");
		message.exec();
	}
}
/*
* 退出用户主界面
*/
void ManagerWindow::on_returnbotton_clicked()
{
	//this->hide();
	if (loginWindow->tag)
		init_Manager();
	manager->saveAllCourier(manager->getCompany(), manager->getCourier());//存储公司名下快递员信息
	manager->saveAllCourier("0", courierList);//存储无主快递员信息
	close();
	loginWindow->on_returnbotton_clicked();
}

