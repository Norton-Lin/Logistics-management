#include "ManagerWindow.h"

ManagerWindow::ManagerWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::ManagerWindow)
{
	ui->setupUi(this);
	loginWindow = new ManagerLoginWindow();
	loginWindow->show();
	item_t = new QTreeWidgetItem;
	database = new Database();//�������ݿ�
	database->connectDatabase();
	manager->readAllUserName(tempList);//��ȡ�û����б�
	for (auto s : tempList)
		userList.emplace_back(manager->readUser(s));//��ȡ�����û���Ϣ
	tempList.clear();
	manager->readAllCourier(tempList, "0");
	for (auto s : tempList)//��ȡ�޹������Ա�б�
		courierList.emplace_back(manager->readCourier(s));
	auto f = [&]() {
		this->show();
		loginWindow->hide();
	};
	connect(loginWindow, &ManagerLoginWindow::sendLoginSuccess, this, f);
	connect(ui->pushButton, &QPushButton::clicked, this, &ManagerWindow::on_returnbotton_clicked);//�˳���ť������
	connect(ui->search, &QPushButton::clicked, this, &ManagerWindow::on_findAllMessage_clicked);//������ť������
	connect(ui->distribution, &QPushButton::clicked, this, &ManagerWindow::on_distribute_clicked);//��ݷ��䰴ť������
	connect(ui->addCourier, SIGNAL(clicked()), this, SLOT(on_addCourier_clicked), Qt::UniqueConnection);//��ӿ��Ա��ť������������������ƣ����ⵥ����������
	connect(ui->deleteCourier, SIGNAL(clicked()), this, SLOT(on_deleteCourier_clicked), Qt::UniqueConnection);//ɾ�����Ա��ť������������������ƣ����ⵥ����������
	//�����ʼ������飨����
	{
		QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget);
		topItem1->setText(0, "1.��ѯ���п����Ϣ");
		topItem1->setText(1, "1");
		topItem1->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem1);

		QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget);
		topItem2->setText(0, "2. ��ѯָ�������Ϣ");
		topItem2->setText(1, "2");
		ui->treeWidget->addTopLevelItem(topItem2);

		QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
		item21->setText(0, "2.1 ���ݿ�ݱ�Ų�ѯ");
		item21->setCheckState(0, Qt::Unchecked);
		item21->setText(1, "3");

		QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
		item22->setText(0, "2.2 ���ݿ��ʱ���ѯ");
		item22->setText(1, "4");

		QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
		item221->setText(0, "2.2.1 ���ݼļ�ʱ���ѯ");
		item221->setCheckState(0, Qt::Unchecked);
		item221->setText(1, "5");

		QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
		item222->setText(0, "2.2.2 ��������ʱ���ѯ");
		item222->setCheckState(0, Qt::Unchecked);
		item222->setText(1, "6");

		QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
		item223->setText(0, "2.2.3�����ռ�ʱ���ѯ");
		item223->setCheckState(0, Qt::Unchecked);
		item223->setText(1, "7");

		QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
		item23->setText(0, "2.3 �����û���ѯ");
		item23->setText(1, "8");

		QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
		item231->setText(0, "2.3.1���ݼļ��˲�ѯ");
		item231->setCheckState(0, Qt::Unchecked);
		item231->setText(1, "9");

		QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
		item232->setText(0, "2.3.2���ݿ��Ա��ѯ");
		item232->setCheckState(0, Qt::Unchecked);
		item232->setText(1, "10");

		QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
		item233->setText(0, "2.3.3�����ռ��˲�ѯ");
		item233->setCheckState(0, Qt::Unchecked);
		item233->setText(1, "11");

		QTreeWidgetItem* item24 = new QTreeWidgetItem(topItem2);
		item24->setText(0, "2.4 ���ݿ��״̬��ѯ");
		item24->setText(1, "12");

		QTreeWidgetItem* item241 = new QTreeWidgetItem(item24);
		item241->setText(0, "2.4.1 ��ѯ����δ���տ��");
		item241->setCheckState(0, Qt::Unchecked);
		item241->setText(1, "13");

		QTreeWidgetItem* item242 = new QTreeWidgetItem(item24);
		item242->setText(0, "2.4.2 ��ѯ����δǩ�տ��");
		item242->setCheckState(0, Qt::Unchecked);
		item242->setText(1, "14");

		QTreeWidgetItem* item243 = new QTreeWidgetItem(item24);
		item243->setText(0, "2.4.3 ��ѯ������ǩ�տ��");
		item243->setCheckState(0, Qt::Unchecked);
		item243->setText(1, "15");
		QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget);

		topItem3->setText(0, "3. ��ѯ�����û���Ϣ");
		topItem3->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem3);
		topItem3->setText(1, "16");

		QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
		topItem4->setText(0, "4. ��ѯָ���û���Ϣ");
		topItem4->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem4);
		topItem4->setText(1, "17");

		QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget);
		topItem5->setText(0, "5. ��ѯ���п��Ա��Ϣ");
		topItem5->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem5);
		topItem5->setText(1, "18");
		
		QTreeWidgetItem* topItem6 = new QTreeWidgetItem(ui->treeWidget);
		topItem6->setText(0, "6. ��ѯָ�����Ա��Ϣ");
		topItem6->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem6);
		topItem6->setText(1, "19");
		
		QTreeWidgetItem* topItem7 = new QTreeWidgetItem(ui->treeWidget);
		topItem7->setText(0, "7. ��ѯ���п���ӿ��Ա��Ϣ");
		topItem7->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem7);
		topItem7->setText(1, "20");

		QTreeWidgetItem* topItem8 = new QTreeWidgetItem(ui->treeWidget);
		topItem8->setText(0, "8. ��ѯ����Ա��Ϣ");
		topItem8->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem8);
		topItem8->setText(1, "21");

		QTreeWidgetItem* topItem9 = new QTreeWidgetItem(ui->treeWidget);
		topItem9->setText(0, "9. ��ѯ���");
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
		//��readAll��ȡĬ��֧�ֵ���ANSI��ʽ,�����С����creator�򿪱༭���˺ܿ��ܴ򲻿�
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
	manager = loginWindow->getManager();//����û���Ϣ
	manager->setPacket(database->findPackageByName(manager->getCompany(), 4));//��ȡ������˾�����Ϣ
	tempList.clear();
	manager->readAllCourier(tempList, manager->getCompany());
	for (auto s : tempList)//��ȡ��˾���¿��Ա�б�
		temp.emplace_back(manager->readCourier(s));
	manager->setCourier(temp);
	loginWindow->tag = false;
	ui->username->setText(Account::sToq(manager->getUserName()));
}
/*
* tableWidget �����ʾ�����ʼ��
*/
void ManagerWindow::init_GoodWindow()
{
	ui->tableWidget->setRowCount(1); //��������
	ui->tableWidget->setColumnCount(12); //��������
	QStringList header;
	header << "��ݵ���" << "�������" << "���״̬" << "������kg/����" << "����ʱ��" << "����ʱ��"
		<< "ǩ��ʱ��" << "�ļ���" << "���Ա" << "�ռ���" << "�������" << "���˹�˾";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*
* tableWidget �û���Ϣ��ʾ�����ʼ��
*/
void ManagerWindow::init_UserWindow()
{
	ui->tableWidget->setRowCount(1); //��������
	ui->tableWidget->setColumnCount(6); //��������
	QStringList header;
	header << "�û���" << "����" << "����" << "�绰����" << "��ַ" << "���";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*
* ����Ա��Ϣ��ʾ�����ʼ��
*/
void ManagerWindow::init_ManagerWindow()
{
	ui->tableWidget->setRowCount(1); //��������
	ui->tableWidget->setColumnCount(6); //��������
	QStringList header;
	header << "�û���" << "����" << "����" << "�绰����" << "��˾" << "���";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}
/*
* �����ѯ��Ϣ
*/
void ManagerWindow::on_findAllMessage_clicked()
{
	if (loginWindow->tag)
		init_Manager();
	if (item_t->checkState(0) == Qt::Checked)
	{
		stringstream stream;
		int choice;//ѡ��
		stream << Account::qTos(item_t->text(1));
		stream >> choice;

		if (choice <= 15)
		{
			init_GoodWindow();
			ui->tableWidget->setRowCount(LGoods.size());
			if (LGoods.empty())
			{
				QMessageBox message(QMessageBox::NoIcon, "Tip", "�޿����Ϣ�� ");
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
				QMessageBox message(QMessageBox::NoIcon, "Tip", "���û���Ϣ�� ");
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
				QMessageBox message(QMessageBox::NoIcon, "Tip", "�޿��Ա��Ϣ�� ");
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
			QMessageBox message(QMessageBox::NoIcon, "Tip", "��ǰ�� " + Account::sToq(to_string(manager->getBalance())) + "Ԫ");
			message.exec();
		}
		item_t->setCheckState(0, Qt::Unchecked);
	}
}
/*
* ����������
*/
void ManagerWindow::on_distribute_clicked()
{
	if (loginWindow->tag)
		init_Manager();
	
}
/*
* ��ѯ������Ϣ
* ֧�ֲ�ѯ �����Ϣ���û���Ϣ�����Ա��Ϣ���˺���Ϣ�����
*/
void ManagerWindow::on_check_Clicked(QTreeWidgetItem* item, int column)
{
	if (loginWindow->tag)
		init_Manager();
	if (item_t != item)
		item_t->setCheckState(0, Qt::Unchecked);//ȡ���ϸ���ť��ѡ�У������ѡ��
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
		case 1://��ѯ���п��
		{
			for (auto s : manager->getPacket())
				LGoods.push_back(s);
		} break;
		case 3://���ݿ�ݱ�Ų�ѯ���
		{
			Goods good;
			if (manager->checkPacket(good, Account::qTos(ui->lineEdit->text()), manager->getPacket()))
				LGoods.push_back(good);
		} break;
		case 5://���ݼļ�ʱ���ѯ���
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
		case 6: //��������ʱ���ѯ���
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
		case 7://�����ռ�ʱ���ѯ���
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
		case 9://���ݼļ��˲�ѯ���
		{
			goods.clear();
			if (manager->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 1, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 10: //���ݿ��Ա��ѯ���
		{
			goods.clear();
			if (manager->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 3, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		}break;
		case 11: //�����ռ��˲�ѯ���
		{
			goods.clear();
			if (manager->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 2, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 13://��ѯδ���տ��
		{
			goods.clear();
			if (manager->checkPacket(goods, State::Uncollect, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		case 14://��ѯδǩ�տ��
		{
			goods.clear();
			if (manager->checkPacket(goods, State::Unsign, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		case 15://��ѯ��ǩ�տ��
		{
			goods.clear();
			if (manager->checkPacket(goods, State::Sign, manager->getPacket()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		}break;
		case 16://��ѯ�����û�
		{
			LUser.clear();
			for (auto s : userList)
				LUser.push_back(s);
		}break;
		case 17://��ѯָ���û�
		{
			LUser.clear();
			for (auto s : userList)
			{
				if(Account::sToq(s.getUserName())==ui->lineEdit->text())
				      LUser.push_back(s);
			}
		}break;
		case 18://��ѯ�������п��Ա
		{
			LCourier.clear();
			for (auto s : manager->getCourier())
				LCourier.push_back(s);
		}break;	
		case 19://��ѯָ�����Ա
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
		case 20://��ѯ�����������Ա
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
* ��ӿ��Ա
*/
void ManagerWindow::on_addCourier_clicked()
{
	bool judge = false;
	for (int i = 0; i < courierList.size(); i++)
	{
		if (Account::qTos(ui->lineEdit->text()) == courierList[i].getUserName())
		{
			manager->addCourier(courierList[i]);//����빫˾���¿��Ա
			courierList.erase(courierList.begin() + i);//�������б���ɾ��
			judge = true;
			break;
		}
	}
	if (judge) {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "���Ա��ӳɹ�����");
		message.exec();
	}
	else{
		QMessageBox message(QMessageBox::NoIcon, "Tip", "���Ա������ ����");
		message.exec();
	}
}
/*
* ɾ�����Ա
*/
void ManagerWindow::on_deleteCourier_clicked()
{
	bool judge = false;
	for (int i = 0; i < manager->getCourier().size(); i++)
	{
		if (Account::qTos(ui->lineEdit->text()) == manager->getCourier()[i].getUserName())
		{
			courierList.emplace_back(manager->decCourier(i));//������������Ա,�ӹ�˾���Ա�б���ɾ��
			judge = true;
			break;
		}
	}
	if (judge) {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "���Աɾ���ɹ�����");
		message.exec();
	}
	else {
		QMessageBox message(QMessageBox::NoIcon, "Tip", "���Ա������ ����");
		message.exec();
	}
}
/*
* �˳��û�������
*/
void ManagerWindow::on_returnbotton_clicked()
{
	//this->hide();
	if (loginWindow->tag)
		init_Manager();
	manager->saveAllCourier(manager->getCompany(), manager->getCourier());//�洢��˾���¿��Ա��Ϣ
	manager->saveAllCourier("0", courierList);//�洢�������Ա��Ϣ
	close();
	loginWindow->on_returnbotton_clicked();
}

