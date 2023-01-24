#include "CourierWindow.h"
CourierWindow::CourierWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CourierWindow)
{
	ui->setupUi(this);
	ui->widget->setFixedSize(2000, 1200);
	loginWindow = new CourierLoginWindow();
	loginWindow->show();
	item_t = new QTreeWidgetItem;
	database = new Database();
	database->connectDatabase();
	//lamda表达式m
	auto f = [&]() {
		this->show();
		loginWindow->hide();
	};
	connect(loginWindow, &CourierLoginWindow::sendLoginSuccess, this, f);
	connect(ui->pushButton, &QPushButton::clicked, this, &CourierWindow::on_returnbotton_clicked);//退出按钮槽连接
	connect(ui->search, &QPushButton::clicked, this, &CourierWindow::on_findAllMessage_clicked);//搜索按钮槽连接
	connect(ui->collect, &QPushButton::clicked, this, &CourierWindow::on_collectExpress_clicked);//快递揽收按钮槽连接
	connect(ui->changeMessage, &QPushButton::clicked, this, &CourierWindow::on_changeMessage_clicked);//修改信息按钮槽连接
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
		topItem3->setText(0, "3. 查询账号信息");
		topItem3->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem3);
		topItem3->setText(1, "16");

		QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
		topItem4->setText(0, "4. 查询余额");
		topItem4->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem4);
		topItem4->setText(1, "17");
		connect(ui->treeWidget, &QTreeWidget::itemClicked, this,
			&CourierWindow::on_check_Clicked);
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

CourierWindow::~CourierWindow()
{
}

void CourierWindow::init_Courier()
{
	courier = loginWindow->getCourier();//获得用户信息
	courier->setAssigned(database->findPackageByName(courier->getUserName(), 3));//获取名下快递
	loginWindow->tag = false;
	ui->username->setText(Account::sToq(courier->getUserName()));
}

void CourierWindow::init_GoodWindow()
{
	ui->tableWidget->setRowCount(1); //设置行数
	ui->tableWidget->setColumnCount(12); //设置列数
	QStringList header;
	header << "快递单号" << "快递类型" << "快递状态" << "数量（kg/本）" << "发送时间" << "揽收时间"
		<< "签收时间" << "寄件人" << "快递员" << "收件人" << "快递描述" << "承运公司";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}

void CourierWindow::init_CourierWindow()
{
	ui->tableWidget->setRowCount(1); //设置行数
	ui->tableWidget->setColumnCount(6); //设置列数
	QStringList header;
	header << "用户名" << "密码" << "姓名" << "电话号码" << "公司" << "余额";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}

