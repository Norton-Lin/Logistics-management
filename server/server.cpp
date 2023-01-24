#include "server.h"
#include<QPushButton>
/*
* ���캯��
*/
server::server(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::serverClass)
{
	ui->setupUi(this);
	database = new Database();
	database->connectDatabase();
	//1.�����������׽��ֶ���
	m_tcpServer = new QTcpServer(this);
	//2.����Ϊ����ģʽ
	m_tcpServer->listen(QHostAddress::Any, 5200);
	//3.ͨ���źŽ��տͻ��˵�����
	connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
	
}
/*
* ��������
*/
server::~server()
{
	delete database;
	database = nullptr;
	delete m_tcpServer;
	m_tcpServer = nullptr;
	delete ui;
}
/*
* �û�����
* @param QString�� data���յ�������
* @param QString&�� buffer���ͻ�����
* @param QStringList& ���ݷֶ�
* @param int�� ����ģʽ
*/
void server::userWindow(QString data, QString& buffer, QStringList& list, int num)
{
	Goods good;
	stringstream stream;
	array<int, 6> day = { 0 };
	if (num >= 5 && num <= 7)
	{
		stream.clear();
		stream << Account::qTos(list[1]);
		stream >> day[0];
		stream.clear();
		stream << Account::qTos(list[2]);
		stream >> day[1];
		stream.clear();
		stream << Account::qTos(list[3]);
		stream >> day[2];
	}
	switch (num)
	{
	case 1://��ѯ���п��
	{
		for (auto s : user->getSend())
			LGoods.push_back(s);
		for (auto s : user->getReceive())
			LGoods.push_back(s);
	} break;
	case 3://���ݿ�ݱ�Ų�ѯ���
	{
		if (user->checkPacket(good, Account::qTos(list[1]), user->getSend()) ||
			user->checkPacket(good, Account::qTos(list[1]), user->getReceive()))
			LGoods.push_back(good);
	} break;
	case 5://���ݼļ�ʱ���ѯ���
	{
		goods.clear();
		if (user->checkPacket(goods, day, 1, user->getSend()) || user->checkPacket(goods, day, 1, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 6: //��������ʱ���ѯ���
	{
		goods.clear();
		if (user->checkPacket(goods, day, 3, user->getSend()) || user->checkPacket(goods, day, 3, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 7://�����ռ�ʱ���ѯ���
	{
		goods.clear();
		if (user->checkPacket(goods, day, 2, user->getSend()) || user->checkPacket(goods, day, 2, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 9://���ݼļ��˲�ѯ���
	{
		goods.clear();
		if (user->checkPacket(goods, Account::qTos(list[1]), 1, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 10: //���ݿ��Ա��ѯ���
	{
		goods.clear();
		if (user->checkPacket(goods, Account::qTos(list[1]), 3, user->getSend()) ||
			user->checkPacket(goods, Account::qTos(list[1]), 3, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	}break;
	case 11: //�����ռ��˲�ѯ���
	{
		goods.clear();
		if (user->checkPacket(goods, Account::qTos(list[1]), 2, user->getSend()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 12://��ѯδǩ�տ��
	{
		goods.clear();
		if (user->checkPacket(goods, State::Unsign, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}

	}break;
	case 15:
	{
		user->setPassword(Account::qTos(list[1]));
		user->setName(Account::qTos(list[2]));
		user->setNumber(Account::qTos(list[3]));
		user->setAddress(Account::qTos(list[4]));
		buffer.append("�޸ĳɹ���");
	}break;
	case 16: 
	{
		bool judge = false;
		for (int i = 0; i < userList.size(); i++)
			if (Account::qTos(list[3]) == userList[i])
			{
				judge = true;
				break;
			}
		if (!judge)
			buffer.append("�û��������� ����");
		else {
			Goods* good;
			string name;
			time_t currentTime = time(0);//��ȡ��ǰϵͳʱ��
			judge = false;
			stream.clear();
			stream << Account::qTos(list[5]);
			stream >> num;
			switch (num)
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
				good = new Fragile(0);
			}break;
			}
			good->setSendTime(&currentTime);//����ϵͳʱ��ȷ����ݱ���
			good->setDecription(Account::qTos(list[2]));//���ÿ������
			good->setRecipient(Account::qTos(list[3]));//�����ռ���
			good->setCompany(Account::qTos(list[4]));//���ó��˹�˾
			stream.clear();
			stream << Account::qTos(list[6]);
			stream >> num;
			good->setNumber(num);//���ÿ����
			good->setState(State::Uncollect);
			good->setSender(user->getUserName());
			good->setReceiveTime("0-0-0 0:0:0");
			good->setCollectTime("0-0-0 0:0:0");
			good->setCourier(" ");
			good->setExpressNumber(&currentTime);
			if (user->getBalance() < good->getPiece())
			{
				buffer.append("���㣡��");
			}
			else
			{
				user->addSend(good);
				database->insertPackage(*good);
				database->addBalance(good->getCompany(), good->getPiece());//����ָ��ָ�������������ú���
				buffer.append("���ͳɹ�");
			}
		}
	}break;
	case 17://���ǩ��
	{
		Goods good;
		if (user->checkPacket(good, Account::qTos(list[1]), user->getReceive()))
		{
			if (good.getState() == State::Sign)
				buffer.append("�ÿ����ǩ�� ����");
			else if (good.getState() == State::Uncollect)
				buffer.append("�ÿ��δ���� ����");
			else {
				good.signExpress();
				for (int i = 0; i < user->getReceive().size(); i++)
				{
					if (user->getReceive()[i].getExpressNumber() == good.getExpressNumber())//�ҵ��ÿ�����б��е�λ��
					{
						user->setReceive(good, i);
					}
				}
				database->updatetPackage(good);
				buffer.append("ǩ�ճɹ� ����");
			}
		}
		else {
			buffer.append("��ݲ����� ����");
		}
	}break;
	case 18://�˺ų�ֵ
	{
		double num1;
		stream.clear();
		stream << Account::qTos(list[1]);
		stream >> num1;
		user->setBalance(user->getBalance() + num1);
		buffer.append("��ֵ�ɹ���");
	}break;
	case 26:
	{
		choice = 0;
		user->saveUser();
		delete user;
		user = nullptr;
		LGoods.clear();
	}break;
	}
	if (num <= 12)
	{
		for (auto s : LGoods)
		{
			buffer.append(Account::sToq(s.getExpressNumber() + "*" + s.getType(1) + "*" + s.getState(1) + "*" + to_string(s.getNumber())
				+ "*" + s.getSendTime(1) + "*" + s.getCollectTime(1) + "*" + s.getReceiveTime(1) + "*" + s.getSender() + "*"
				+ s.getCourier() + "*" + s.getRecipient() + "*" + s.getDescribtion() + "*" + s.getCompany()));
			buffer.append("/");
		}
	}
	else if (num == 13) {
		buffer.append(Account::sToq(user->getUserName() + "*" + user->getPassword() + "*" + user->getName()
			+ "*" + user->getNumber() + "*" + user->getAddress() + "*"));
	}
	if (num > 12 && num < 15)
		buffer.append(QString::number(user->getBalance()));
}
/*
* ����Ա����
* @param QString�� data���յ�������
* @param QString&�� buffer���ͻ�����
* @param QStringList& ���ݷֶ�
* @param int�� ����ģʽ
*/
void server::managerWindow(QString data, QString& buffer, QStringList& list, int num)
{
	Goods good;
	stringstream stream;
	array<int, 6> day = { 0 };
	if (num >= 5 && num <= 7)
	{
		stream.clear();
		stream << Account::qTos(list[1]);
		stream >> day[0];
		stream.clear();
		stream << Account::qTos(list[2]);
		stream >> day[1];
		stream.clear();
		stream << Account::qTos(list[3]);
		stream >> day[2];
	}
	goods.clear();
	LUser.clear();
	LCourier.clear();
	LGoods.clear();
	switch (num)
	{
	case 1://��ѯ���п��
	{
		for (auto s : manager->getPacket())
			LGoods.push_back(s);
	} break;
	case 3://���ݿ�ݱ�Ų�ѯ���
	{
		if (manager->checkPacket(good, Account::qTos(list[1]), manager->getPacket()))
			LGoods.push_back(good);
	} break;
	case 5://���ݼļ�ʱ���ѯ���
	{
		if (manager->checkPacket(goods, day, 1, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 6: //��������ʱ���ѯ���
	{
		if (manager->checkPacket(goods, day, 3, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 7://�����ռ�ʱ���ѯ���
	{
		if (manager->checkPacket(goods, day, 2, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 9://���ݼļ��˲�ѯ���
	{
		if (manager->checkPacket(goods, Account::qTos(list[1]), 1, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 10: //���ݿ��Ա��ѯ���
	{
		if (manager->checkPacket(goods, Account::qTos(list[1]), 3, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	}break;
	case 11: //�����ռ��˲�ѯ���
	{
		if (manager->checkPacket(goods, Account::qTos(list[1]), 2, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 13://��ѯδ���տ��
	{
		if (manager->checkPacket(goods, State::Uncollect, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}

	} break;
	case 14://��ѯδǩ�տ��
	{
		if (manager->checkPacket(goods, State::Unsign, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 15://��ѯ��ǩ�տ��
	{
		if (manager->checkPacket(goods, State::Sign, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 16: //��ѯ�����û���Ϣ
	{
		for (auto s : userList)
			LUser.push_back(manager->readUser(s));//��ȡ�����û���Ϣ
	} break;
	case 17://��ѯָ���û���Ϣ
	{
		for (auto s : userList)
		{
			if (Account::sToq(s) == list[1])
				LUser.push_back(manager->readUser(s));
		}
	}break;
	case 18: //��ѯ��˾�������п��Ա��Ϣ
	{
		for (auto s : manager->getCourier())
			LCourier.push_back(s);
	}break;
	case 19: //��ѯָ�����Ա��Ϣ
	{
		for (auto s : manager->getCourier())
		{
			if (Account::sToq(s.getUserName()) == list[1])
				LCourier.push_back(s);
		}
		for (auto s : couriers)
		{
			if (Account::sToq(s.getUserName()) == list[1])
				LCourier.push_back(s);
		}
	}break;
	case 20://��ѯ�����������Ա��Ϣ
	{
		for (auto s : couriers)
			LCourier.push_back(s);
	}break;
	case 24://���Ա���
	{
		bool judge = false;
		for (int i = 0; i < couriers.size(); i++)
		{
			if (Account::qTos(list[1]) == couriers[i].getUserName())
			{
				manager->addCourier(couriers[i]);//����빫˾���¿��Ա
				couriers.erase(couriers.begin() + i);//�������б���ɾ��
				judge = true;
				break;
			}
		}
		if (judge) {
			buffer.append("���Ա��ӳɹ�����");
		}
		else {
			buffer.append("���Ա������ ����");
		}
	}break;
	case 25://���Աɾ��
	{
		bool judge = false;
		for (int i = 0; i < manager->getCourier().size(); i++)
		{
			if (Account::qTos(list[1]) == manager->getCourier()[i].getUserName())
			{
				couriers.emplace_back(manager->decCourier(i));//������������Ա,�ӹ�˾���Ա�б���ɾ��
				judge = true;
				break;
			}
		}
		if (judge) {
			buffer.append("���Աɾ���ɹ�����");
		}
		else {
			buffer.append("���Ա������ ����");
		}
	}break;
	case 26://��ݷ���
	{
		Goods* goodPoint;
		if (manager->findPacket(manager->getPacket(), Account::qTos(list[1]), good))//Ѱ�ҿ��
		{
			if (good.getState() != State::Uncollect)
				buffer.append("�ÿ�������� ����");
			else {
				if (good.getType() == Type::common)
					goodPoint = new Common(good.getNumber());
				else if (good.getType() == Type::book)
					goodPoint = new Book(good.getNumber());
				else
					goodPoint = new Fragile(good.getNumber());
				if (manager->findCourier(Account::qTos(list[2])))
				{
					good.distributeCourier(Account::qTos(list[2]));
					for (int i = 0; i < manager->getPacket().size(); i++)
					{
						if (manager->getPacket()[i].getExpressNumber() == good.getExpressNumber())
							manager->setPacket(good, i);//���������п�ݵ���Ϣ
					}
					database->updatetPackage(good);
					buffer.append("����ɹ� ����");
				}
				else
				{
					buffer.append("�ÿ��Ա������ ����");
				}

			}
		}
	}break;
	case 27:
	{
		choice = 0;
		manager->saveAllCourier(manager->getCompany(), manager->getCourier());//�洢��˾���¿��Ա��Ϣ
		manager->saveAllCourier("0", couriers);//�洢�������Ա��Ϣ
		delete manager;
		manager = nullptr;
		LGoods.clear();
	}break;
	}
	if (num <= 15)
	{
		for (auto s : LGoods)
		{
			buffer.append(Account::sToq(s.getExpressNumber() + "*" + s.getType(1) + "*" + s.getState(1) + "*" + to_string(s.getNumber())
				+ "*" + s.getSendTime(1) + "*" + s.getCollectTime(1) + "*" + s.getReceiveTime(1) + "*" + s.getSender() + "*"
				+ s.getCourier() + "*" + s.getRecipient() + "*" + s.getDescribtion() + "*" + s.getCompany()));
			buffer.append("/");
		}
	}
	else if (num <=17) {
		for (auto s : LUser)
		{
			buffer.append(Account::sToq(s.getUserName() + "*" + s.getPassword() + "*" + s.getName()
				+ "*" + s.getNumber() + "*" + s.getAddress() + "*"));
			buffer.append(QString::number(s.getBalance())+"/");
		}
	}
	else if (num <= 20) {
		for (auto s : LCourier)
		{
			buffer.append(Account::sToq(s.getUserName() + "*" + s.getPassword() + "*" + s.getName()
				+ "*" + s.getNumber() + "*" + s.getCompany() + "*"));
			buffer.append(QString::number(s.getBalance()) + "/");
		}
	}
	else if (num == 21) {
		buffer.append(Account::sToq(manager->getUserName() + "/" + manager->getPassword() + "/" 
			+ manager->getName()+ "/" + manager->getNumber() + "/" + manager->getCompany() + "/"));
		buffer.append(QString::number(manager->getBalance()));
	}
	else if(num == 22)
		buffer.append(QString::number(manager->getBalance()));
}
/*
* ���Ա����
* @param QString�� data���յ�������
* @param QString&�� buffer���ͻ�����
* @param QStringList& ���ݷֶ�
* @param int�� ����ģʽ
*/
void server::courierWindow(QString data, QString& buffer, QStringList& list, int num)
{
	Goods good;
	stringstream stream;
	array<int, 6> day = { 0 };
	if (num >= 5 && num <= 7)
	{
		stream.clear();
		stream << Account::qTos(list[1]);
		stream >> day[0];
		stream.clear();
		stream << Account::qTos(list[2]);
		stream >> day[1];
		stream.clear();
		stream << Account::qTos(list[3]);
		stream >> day[2];
	}
	goods.clear();
	LUser.clear();
	LCourier.clear();
	LGoods.clear();
	switch (num)
	{
	case 1://��ѯ���п��
	{
		for (auto s : courier->getAssigned())
			LGoods.push_back(s);
	} break;
	case 3://���ݿ�ݱ�Ų�ѯ���
	{
		if (courier->checkPacket(good, Account::qTos(list[1]), courier->getAssigned()))
			LGoods.push_back(good);
	} break;
	case 5://���ݼļ�ʱ���ѯ���
	{
		if (courier->checkPacket(goods, day, 1, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 6: //��������ʱ���ѯ���
	{
		if (courier->checkPacket(goods, day, 3, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 7://�����ռ�ʱ���ѯ���
	{
		if (courier->checkPacket(goods, day, 2, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 9://���ݼļ��˲�ѯ���
	{
		if (courier->checkPacket(goods, Account::qTos(list[1]), 1, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 10: //���ݿ��Ա��ѯ���
	{
		if (courier->checkPacket(goods, Account::qTos(list[1]), 3, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	}break;
	case 11: //�����ռ��˲�ѯ���
	{
		if (courier->checkPacket(goods, Account::qTos(list[1]), 2, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 13://��ѯδ���տ��
	{
		if (courier->checkPacket(goods, State::Uncollect, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}

	} break;
	case 14://��ѯδǩ�տ��
	{
		if (courier->checkPacket(goods, State::Unsign, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 15://��ѯ��ǩ�տ��
	{
		if (courier->checkPacket(goods, State::Sign, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 18: //�޸Ŀ��Ա�˺���Ϣ
	{
		courier->setPassword(Account::qTos(list[1]));
		courier->setName(Account::qTos(list[2]));
		courier->setNumber(Account::qTos(list[3]));
	} break;
	case 19: //���տ��
	{
		double money;//�˷�
		if (courier->findPacket(courier->getAssigned(), Account::qTos(list[1]), good))
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
						buffer.append("���ճɹ�");
					}
				}
			}
			else 
				buffer.append("��������� ����");
		}
		else
			buffer.append("��ݲ����� ����");
	}break;
	case 28:
	{
		choice = 0;
		courier->saveCourier();
		delete courier;
		courier = nullptr;
		LGoods.clear();
	}break;
	}
	if (num <= 15)
	{
		for (auto s : LGoods)
		{
			buffer.append(Account::sToq(s.getExpressNumber() + "*" + s.getType(1) + "*" + s.getState(1) + "*" + to_string(s.getNumber())
				+ "*" + s.getSendTime(1) + "*" + s.getCollectTime(1) + "*" + s.getReceiveTime(1) + "*" + s.getSender() + "*"
				+ s.getCourier() + "*" + s.getRecipient() + "*" + s.getDescribtion() + "*" + s.getCompany()));
			buffer.append("/");
		}
	}
	else if (num == 16) {
		 buffer.append(Account::sToq(courier->getUserName() + "*" + courier->getPassword() + "*" + courier->getName()
				+ "*" + courier->getNumber() + "*" + courier->getCompany() + "*"));
			buffer.append(QString::number(courier->getBalance()) + "/");
	}
	else if (num == 17)
		buffer.append(QString::number(courier->getBalance()));
}
/*
* �û�ע��
* @param QString�� data���յ�������
* @param QString&�� buffer���ͻ�����
* @param QStringList& ���ݷֶ�
* @param int�� ����ģʽ
*/
void server::userRegister(QString data, QString& buffer, QStringList& list, int num)
{
	if (num == 1)
	{
		if (list.size() == 1)
			buffer.append("�û�������Ϊ�գ�");
		else if(Account::checkUsername(Account::qTos(list[1]), 1))
			buffer.append("�û����Ѵ��� ��");
	}
	else if (num == 2)
	{
		user->setUserName(Account::qTos(list[1]));
		user->setPassword(Account::qTos(list[2]));
		user->setName(Account::qTos(list[3]));
		user->setNumber(Account::qTos(list[4]));
		user->setAddress(Account::qTos(list[5]));
		user->setBalance(0);
		user->saveUser();
		user->saveUserList(user->getUserName());
		choice = 0;//ת�س�ʼ̬
		delete user;
		user = nullptr;
	}
	else {
		choice = 0;//ת�س�ʼ̬
		delete user;
		user = nullptr;
	}
}
/*
* ���Աע��
* @param QString�� data���յ�������
* @param QString&�� buffer���ͻ�����
* @param QStringList& ���ݷֶ�
* @param int�� ����ģʽ
*/
void server::courierRegister(QString data, QString& buffer, QStringList& list, int num) {
	if (num == 1)
	{
		if (list.size() == 1)
			buffer.append("�û�������Ϊ�գ�");
		else if (Account::checkUsername(Account::qTos(list[1]), 2))
			buffer.append("�û����Ѵ��� ��");
	}
	else if (num == 2)
	{
		courier->setUserName(Account::qTos(list[1]));
		courier->setPassword(Account::qTos(list[2]));
		courier->setName(Account::qTos(list[3]));
		courier->setNumber(Account::qTos(list[4]));
		courier->setBalance(0);
		courier->saveCourier();
		courier->saveCourierToList();
		choice = 0;//ת�س�ʼ̬
		delete courier;
		courier = nullptr;
	}
	else {
		choice = 0;//ת�س�ʼ̬
		delete courier;
		courier = nullptr;
	}
}
/*
* ��ͻ��˽�������
*/
void server::slotNewConnection()
{
	//4.����ͻ�������
	m_tcpSocket = m_tcpServer->nextPendingConnection();
	//5.��������
	ui->textEdit_receiver->append("success");
	//6.�����źţ����ܿͻ�������
	connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
}
/*
* ��¼ǰ����
* @param QString�� data���յ�������
* @param QString&�� buffer���ͻ�����
* @param QStringList& ���ݷֶ�
* @param int�� ����ģʽ
*/
void server::login(QString data, QString& buffer, QStringList& list, int num)
{
	switch (num)
	{
	case 1:
	{
		user = new User(Account::qTos(list[1]), Account::qTos(list[2]));
		if (user->readUser())
		{
			buffer = "1";
			buffer.append("/" + Account::sToq(user->getUserName()) + "/" + Account::sToq(user->getPassword()) +
				"/" + Account::sToq(user->getName()) + "/" + Account::sToq(user->getNumber()) +
				"/" + Account::sToq(user->getAddress()) + "/" + QString::number(user->getBalance()));
			user->setSend(database->findPackageByName(user->getUserName(), 1));//��ȡ�û��ļ���Ϣ
			user->setReceive(database->findPackageByName(user->getUserName(), 2));//��ȡ�û��ռ���Ϣ
			choice = 1;//�û�����ģʽ
			userList.clear();
			user->readAllUserName(userList);
		}
	}break;
	case 2:
	{
		manager = new Manager(Account::qTos(list[1]), Account::qTos(list[2]));
		if (database->findManger(*manager))//�ɹ��ͽ���������
		{
			buffer = "2";
			vector<string> temp;
			couriers.clear();
			buffer.append("/" + Account::sToq(manager->getUserName()) + "/" + Account::sToq(manager->getPassword()) +
				"/" + Account::sToq(manager->getName()) + "/" + Account::sToq(manager->getNumber()) +
				"/" + Account::sToq(manager->getCompany()) + "/" + QString::number(manager->getBalance()));
			manager->setPacket(database->findPackageByName(manager->getCompany(), 4));//��ȡ������˾�����Ϣ
			manager->readAllCourier(temp, manager->getCompany());
			for (auto s : temp)
				couriers.emplace_back(manager->readCourier(s));
			manager->setCourier(couriers);//��ȡ���Ա���ݼ�
			temp.clear();
			couriers.clear();
			manager->readAllCourier(temp, "0");
			for (auto s : temp)
				couriers.emplace_back(manager->readCourier(s));
			choice = 2;//����Ա����ģʽ
			userList.clear();
			manager->readAllUserName(userList);
		}
	}break;
	case 3: 
	{
		courier = new Courier(Account::qTos(list[1]), Account::qTos(list[2]));
		if (courier->readCourier())
		{
			buffer = "3";
			buffer.append("/" + Account::sToq(courier->getUserName()) + "/" + Account::sToq(courier->getPassword()) +
				"/" + Account::sToq(courier->getName()) + "/" + Account::sToq(courier->getNumber()) +
				"/" + Account::sToq(courier->getCompany()) + "/" + QString::number(courier->getBalance()));
			courier->setAssigned(database->findPackageByName(courier->getUserName(), 3));//��ȡ���Ա������Ϣ
			choice = 3;//���Ա����ģʽ
		}
	}break;
	case 4:
	{
		user = new User();
		choice = 4;
		buffer.append("4");
	}break;
	case 5: 
	{
		courier = new Courier();
		choice = 5;
		buffer.append("5");
	}break;
	}
}
/*
* ���ݽ���
*/
void server::slotReadyRead()
 {
	QString data = m_tcpSocket->readAll();
	QString buffer="";
	QStringList list = data.split("*");
	int num;
	Goods good;
	stringstream stream;
	stream << Account::qTos(list[0]);
	stream >> num;
	LGoods.clear();
	switch (choice)//δ��¼
	{
	case 0:login(data, buffer, list, num);
		break;
	case 1: userWindow(data, buffer, list, num);
		break;
	case 2: managerWindow(data, buffer, list, num);
		break;
	case 3: courierWindow(data,buffer,list,num); 
		break;
	case 4: userRegister(data, buffer, list, num); 
		break;
	case 5: courierRegister(data, buffer, list, num); 
		break;
	}
	if (buffer == "")
		buffer += "/";
	m_tcpSocket->write(buffer.toUtf8());
	m_tcpSocket->flush();
}
/*
* �Ͽ�����
*/
void server::closeConnection()
{
	ui->textEdit_receiver->append("close");
	m_tcpSocket->disconnectFromHost();
	m_tcpSocket->close();
}
/*
* ���԰�ť
*/
void server::on_pushButton_send_clicked()
 {
	QString sendData = ui->textEdit_send->toPlainText();
	m_tcpSocket->write(sendData.toLatin1()+"\n");
	m_tcpSocket->write(sendData.toLatin1());
}
