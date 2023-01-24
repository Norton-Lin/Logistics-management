#include "server.h"
#include<QPushButton>
/*
* 构造函数
*/
server::server(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::serverClass)
{
	ui->setupUi(this);
	database = new Database();
	database->connectDatabase();
	//1.创建服务器套接字对象
	m_tcpServer = new QTcpServer(this);
	//2.设置为监听模式
	m_tcpServer->listen(QHostAddress::Any, 5200);
	//3.通过信号接收客户端的请求
	connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
	
}
/*
* 析构函数
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
* 用户服务
* @param QString型 data接收到的数据
* @param QString&型 buffer发送缓冲区
* @param QStringList& 数据分段
* @param int型 操作模式
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
	case 1://查询所有快递
	{
		for (auto s : user->getSend())
			LGoods.push_back(s);
		for (auto s : user->getReceive())
			LGoods.push_back(s);
	} break;
	case 3://根据快递编号查询快递
	{
		if (user->checkPacket(good, Account::qTos(list[1]), user->getSend()) ||
			user->checkPacket(good, Account::qTos(list[1]), user->getReceive()))
			LGoods.push_back(good);
	} break;
	case 5://根据寄件时间查询快递
	{
		goods.clear();
		if (user->checkPacket(goods, day, 1, user->getSend()) || user->checkPacket(goods, day, 1, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 6: //根据揽收时间查询快递
	{
		goods.clear();
		if (user->checkPacket(goods, day, 3, user->getSend()) || user->checkPacket(goods, day, 3, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 7://根据收件时间查询快递
	{
		goods.clear();
		if (user->checkPacket(goods, day, 2, user->getSend()) || user->checkPacket(goods, day, 2, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 9://根据寄件人查询快递
	{
		goods.clear();
		if (user->checkPacket(goods, Account::qTos(list[1]), 1, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 10: //根据快递员查询快递
	{
		goods.clear();
		if (user->checkPacket(goods, Account::qTos(list[1]), 3, user->getSend()) ||
			user->checkPacket(goods, Account::qTos(list[1]), 3, user->getReceive()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	}break;
	case 11: //根据收件人查询快递
	{
		goods.clear();
		if (user->checkPacket(goods, Account::qTos(list[1]), 2, user->getSend()))
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
	case 15:
	{
		user->setPassword(Account::qTos(list[1]));
		user->setName(Account::qTos(list[2]));
		user->setNumber(Account::qTos(list[3]));
		user->setAddress(Account::qTos(list[4]));
		buffer.append("修改成功！");
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
			buffer.append("用户名不存在 ！！");
		else {
			Goods* good;
			string name;
			time_t currentTime = time(0);//获取当前系统时间
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
			good->setSendTime(&currentTime);//根据系统时间确定快递编码
			good->setDecription(Account::qTos(list[2]));//设置快递描述
			good->setRecipient(Account::qTos(list[3]));//设置收件人
			good->setCompany(Account::qTos(list[4]));//设置承运公司
			stream.clear();
			stream << Account::qTos(list[6]);
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
				buffer.append("余额不足！！");
			}
			else
			{
				user->addSend(good);
				database->insertPackage(*good);
				database->addBalance(good->getCompany(), good->getPiece());//基类指针指向派生类对象调用函数
				buffer.append("发送成功");
			}
		}
	}break;
	case 17://快递签收
	{
		Goods good;
		if (user->checkPacket(good, Account::qTos(list[1]), user->getReceive()))
		{
			if (good.getState() == State::Sign)
				buffer.append("该快递已签收 ！！");
			else if (good.getState() == State::Uncollect)
				buffer.append("该快递未揽收 ！！");
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
				buffer.append("签收成功 ！！");
			}
		}
		else {
			buffer.append("快递不存在 ！！");
		}
	}break;
	case 18://账号充值
	{
		double num1;
		stream.clear();
		stream << Account::qTos(list[1]);
		stream >> num1;
		user->setBalance(user->getBalance() + num1);
		buffer.append("充值成功！");
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
* 管理员服务
* @param QString型 data接收到的数据
* @param QString&型 buffer发送缓冲区
* @param QStringList& 数据分段
* @param int型 操作模式
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
	case 1://查询所有快递
	{
		for (auto s : manager->getPacket())
			LGoods.push_back(s);
	} break;
	case 3://根据快递编号查询快递
	{
		if (manager->checkPacket(good, Account::qTos(list[1]), manager->getPacket()))
			LGoods.push_back(good);
	} break;
	case 5://根据寄件时间查询快递
	{
		if (manager->checkPacket(goods, day, 1, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 6: //根据揽收时间查询快递
	{
		if (manager->checkPacket(goods, day, 3, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 7://根据收件时间查询快递
	{
		if (manager->checkPacket(goods, day, 2, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 9://根据寄件人查询快递
	{
		if (manager->checkPacket(goods, Account::qTos(list[1]), 1, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 10: //根据快递员查询快递
	{
		if (manager->checkPacket(goods, Account::qTos(list[1]), 3, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	}break;
	case 11: //根据收件人查询快递
	{
		if (manager->checkPacket(goods, Account::qTos(list[1]), 2, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 13://查询未揽收快递
	{
		if (manager->checkPacket(goods, State::Uncollect, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}

	} break;
	case 14://查询未签收快递
	{
		if (manager->checkPacket(goods, State::Unsign, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 15://查询已签收快递
	{
		if (manager->checkPacket(goods, State::Sign, manager->getPacket()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 16: //查询所有用户信息
	{
		for (auto s : userList)
			LUser.push_back(manager->readUser(s));//读取所有用户信息
	} break;
	case 17://查询指定用户信息
	{
		for (auto s : userList)
		{
			if (Account::sToq(s) == list[1])
				LUser.push_back(manager->readUser(s));
		}
	}break;
	case 18: //查询公司名下所有快递员信息
	{
		for (auto s : manager->getCourier())
			LCourier.push_back(s);
	}break;
	case 19: //查询指定快递员信息
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
	case 20://查询所有无主快递员信息
	{
		for (auto s : couriers)
			LCourier.push_back(s);
	}break;
	case 24://快递员添加
	{
		bool judge = false;
		for (int i = 0; i < couriers.size(); i++)
		{
			if (Account::qTos(list[1]) == couriers[i].getUserName())
			{
				manager->addCourier(couriers[i]);//添加入公司名下快递员
				couriers.erase(couriers.begin() + i);//从无属列表中删除
				judge = true;
				break;
			}
		}
		if (judge) {
			buffer.append("快递员添加成功！！");
		}
		else {
			buffer.append("快递员不存在 ！！");
		}
	}break;
	case 25://快递员删除
	{
		bool judge = false;
		for (int i = 0; i < manager->getCourier().size(); i++)
		{
			if (Account::qTos(list[1]) == manager->getCourier()[i].getUserName())
			{
				couriers.emplace_back(manager->decCourier(i));//添加入无属快递员,从公司快递员列表中删除
				judge = true;
				break;
			}
		}
		if (judge) {
			buffer.append("快递员删除成功！！");
		}
		else {
			buffer.append("快递员不存在 ！！");
		}
	}break;
	case 26://快递分配
	{
		Goods* goodPoint;
		if (manager->findPacket(manager->getPacket(), Account::qTos(list[1]), good))//寻找快递
		{
			if (good.getState() != State::Uncollect)
				buffer.append("该快递已揽收 ！！");
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
							manager->setPacket(good, i);//更新序列中快递的信息
					}
					database->updatetPackage(good);
					buffer.append("分配成功 ！！");
				}
				else
				{
					buffer.append("该快递员不存在 ！！");
				}

			}
		}
	}break;
	case 27:
	{
		choice = 0;
		manager->saveAllCourier(manager->getCompany(), manager->getCourier());//存储公司名下快递员信息
		manager->saveAllCourier("0", couriers);//存储无主快递员信息
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
* 快递员服务
* @param QString型 data接收到的数据
* @param QString&型 buffer发送缓冲区
* @param QStringList& 数据分段
* @param int型 操作模式
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
	case 1://查询所有快递
	{
		for (auto s : courier->getAssigned())
			LGoods.push_back(s);
	} break;
	case 3://根据快递编号查询快递
	{
		if (courier->checkPacket(good, Account::qTos(list[1]), courier->getAssigned()))
			LGoods.push_back(good);
	} break;
	case 5://根据寄件时间查询快递
	{
		if (courier->checkPacket(goods, day, 1, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 6: //根据揽收时间查询快递
	{
		if (courier->checkPacket(goods, day, 3, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 7://根据收件时间查询快递
	{
		if (courier->checkPacket(goods, day, 2, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 9://根据寄件人查询快递
	{
		if (courier->checkPacket(goods, Account::qTos(list[1]), 1, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 10: //根据快递员查询快递
	{
		if (courier->checkPacket(goods, Account::qTos(list[1]), 3, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	}break;
	case 11: //根据收件人查询快递
	{
		if (courier->checkPacket(goods, Account::qTos(list[1]), 2, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 13://查询未揽收快递
	{
		if (courier->checkPacket(goods, State::Uncollect, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}

	} break;
	case 14://查询未签收快递
	{
		if (courier->checkPacket(goods, State::Unsign, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 15://查询已签收快递
	{
		if (courier->checkPacket(goods, State::Sign, courier->getAssigned()))
		{
			for (auto s : goods)
				LGoods.push_back(s);
		}
	} break;
	case 18: //修改快递员账号信息
	{
		courier->setPassword(Account::qTos(list[1]));
		courier->setName(Account::qTos(list[2]));
		courier->setNumber(Account::qTos(list[3]));
	} break;
	case 19: //揽收快递
	{
		double money;//运费
		if (courier->findPacket(courier->getAssigned(), Account::qTos(list[1]), good))
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
						buffer.append("揽收成功");
					}
				}
			}
			else 
				buffer.append("快递已揽收 ！！");
		}
		else
			buffer.append("快递不存在 ！！");
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
* 用户注册
* @param QString型 data接收到的数据
* @param QString&型 buffer发送缓冲区
* @param QStringList& 数据分段
* @param int型 操作模式
*/
void server::userRegister(QString data, QString& buffer, QStringList& list, int num)
{
	if (num == 1)
	{
		if (list.size() == 1)
			buffer.append("用户名不可为空！");
		else if(Account::checkUsername(Account::qTos(list[1]), 1))
			buffer.append("用户名已存在 ！");
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
		choice = 0;//转回初始态
		delete user;
		user = nullptr;
	}
	else {
		choice = 0;//转回初始态
		delete user;
		user = nullptr;
	}
}
/*
* 快递员注册
* @param QString型 data接收到的数据
* @param QString&型 buffer发送缓冲区
* @param QStringList& 数据分段
* @param int型 操作模式
*/
void server::courierRegister(QString data, QString& buffer, QStringList& list, int num) {
	if (num == 1)
	{
		if (list.size() == 1)
			buffer.append("用户名不可为空！");
		else if (Account::checkUsername(Account::qTos(list[1]), 2))
			buffer.append("用户名已存在 ！");
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
		choice = 0;//转回初始态
		delete courier;
		courier = nullptr;
	}
	else {
		choice = 0;//转回初始态
		delete courier;
		courier = nullptr;
	}
}
/*
* 与客户端建立连接
*/
void server::slotNewConnection()
{
	//4.处理客户端请求
	m_tcpSocket = m_tcpServer->nextPendingConnection();
	//5.发送数据
	ui->textEdit_receiver->append("success");
	//6.连接信号，接受客户端数据
	connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
}
/*
* 登录前操作
* @param QString型 data接收到的数据
* @param QString&型 buffer发送缓冲区
* @param QStringList& 数据分段
* @param int型 操作模式
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
			user->setSend(database->findPackageByName(user->getUserName(), 1));//读取用户寄件信息
			user->setReceive(database->findPackageByName(user->getUserName(), 2));//读取用户收件信息
			choice = 1;//用户操作模式
			userList.clear();
			user->readAllUserName(userList);
		}
	}break;
	case 2:
	{
		manager = new Manager(Account::qTos(list[1]), Account::qTos(list[2]));
		if (database->findManger(*manager))//成功就进入主界面
		{
			buffer = "2";
			vector<string> temp;
			couriers.clear();
			buffer.append("/" + Account::sToq(manager->getUserName()) + "/" + Account::sToq(manager->getPassword()) +
				"/" + Account::sToq(manager->getName()) + "/" + Account::sToq(manager->getNumber()) +
				"/" + Account::sToq(manager->getCompany()) + "/" + QString::number(manager->getBalance()));
			manager->setPacket(database->findPackageByName(manager->getCompany(), 4));//读取物流公司快递信息
			manager->readAllCourier(temp, manager->getCompany());
			for (auto s : temp)
				couriers.emplace_back(manager->readCourier(s));
			manager->setCourier(couriers);//获取快递员数据集
			temp.clear();
			couriers.clear();
			manager->readAllCourier(temp, "0");
			for (auto s : temp)
				couriers.emplace_back(manager->readCourier(s));
			choice = 2;//管理员操作模式
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
			courier->setAssigned(database->findPackageByName(courier->getUserName(), 3));//读取快递员揽件信息
			choice = 3;//快递员操作模式
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
* 数据接受
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
	switch (choice)//未登录
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
* 断开连接
*/
void server::closeConnection()
{
	ui->textEdit_receiver->append("close");
	m_tcpSocket->disconnectFromHost();
	m_tcpSocket->close();
}
/*
* 测试按钮
*/
void server::on_pushButton_send_clicked()
 {
	QString sendData = ui->textEdit_send->toPlainText();
	m_tcpSocket->write(sendData.toLatin1()+"\n");
	m_tcpSocket->write(sendData.toLatin1());
}