void CourierWindow::on_findAllMessage_clicked()
{
	if (loginWindow->tag)
		init_Courier();
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
		else if (choice == 16) {
			init_CourierWindow();
			ui->tableWidget->setItem(0, 0, new QTableWidgetItem(Account::sToq(courier->getUserName())));
			ui->tableWidget->setItem(0, 1, new QTableWidgetItem(Account::sToq(courier->getPassword())));
			ui->tableWidget->setItem(0, 2, new QTableWidgetItem(Account::sToq(courier->getName())));
			ui->tableWidget->setItem(0, 3, new QTableWidgetItem(Account::sToq(courier->getNumber())));
			ui->tableWidget->setItem(0, 4, new QTableWidgetItem(Account::sToq(courier->getCompany())));
			ui->tableWidget->setItem(0, 5, new QTableWidgetItem(Account::sToq(courier->getBalance(1))));
		}
		else {
			QMessageBox message(QMessageBox::NoIcon, "Tip", "当前余额： " + Account::sToq(to_string(courier->getBalance())) + "元");
			message.exec();
		}
		item_t->setCheckState(0, Qt::Unchecked);
	}
}
/*
* 账号信息修改
*/
void CourierWindow::on_changeMessage_clicked()
{
	if (loginWindow->tag)
		init_Courier();
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("请输入:"));
	// 修改密码
	QString password = QString("新密码（8~16位）: ");
	QLineEdit* lineEdit1 = new QLineEdit(&dialog);
	lineEdit1->setEchoMode(QLineEdit::Password);
	lineEdit1->setText(Account::sToq(courier->getPassword()));
	form.addRow(password, lineEdit1);
	//请确认新密码
	QLineEdit* lineEdit5 = new QLineEdit(&dialog);
	lineEdit5->setEchoMode(QLineEdit::Password);
	lineEdit5->setText(Account::sToq(courier->getPassword()));
	form.addRow(password, lineEdit5);
	// 修改姓名
	QString name = QString("新姓名: ");
	QLineEdit* lineEdit2 = new QLineEdit(&dialog);
	lineEdit2->setText(Account::sToq(courier->getName()));
	form.addRow(name, lineEdit2);
	//修改电话号码
	QString number = QString("新电话号码（11位）: ");
	QLineEdit* lineEdit3 = new QLineEdit(&dialog);
	lineEdit3->setText(Account::sToq(courier->getNumber()));
	form.addRow(number, lineEdit3);
	//公司和余额不可修改
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
			courier->setPassword(Account::qTos(lineEdit1->text()));
			courier->setName(Account::qTos(lineEdit2->text()));
			courier->setNumber(Account::qTos(lineEdit3->text()));
			QMessageBox message(QMessageBox::NoIcon, "Tip", "修改成功！");
			message.exec();
		}
	}
}
/*
* 查询所有信息
* 支持查询 快递信息，账号信息，余额
*/
void CourierWindow::on_check_Clicked(QTreeWidgetItem* item, int column)
{
	if (loginWindow->tag)
		init_Courier();
	if(item_t!=item)
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
			for (auto s : courier->getAssigned())
				LGoods.push_back(s);
		} break;
		case 3://根据快递编号查询快递
		{
			Goods good;
			if (courier->checkPacket(good, Account::qTos(ui->lineEdit->text()), courier->getAssigned()))
				LGoods.push_back(good);
		} break;
		case 5://根据寄件时间查询快递
		{
			goods.clear();
			array<int, 6> day = { 0 };
			day[0] = ui->year->value();
			day[1] = ui->month->value();
			day[2] = ui->day->value();
			if (courier->checkPacket(goods, day, 1, courier->getAssigned()))
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
			if (courier->checkPacket(goods, day, 3, courier->getAssigned()))
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
			if (courier->checkPacket(goods, day, 2, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 9://根据寄件人查询快递
		{
			goods.clear();
			if (courier->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 1, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 10: //根据快递员查询快递
		{
			goods.clear();
			if (courier->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 3, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 11: //根据收件人查询快递
		{
			goods.clear();
			if (courier->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 2, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 13://查询未揽收快递
		{
			goods.clear();
			if (courier->checkPacket(goods, State::Uncollect, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		} break;
		case 14://查询未签收快递
		{
			goods.clear();
			if (courier->checkPacket(goods, State::Unsign, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		} break;
		case 15://查询已签收快递
		{
			goods.clear();
			if (courier->checkPacket(goods, State::Sign, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		} break;
		}
	}
	item_t = item;
}
/*
* 快递揽收
*/
void CourierWindow::on_collectExpress_clicked()
{
	if (loginWindow->tag)
		init_Courier();
	Goods good;
	double money;//运费
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("请输入:"));
	// 设置快递类型
	QString expressNumber = QString("快递单号： ");
	QLineEdit* lineEdit = new QLineEdit(&dialog);
	form.addRow(expressNumber, lineEdit);
	// 添加OK键和Cancel键
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	// 当OK键被按下
	if (dialog.exec() == QDialog::Accepted)
	{
		if (courier->findPacket(courier->getAssigned(), Account::qTos(lineEdit->text()), good))
		{
			if (good.getState() == State::Uncollect)
			{
				courier->collectExpress(good, money);//揽收快递
				for (int i = 0; i < courier->getAssigned().size(); i++)
				{
					if (good.getExpressNumber() == courier->getAssigned()[i].getExpressNumber())
					{
						courier->setPacket(good, i);
						database->updatetPackage(good);
						database->addBalance(courier->getCompany(), (-1) * money);
					}
				}
			}
			else {
				QMessageBox message(QMessageBox::NoIcon, "Tip", "快递已揽收 ！！");
				message.exec();
			}
		}
		else {
			QMessageBox message(QMessageBox::NoIcon, "Tip", "快递不存在 ！！");
			message.exec();
		}
	}
}
/*
* 退出快递员主界面
*/
void CourierWindow::on_returnbotton_clicked()
{
	//this->hide();
	if (loginWindow->tag)
		init_Courier();
	courier->saveCourier();
	close();
	loginWindow->on_returnbotton_clicked();
}