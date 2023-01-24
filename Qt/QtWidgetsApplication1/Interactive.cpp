#include "Interactive.h"
/*
* 交互类构造函数
* 数据库连接
*/
Interctive::Interctive()
{
	database = new Database();
	database->connectDatabase();
}
/*
* 交互类析构函数
* 释放数据库对象内存，断开数据库连接
*/
Interctive::~Interctive()
{
	database->FreeConnect();
	delete database;
	database = nullptr;
}
void Interctive::inputAccountData(string& username, string& name, string& number, string& password, int judge)
{
	cout << "请输入用户名：" << endl;
	cin >> username;
	while (this->checkUsername(username, judge))//检查用户名是否存在
	{
		cout << "用户已存在，请重新输入" << endl;
		cout << "请输入用户名：" << endl;
		cin >> username;
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输联系电话：" << endl;
	cin >> number;
	while (!this->checkNumber(number))
	{
		cout << "电话号码不正确，请重新输入" << endl;
		cout << "请输入电话号码：" << endl;
		cin >> number;
	}
	cout << "请输入密码，密码长度为8~16位" << endl;
	cin >> password;
	while (!this->checkPaasword(password))
	{
		cout << "密码不合规范，请重新输入" << endl;
		cout << "请输入密码，密码长度为8~16位" << endl;
		cin >> password;
	}
}
/*
* 注册函数，用户进行注册操作
*/
void Interctive::RegisterUser()
{
	User* user = new User();//建立用户类对象
	string username;
	string name;
	string number;
	string password;
	string address;
	int balance = 0;
	int n;
	inputAccountData(username, name, number, password, 1);
	cout << "请输入联系地址：" << endl;
	cin >> address;
	cout << "请问是否进行充值？" << endl << "1.是\t" << "0.否" << endl;
	cin >> n;
	if (n == 1)
	{
		cout << "请输入充值数额:" << endl;
		cin >> balance;
	}
	user->registerAccount(username, name, number, password, address, balance);//注册用户
	user->saveUser();//保存用户信息
	database->insertUser(username);
	delete user;
	user = nullptr;
}
/*
* 注册函数，快递员进行注册操作
*/
void Interctive::RegisterCourier()
{
	Courier* courier = new Courier();//建立用户类对象
	string username;
	string name;
	string number;
	string password;
	int balance = 0;
	inputAccountData(username, name, number, password, 2);
	courier->registerAccount(username, name, number, password, balance);//注册用户
	courier->setCompany("0");//0表该快递员无所属公司
	courier->saveCourier();
	courier->saveCourierToList();
}
/*
* 登录函数，用户进行登录操作
* 并进行后续操作
*/
void Interctive::Login()
{
	string username;
	string password;
	cout << "请输入用户名" << endl;
	cin >> username;
	cout << "请输入密码" << endl;
	cin >> password;
	User* user = new User(username, password);
	if (user->readUser())
	{
		cout << "登录成功！" << endl;
		int choice = 1;
		vector<Goods> goods;
		Goods good;
		user->setSend(database->findPackageByName(username, 1));//读取用户寄件信息
		user->setReceive(database->findPackageByName(username, 2));//读取用户收件信息
		vector<string> userList;
		vector<string> companyList;
		database->findUser(userList);//读取用户名列表
		database->findCompany(companyList);//读取物流公司列表
		while (choice >= 1 && choice <= 8)
		{
			cout << "请选择执行操作：" << endl
				<< "1.查询所有快递" << endl
				<< "2.查询指定快递" << endl
				<< "3.发送快递" << endl
				<< "4.账户充值" << endl
				<< "5.查询所有未签收快递" << endl
				<< "6.修改账户信息" << endl
				<< "7.查询账号信息" << endl
				<< "8.余额查询" << endl
				<< "9.退出" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				if (user->getSend().size() == 0)//寄件数量为0
					cout << "当前无已发送快递信息" << endl;
				else
				{
					cout << "已发送的快递如下：" << endl;
					user->printPacket(user->getSend());
				}
				if (user->getReceive().size() == 0)//收件数量为0
					cout << "当前无接受快递信息" << endl;
				else
				{
					cout << "已签收的快递如下：" << endl;
					user->printPacket(user->getReceive());
				}
			}
				  break;
			case 2: {
				int choice1 = 0;
				cout << "请选择查询方式：" << endl
					<< "1. 根据快递单号进行查询" << endl
					<< "2. 根据快递时间进行查询" << endl
					<< "3. 根据用户进行查询" << endl;
				cin >> choice1;
				switch (choice1) {
				case 1:
				{
					string s;
					cout << "请输入快递单号" << endl;
					cin >> s;
					if (user->checkPacket(good, s, user->getSend()) || user->checkPacket(good, s, user->getReceive()))//从收寄件中查询
					{
						cout << "查询成功！" << endl;
						user->printPacket(good);
					}
					else
						cout << "查询失败" << endl;
					break;
				}
				case 2:
				{
					cout << "请输入查询时间（年.月.日）" << endl;
					array<int, 6> day = { 0 };
					cout << "请输入年：";
					cin >> day[0];
					cout << "请输入月：";
					cin >> day[1];
					cout << "请输入日：";
					cin >> day[2];
					goods.clear();//清空临时快递列表
					//查询该日期的收寄件
					if (user->checkPacket(goods, day, 1, user->getSend()) || user->checkPacket(goods, day, 2, user->getReceive()))
					{
						cout << "该日收发快递如下：" << endl;
						user->printPacket(goods);
					}
					else
						cout << "该日无快递收发记录" << endl;
					break;
				}
				case 3:
				{
					cout << "请输入用户名：" << endl;
					cin >> username;
					goods.clear();//清空临时快递列表
					if (user->checkPacket(goods, username, 1, user->getSend()))//查询该用户的的寄件
					{
						cout << "查询成功！" << endl;
						cout << "发送给该用户的快递如下：" << endl;
						user->printPacket(goods);
						goods.clear();
					}
					else
						cout << "无发送给该用户的快递" << endl;
					if (user->checkPacket(goods, username, 2, user->getReceive()))//查询该用户的收件
					{
						cout << "查询成功！" << endl;
						cout << "来自于该用户的快递如下：" << endl;
						user->printPacket(goods);
					}
					else
						cout << "无来自于该用户的快递" << endl;
					break;
				}
				}
			}
				  break;
			case 3:
				user->sendExpress(userList, companyList);//发送快递
				break;
			case 4:
			{
				int num;
				cout << "请输入充值金额" << endl;
				cin >> num;
				user->setBalance(user->getBalance() + num);//充值
				break;
			}
			case 5:
			{
				string s;
				int num = 0;
				bool judge = false;
				goods.clear();
				if (user->checkPacket(goods, State::Unsign, user->getReceive()))//查询未签收快递
				{
					cout << "未签收快递如下：" << endl;
					user->printPacket(goods);
					cout << "是否签收快递（1.是，2.否）" << endl;
					cin >> num;
					while (num == 1)//签收快递
					{
						Goods temp;
						cout << "请输入待签收快递单号" << endl;
						cin >> s;
						for (auto i = goods.begin(); i != goods.end(); i++)
							if (i->getExpressNumber() == s)//找到对应快递
							{
								temp = *i;//找到对应快递
								temp.signExpress();
								goods.erase(i);
								judge = true;
								break;
							}
						if (judge)//签收成功，修改数据库内的状态
							for (int i = 0; i < user->getReceive().size(); i++)
							{
								if (user->getReceive()[i].getExpressNumber() == s)
								{
									user->setReceive(temp, i);
									database->updatetPackage(temp);
									break;
								}
							}
						else
							cout << "该快递不存在于待签收快递列表中";
						if (goods.size() > 0)//还有快递未签收
						{
							cout << "是否继续签收快递（1.是，2.否）" << endl;
							judge = false;
							cin >> num;
						}
						else
							break;
					}
				}
				else
					cout << "无未签收快递" << endl;
			}
			break;
			case 6:
				user->changeMessage();//修改账号信息
				break;
			case 7:
				user->printUser();//打印账号信息
				break;
			case 8:
				cout << "当前余额： " << user->getBalance() << endl;//查询余额
				break;
			default:
				break;
			}
		}
		user->saveUser();//存储账号信息
	}
	delete user;//回收内存
	user = nullptr; //防止野指针
}
/*
* 管理员登录函数
*/
void Interctive::LoginManager()
{
	string username;
	string password;
	cout << "请输入用户名" << endl;
	cin >> username;
	cout << "请输入密码" << endl;
	cin >> password;
	Manager* manager = new Manager(username, password);
	vector<User> user;//用户信息列表
	vector<string> userList;
	vector<Courier> courier1;//读取公司所有快递员信息
	vector<Courier> courier2;//读取所有无属快递员信息
	vector<Goods> goods;
	Goods good;
	Goods* goodPoint = nullptr;
	if (database->findManger(*manager))//查询管理员信息并连接数据库
	{
		cout << "登录成功！" << endl;
		int choice = 1;
		manager->setPacket(database->findPackageByName(manager->getCompany(), 4));//获取管理员名下所有快递
		database->findUser(userList);
		manager->readAllUserName(userList);//获取用户名列表
		for (auto s : userList)
			user.emplace_back(manager->readUser(s));//读取所有用户信息
		userList.clear();
		//manager->readAllCourierName(userList,manager->getCompany());//获取快递员名列表
		manager->readAllCourier(userList, manager->getCompany());
		for (auto s : userList)//读取公司名下快递员列表
			courier1.emplace_back(manager->readCourier(s));
		manager->setCourier(courier1);
		userList.clear();
		manager->readAllCourier(userList, "0");
		for (auto s : userList)//读取无归属快递员列表
			courier2.emplace_back(manager->readCourier(s));
		while (choice >= 1 && choice <= 7)
		{
			cout << "请选择执行操作：" << endl
				<< "1.查询所有快递信息" << endl
				<< "2.查询所有用户信息" << endl
				<< "3.查询账户余额" << endl
				<< "4.查询指定快递信息" << endl
				<< "5.查询名下所有快递员信息" << endl
				<< "6.分配快递任务" << endl
				<< "7.快递员操作" << endl
				<< "8.退出" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				manager->printPacket(manager->getPacket());//查询所有快递信息
				if (manager->getPacket().size() == 0)
					cout << "当前无快递信息" << endl;
			}
				  break;
			case 2: {
				for (auto s : user)//输出所有用户信息
					s.printUser();
				if (user.size() == 0)
					cout << "当前无用户信息" << endl;
			}
				  break;
			case 3: {
				cout << manager->getBalance() << endl;//查询余额
			}
				  break;
			case 4: {
				int choice1 = 0;
				do {
					cout << "请选择查询方式：" << endl
						<< "1. 根据用户进行查询" << endl
						<< "2. 根据快递单号进行查询" << endl
						<< "3. 根据快递时间进行查询" << endl
						<< "4. 根据投递快递员进行查询" << endl
						<< "5.返回上个界面" << endl;
					cin >> choice1;
					switch (choice1)
					{
					case 1:
					{
						int num;
						cout << "请输入用户名：" << endl;
						cin >> username;
						goods.clear();
						cout << "请输入查询对象(1.寄件人,2.收件人)：";
						cin >> num;
						if (num == 1)
						{
							if (manager->checkPacket(goods, username, 1, manager->getPacket()))
							{
								cout << "查询成功！" << endl;
								cout << "该用户所发送快递如下：" << endl;
								manager->printPacket(goods);
								goods.clear();
							}
							else
								cout << "该用户无寄件记录" << endl;
						}
						else {
							if (manager->checkPacket(goods, username, 2, manager->getPacket()))
							{
								cout << "查询成功！" << endl;
								cout << "该用户所接收快递如下：" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "该用户无收件记录" << endl;
						}
					}
					break;
					case 2:
					{
						cout << "请输入快递单号:" << endl;
						cin >> username;
						if (manager->checkPacket(good, username, manager->getPacket()))
						{
							cout << "查询成功！" << endl;
							manager->printPacket(good);
						}
						else
							cout << "查询失败" << endl;
					}
					break;
					case 3:
					{
						cout << "请输入查询时间（年.月.日）" << endl;
						array<int, 6> day = { 0 };
						cout << "请输入年：";
						cin >> day[0];
						cout << "请输入月：";
						cin >> day[1];
						cout << "请输入日：";
						cin >> day[2];
						goods.clear();
						int num;
						cout << "请选择查询方式：" << endl << "1.发送时间" << endl << "2.签收时间" << endl << "3.揽收时间" << endl;
						cin >> num;
						switch (num) {
						case 1: {
							if (manager->checkPacket(goods, day, 1, manager->getPacket()))
							{
								cout << "该日所有发送快递记录如下：" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "该日无快递发送记录" << endl;
						}break;
						case 2: {
							if (manager->checkPacket(goods, day, 2, manager->getPacket()))
							{
								cout << "该日所有签收快递记录如下：" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "该日无快递签收记录" << endl;
						}break;
						case 3: {
							if (manager->checkPacket(goods, day, 3, manager->getPacket()))
							{
								cout << "该日所有揽收快递记录如下：" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "该日无快递揽收记录" << endl;
						}break;
						default:
							cout << "非法输入！" << endl;
							break;
						}
						break;
					}
					break;
					case 4:
					{
						cout << "请输入快递员账号名：" << endl;
						cin >> username;
						goods.clear();
						if (manager->checkPacket(goods, username, 3, manager->getPacket()))
						{
							int choice2;
							vector<Goods> temp;
							do {
								cout << "请选择查询方式：" << endl
									<< "1. 根据收件人进行查询" << endl
									<< "2. 根据寄件人进行查询" << endl
									<< "3. 根据快递时间进行查询" << endl
									<< "4. 根据快递单号进行查询" << endl
									<< "5. 查询所有快递信息" << endl
									<< "6. 返回上个界面" << endl;
								cin >> choice2;
								switch (choice2) {
								case 1: {
									cout << "请输入寄件人姓名:" << endl;
									cin >> username;
									if (manager->checkPacket(temp, username, 1, goods))
									{
										cout << "查询成功！" << endl;
										cout << "揽收快递中 该用户寄件记录如下：" << endl;
										manager->printPacket(temp);
										temp.clear();
									}
									else
										cout << "揽收快递中 无该用户寄件记录" << endl;
								} break;
								case 2: {
									cout << "请输入收件人姓名:" << endl;
									cin >> username;
									if (manager->checkPacket(temp, username, 2, goods))
									{
										cout << "查询成功！" << endl;
										cout << "揽收快递中 该用户收件记录如下：" << endl;
										manager->printPacket(temp);
										temp.clear();
									}
									else
										cout << "揽收快递中 无该用户收件记录" << endl;
								} break;
								case 3: {
									cout << "请输入查询时间（年.月.日）" << endl;
									array<int, 6> day = { 0 };
									cout << "请输入年：";
									cin >> day[0];
									cout << "请输入月：";
									cin >> day[1];
									cout << "请输入日：";
									cin >> day[2];
									temp.clear();
									int num;
									cout << "请选择查询方式：" << endl << "1.发送时间" << endl << "2.签收时间" << endl << "3.揽收时间" << endl;
									cin >> num;
									switch (num) {
									case 1: {
										if (manager->checkPacket(temp, day, 1, goods))
										{
											cout << "揽收快递中该日所有发送快递记录如下：" << endl;
											manager->printPacket(temp);
										}
										else
											cout << "揽收快递中该日无快递发送记录" << endl;
									}break;
									case 2: {
										if (manager->checkPacket(temp, day, 2, goods))
										{
											cout << "揽收快递中该日所有签收快递记录如下：" << endl;
											manager->printPacket(temp);
										}
										else
											cout << "揽收快递中该日无快递签收记录" << endl;
									}break;
									case 3: {
										if (manager->checkPacket(temp, day, 3, goods))
										{
											cout << "揽收快递中该日所有揽收快递记录如下：" << endl;
											manager->printPacket(temp);
										}
										else
											cout << "揽收快递中该日无快递揽收记录" << endl;
									}break;
									default:
										cout << "非法输入！" << endl;
										break;
									}
									break;
								} break;
								case 4: {
									cout << "请输入快递单号:" << endl;
									cin >> username;
									if (manager->checkPacket(good, username, goods))
									{
										cout << "查询成功！" << endl;
										manager->printPacket(good);
									}
									else
										cout << "查询失败" << endl;
								} break;
								case 5: {
									manager->printPacket(goods);
								} break;
								}
								temp.clear();
							} while (choice2 >= 1 && choice2 <= 5);
						}
						else
							cout << "该快递员无快递揽收记录" << endl;
					}
					break;
					}
				} while (choice1 <= 4 && choice1 >= 1);
			}
				  break;
			case 5: {
				for (auto s : manager->getCourier())
					s.printCourier();
				if (manager->getCourier().size() == 0)
					cout << "当前无快递员信息" << endl;
			}
				  break;
			case 6: {
				int num = 1;
				string s;
				while (num == 1)
				{
					cout << "请输入待分配快递编号：" << endl;
					cin >> s;
					if (manager->findPacket(manager->getPacket(), s, good))
					{
						if (good.getType() == Type::common)
							goodPoint = new Common(good.getNumber());
						else if (good.getType() == Type::book)
							goodPoint = new Book(good.getNumber());
						else
							goodPoint = new Fragile(good.getNumber());
						do {
							cout << "请输入揽收快递员账号名：" << endl;
							cin >> s;
							if (manager->findCourier(s))//公司名下寻找对应快递员
							{
								good.distributeCourier(s);
								for (int i = 0; i < manager->getPacket().size(); i++)
								{
									if (manager->getPacket()[i].getExpressNumber() == good.getExpressNumber())
										manager->setPacket(good, i);
								}
								database->updatetPackage(good);
							}
							else
								cout << "快递员不存在" << endl;
						} while (!manager->findCourier(s));
						delete goodPoint;//及时释放内存
						goodPoint = nullptr;
					}
					else
						cout << "未揽收快递中不存在此编号！" << endl;
					cout << "是否继续分配?(1.是,0.否）" << endl;
					cin >> num;
				}

			}
				  break;
			case 7: {
				int num = 1;
				string s;
				bool judge = false;
				while (num <= 2 && num >= 1)
				{
					cout << "请选择操作：" << endl << "1.添加快递员" << endl << "2.删除快递员" << endl
						<< "3.查询所有可添加快递员" << endl << "4.返回上一界面" << endl;
					cin >> num;
					judge = false;
					if (num == 1)
					{
						cout << "请输入待添加快递员用户名" << endl;
						cin >> s;
						for (int i = 0; i < courier2.size(); i++)
						{
							if (s == courier2[i].getUserName())
							{
								manager->addCourier(courier2[i]);//添加入公司名下快递员
								courier2.erase(courier2.begin() + i);//从无属列表中删除
								judge = true;
								break;
							}
						}
						if (!judge)
							cout << "快递员不存在" << endl;
					}
					else if (num == 2)
					{
						cout << "请输入待删除快递员用户名" << endl;
						cin >> s;
						for (int i = 0; i < manager->getCourier().size(); i++)
						{
							if (s == manager->getCourier()[i].getUserName())
							{
								courier2.emplace_back(manager->decCourier(i));//添加入无属快递员,从公司快递员列表中删除
								judge = true;
								break;
							}
						}
						if (!judge)
							cout << "快递员不存在" << endl;
					}
					else if (num == 3) {
						for (auto s : courier2)
							s.printCourier();
						if (courier2.size() == 0)
							cout << "当前无快递员信息" << endl;
						break;
					}
				}

			}
				  break;
			default:
				break;
			}
		}
		manager->saveAllCourier(manager->getCompany(), manager->getCourier());//存储公司名下快递员信息
		manager->saveAllCourier("0", courier2);//存储无主快递员信息
	}
	delete manager;
	manager = nullptr;
}
/*
* 快递员登录函数
*/
void Interctive::LoginCourier()
{
	string username;
	string password;
	cout << "请输入用户名" << endl;
	cin >> username;
	cout << "请输入密码" << endl;
	cin >> password;
	Courier* courier = new Courier(username, password);
	if (courier->readCourier())
	{
		int choice = 1;
		courier->setAssigned(database->findPackageByName(username, 3));//获取名下快递
		while (choice >= 1 && choice <= 6)
		{
			cout << "请选择执行操作：" << endl
				<< "1.查询所有快递" << endl
				<< "2.查询指定快递" << endl
				<< "3.揽收快递" << endl
				<< "4.修改账户密码" << endl
				<< "5.查询账号信息" << endl
				<< "6.余额查询" << endl
				<< "7.退出" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				if (courier->getAssigned().size() == 0)//寄件数量为0
					cout << "当前无快递信息" << endl;
				else
				{
					cout << "分配得的快递信息如下:" << endl;
					courier->printPacket(courier->getAssigned());
				}
			}
				  break;
			case 2: {
				int num = 1;
				vector<Goods> temp;
				do {
					temp.clear();
					cout << "请选择执行操作:" << endl;
					cout << "1.根据用户名查询快递" << endl << "2.跟据时间查询快递" << endl
						<< "3.根据快递编号查询快递" << endl << "4.查询所有未揽收快递" << endl
						<< "5.查询所有未签收快递" << endl << "6.查询所有已签收快递" << endl
						<< "7.查询所有已揽收快递" << endl << "8.返回上个界面" << endl;
					cin >> num;
					switch (num) {
					case 1: {
						string s;
						cout << "请输入用户名" << endl;
						cin >> s;
						for (auto c : courier->getAssigned())
							if (c.getSender() == s || c.getRecipient() == s)
								temp.emplace_back(c);
						if (temp.empty())
							cout << "无对应快递" << endl;
						else
						{
							cout << "该用户名下快递如下：" << endl;
							courier->printPacket(temp);
						}
					}break;
					case 2: {
						cout << "请输入查询时间（年.月.日）" << endl;
						array<int, 6> day = { 0 };
						cout << "请输入年：";
						cin >> day[0];
						cout << "请输入月：";
						cin >> day[1];
						cout << "请输入日：";
						cin >> day[2];
						//查询该日期的收寄件
						int num;
						cout << "请选择查询方式：" << endl << "1.发送时间" << endl << "2.签收时间" << endl << "3.揽收时间" << endl;
						cin >> num;
						switch (num) {
						case 1: {
							if (courier->checkPacket(temp, day, 1, courier->getAssigned()))
							{
								cout << "该日所有发送快递记录如下：" << endl;
								courier->printPacket(temp);
							}
							else
								cout << "该日无快递发送记录" << endl;
						}break;
						case 2: {
							if (courier->checkPacket(temp, day, 2, courier->getAssigned()))
							{
								cout << "该日所有签收快递记录如下：" << endl;
								courier->printPacket(temp);
							}
							else
								cout << "该日无快递签收记录" << endl;
						}break;
						case 3: {
							if (courier->checkPacket(temp, day, 3, courier->getAssigned()))
							{
								cout << "该日所有揽收快递记录如下：" << endl;
								courier->printPacket(temp);
							}
							else
								cout << "该日无快递揽收记录" << endl;
						}break;
						default:
							cout << "非法输入！" << endl;
							break;
						}
					}break;
					case 3: {
						Goods temp;//局部变量
						cout << "请输入快递单号:" << endl;
						cin >> username;
						if (courier->checkPacket(temp, username, courier->getAssigned()))
						{
							cout << "查询成功！" << endl;
							courier->printPacket(temp);
						}
						else
							cout << "查询失败" << endl; }break;
					case 4: {
						if (courier->checkPacket(temp, State::Uncollect, courier->getAssigned()))
						{
							cout << "未揽收快递如下：" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "无未揽收快递" << endl;
						}
					}break;
					case 5: {
						if (courier->checkPacket(temp, State::Unsign, courier->getAssigned()))
						{
							cout << "未签收快递如下：" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "无未签收快递" << endl;
						}
					}break;
					case 6: {
						if (courier->checkPacket(temp, State::Sign, courier->getAssigned()))
						{
							cout << "签收快递如下：" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "无已签收快递" << endl;
						}
					}break;
					case 7: {
						if (courier->checkPacket(temp, State::Unsign, courier->getAssigned()) || courier->checkPacket(temp, State::Sign, courier->getAssigned()))
						{
							cout << "揽收快递如下：" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "无未揽收快递" << endl;
						}
					}break;
					}
				} while (num >= 1 && num <= 7);
			}
				  break;
			case 3: {
				vector<Goods> temp;
				Goods tmp;
				string num;//快递单号
				int judge;//揽收循环判断变量
				double money;//快递价格
				do {
					temp.clear();
					if (courier->checkPacket(temp, State::Uncollect, courier->getAssigned()))
					{
						cout << "未揽收快递如下：" << endl;
						courier->printPacket(temp);
						cout << "请输入待揽收快递编号：" << endl;
						cin >> num;
						if (courier->findPacket(temp, num, tmp))
						{
							courier->collectExpress(tmp, money);//揽收快递
							for (int i = 0; i < temp.size(); i++)
							{
								if (temp[i].getExpressNumber() == tmp.getExpressNumber())
									temp.erase(temp.begin() + i);
							}
							for (int i = 0; i < courier->getAssigned().size(); i++)
							{
								if (tmp.getExpressNumber() == courier->getAssigned()[i].getExpressNumber())
								{
									courier->setPacket(tmp, i);
									database->updatetPackage(tmp);
									database->addBalance(courier->getCompany(), (-1) * money);
								}
							}
						}
					}
					else {
						cout << "无未揽收快递" << endl;
						break;
					}
					cout << "是否继续揽收？(1.是，2.否)" << endl;
					cin >> judge;
				} while (judge == 1);
			}
				  break;
			case 4: {
				courier->changeMessage();
			}
				  break;
			case 5: {
				courier->printCourier();//输出账号信息
			}
				  break;
			case 6: {
				cout << "账户余额： " << courier->getBalance() << endl;
			}
				  break;
			}
		}
	}
}
/*
* 查验账号用户名是否重复,返回false说明不重复
*/
bool Interctive::checkUsername(string username, int index)
{
	bool result = true;
	fstream fcheck;//文件输出流
	if (index == 1)
		fcheck.open("User/" + username + ".txt");
	else
		fcheck.open("Courier/" + username + ".txt");
	if (!fcheck)//不存在同名账号
		result = false;
	return result;
}
/*
*检查电话号码位数是否正确,电话号码需为11位
*/
bool Interctive::checkNumber(string number)
{
	bool result = false;
	if (number.length() == 11)
		result = true;
	return result;
}
/*
* 检查密码是否符合规范，密码长度为8~16位
*/
bool Interctive::checkPaasword(string password)
{
	bool result = false;
	if (password.length() >= 8 && password.length() <= 16)
		result = true;
	return result;
}

