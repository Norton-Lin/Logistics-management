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
	//lamda���ʽm
	auto f = [&]() {
		this->show();
		loginWindow->hide();
	};
	connect(loginWindow, &CourierLoginWindow::sendLoginSuccess, this, f);
	connect(ui->pushButton, &QPushButton::clicked, this, &CourierWindow::on_returnbotton_clicked);//�˳���ť������
	connect(ui->search, &QPushButton::clicked, this, &CourierWindow::on_findAllMessage_clicked);//������ť������
	connect(ui->collect, &QPushButton::clicked, this, &CourierWindow::on_collectExpress_clicked);//������հ�ť������
	connect(ui->changeMessage, &QPushButton::clicked, this, &CourierWindow::on_changeMessage_clicked);//�޸���Ϣ��ť������
	ui->treeWidget->setColumnCount(1);//һ��
	ui->treeWidget->clear();
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
		topItem3->setText(0, "3. ��ѯ�˺���Ϣ");
		topItem3->setCheckState(0, Qt::Unchecked);
		ui->treeWidget->addTopLevelItem(topItem3);
		topItem3->setText(1, "16");

		QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
		topItem4->setText(0, "4. ��ѯ���");
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
		//��readAll��ȡĬ��֧�ֵ���ANSI��ʽ,�����С����creator�򿪱༭���˺ܿ��ܴ򲻿�
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
	courier = loginWindow->getCourier();//����û���Ϣ
	courier->setAssigned(database->findPackageByName(courier->getUserName(), 3));//��ȡ���¿��
	loginWindow->tag = false;
	ui->username->setText(Account::sToq(courier->getUserName()));
}

void CourierWindow::init_GoodWindow()
{
	ui->tableWidget->setRowCount(1); //��������
	ui->tableWidget->setColumnCount(12); //��������
	QStringList header;
	header << "��ݵ���" << "�������" << "���״̬" << "������kg/����" << "����ʱ��" << "����ʱ��"
		<< "ǩ��ʱ��" << "�ļ���" << "���Ա" << "�ռ���" << "�������" << "���˹�˾";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}

void CourierWindow::init_CourierWindow()
{
	ui->tableWidget->setRowCount(1); //��������
	ui->tableWidget->setColumnCount(6); //��������
	QStringList header;
	header << "�û���" << "����" << "����" << "�绰����" << "��˾" << "���";
	ui->tableWidget->setHorizontalHeaderLabels(header);
}

void CourierWindow::on_findAllMessage_clicked()
{
	if (loginWindow->tag)
		init_Courier();
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
			QMessageBox message(QMessageBox::NoIcon, "Tip", "��ǰ�� " + Account::sToq(to_string(courier->getBalance())) + "Ԫ");
			message.exec();
		}
		item_t->setCheckState(0, Qt::Unchecked);
	}
}
/*
* �˺���Ϣ�޸�
*/
void CourierWindow::on_changeMessage_clicked()
{
	if (loginWindow->tag)
		init_Courier();
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("������:"));
	// �޸�����
	QString password = QString("�����루8~16λ��: ");
	QLineEdit* lineEdit1 = new QLineEdit(&dialog);
	lineEdit1->setEchoMode(QLineEdit::Password);
	lineEdit1->setText(Account::sToq(courier->getPassword()));
	form.addRow(password, lineEdit1);
	//��ȷ��������
	QLineEdit* lineEdit5 = new QLineEdit(&dialog);
	lineEdit5->setEchoMode(QLineEdit::Password);
	lineEdit5->setText(Account::sToq(courier->getPassword()));
	form.addRow(password, lineEdit5);
	// �޸�����
	QString name = QString("������: ");
	QLineEdit* lineEdit2 = new QLineEdit(&dialog);
	lineEdit2->setText(Account::sToq(courier->getName()));
	form.addRow(name, lineEdit2);
	//�޸ĵ绰����
	QString number = QString("�µ绰���루11λ��: ");
	QLineEdit* lineEdit3 = new QLineEdit(&dialog);
	lineEdit3->setText(Account::sToq(courier->getNumber()));
	form.addRow(number, lineEdit3);
	//��˾�������޸�
	// ���OK����Cancel��
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	// ��OK��������
	if (dialog.exec() == QDialog::Accepted) {
		if (lineEdit1->text() != lineEdit5->text())
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "�������벻һ�£��� ");
			message.exec();
		}
		else if (lineEdit1->text().size() > 16 || lineEdit1->text().size() < 8)
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "���볤�Ȳ����Ϲ淶 ����");
			message.exec();
		}
		else if (11 != lineEdit3->text().size())
		{
			QMessageBox message(QMessageBox::NoIcon, "Tip", "�绰���볤�Ȳ����Ϲ淶 ����");
			message.exec();
		}
		else {
			courier->setPassword(Account::qTos(lineEdit1->text()));
			courier->setName(Account::qTos(lineEdit2->text()));
			courier->setNumber(Account::qTos(lineEdit3->text()));
			QMessageBox message(QMessageBox::NoIcon, "Tip", "�޸ĳɹ���");
			message.exec();
		}
	}
}
/*
* ��ѯ������Ϣ
* ֧�ֲ�ѯ �����Ϣ���˺���Ϣ�����
*/
void CourierWindow::on_check_Clicked(QTreeWidgetItem* item, int column)
{
	if (loginWindow->tag)
		init_Courier();
	if(item_t!=item)
	    item_t->setCheckState(0, Qt::Unchecked);//ȡ���ϸ���ť��ѡ�У������ѡ��
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
		case 1://��ѯ���п��
		{
			for (auto s : courier->getAssigned())
				LGoods.push_back(s);
		} break;
		case 3://���ݿ�ݱ�Ų�ѯ���
		{
			Goods good;
			if (courier->checkPacket(good, Account::qTos(ui->lineEdit->text()), courier->getAssigned()))
				LGoods.push_back(good);
		} break;
		case 5://���ݼļ�ʱ���ѯ���
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
		case 6: //��������ʱ���ѯ���
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
		case 7://�����ռ�ʱ���ѯ���
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
		case 9://���ݼļ��˲�ѯ���
		{
			goods.clear();
			if (courier->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 1, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 10: //���ݿ��Ա��ѯ���
		{
			goods.clear();
			if (courier->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 3, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 11: //�����ռ��˲�ѯ���
		{
			goods.clear();
			if (courier->checkPacket(goods, Account::qTos(ui->lineEdit->text()), 2, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}
		} break;
		case 13://��ѯδ���տ��
		{
			goods.clear();
			if (courier->checkPacket(goods, State::Uncollect, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		} break;
		case 14://��ѯδǩ�տ��
		{
			goods.clear();
			if (courier->checkPacket(goods, State::Unsign, courier->getAssigned()))
			{
				for (auto s : goods)
					LGoods.push_back(s);
			}

		} break;
		case 15://��ѯ��ǩ�տ��
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
* �������
*/
void CourierWindow::on_collectExpress_clicked()
{
	if (loginWindow->tag)
		init_Courier();
	Goods good;
	double money;//�˷�
	QDialog dialog(this);
	QFormLayout form(&dialog);
	form.addRow(new QLabel("������:"));
	// ���ÿ������
	QString expressNumber = QString("��ݵ��ţ� ");
	QLineEdit* lineEdit = new QLineEdit(&dialog);
	form.addRow(expressNumber, lineEdit);
	// ���OK����Cancel��
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	// ��OK��������
	if (dialog.exec() == QDialog::Accepted)
	{
		if (courier->findPacket(courier->getAssigned(), Account::qTos(lineEdit->text()), good))
		{
			if (good.getState() == State::Uncollect)
			{
				courier->collectExpress(good, money);//���տ��
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
				QMessageBox message(QMessageBox::NoIcon, "Tip", "��������� ����");
				message.exec();
			}
		}
		else {
			QMessageBox message(QMessageBox::NoIcon, "Tip", "��ݲ����� ����");
			message.exec();
		}
	}
}
/*
* �˳����Ա������
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