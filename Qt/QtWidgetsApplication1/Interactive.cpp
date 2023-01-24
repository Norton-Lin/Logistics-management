#include "Interactive.h"
/*
* �����๹�캯��
* ���ݿ�����
*/
Interctive::Interctive()
{
	database = new Database();
	database->connectDatabase();
}
/*
* ��������������
* �ͷ����ݿ�����ڴ棬�Ͽ����ݿ�����
*/
Interctive::~Interctive()
{
	database->FreeConnect();
	delete database;
	database = nullptr;
}
void Interctive::inputAccountData(string& username, string& name, string& number, string& password, int judge)
{
	cout << "�������û�����" << endl;
	cin >> username;
	while (this->checkUsername(username, judge))//����û����Ƿ����
	{
		cout << "�û��Ѵ��ڣ�����������" << endl;
		cout << "�������û�����" << endl;
		cin >> username;
	}
	cout << "������������" << endl;
	cin >> name;
	cout << "������ϵ�绰��" << endl;
	cin >> number;
	while (!this->checkNumber(number))
	{
		cout << "�绰���벻��ȷ������������" << endl;
		cout << "������绰���룺" << endl;
		cin >> number;
	}
	cout << "���������룬���볤��Ϊ8~16λ" << endl;
	cin >> password;
	while (!this->checkPaasword(password))
	{
		cout << "���벻�Ϲ淶������������" << endl;
		cout << "���������룬���볤��Ϊ8~16λ" << endl;
		cin >> password;
	}
}
/*
* ע�ắ�����û�����ע�����
*/
void Interctive::RegisterUser()
{
	User* user = new User();//�����û������
	string username;
	string name;
	string number;
	string password;
	string address;
	int balance = 0;
	int n;
	inputAccountData(username, name, number, password, 1);
	cout << "��������ϵ��ַ��" << endl;
	cin >> address;
	cout << "�����Ƿ���г�ֵ��" << endl << "1.��\t" << "0.��" << endl;
	cin >> n;
	if (n == 1)
	{
		cout << "�������ֵ����:" << endl;
		cin >> balance;
	}
	user->registerAccount(username, name, number, password, address, balance);//ע���û�
	user->saveUser();//�����û���Ϣ
	database->insertUser(username);
	delete user;
	user = nullptr;
}
/*
* ע�ắ�������Ա����ע�����
*/
void Interctive::RegisterCourier()
{
	Courier* courier = new Courier();//�����û������
	string username;
	string name;
	string number;
	string password;
	int balance = 0;
	inputAccountData(username, name, number, password, 2);
	courier->registerAccount(username, name, number, password, balance);//ע���û�
	courier->setCompany("0");//0��ÿ��Ա��������˾
	courier->saveCourier();
	courier->saveCourierToList();
}
/*
* ��¼�������û����е�¼����
* �����к�������
*/
void Interctive::Login()
{
	string username;
	string password;
	cout << "�������û���" << endl;
	cin >> username;
	cout << "����������" << endl;
	cin >> password;
	User* user = new User(username, password);
	if (user->readUser())
	{
		cout << "��¼�ɹ���" << endl;
		int choice = 1;
		vector<Goods> goods;
		Goods good;
		user->setSend(database->findPackageByName(username, 1));//��ȡ�û��ļ���Ϣ
		user->setReceive(database->findPackageByName(username, 2));//��ȡ�û��ռ���Ϣ
		vector<string> userList;
		vector<string> companyList;
		database->findUser(userList);//��ȡ�û����б�
		database->findCompany(companyList);//��ȡ������˾�б�
		while (choice >= 1 && choice <= 8)
		{
			cout << "��ѡ��ִ�в�����" << endl
				<< "1.��ѯ���п��" << endl
				<< "2.��ѯָ�����" << endl
				<< "3.���Ϳ��" << endl
				<< "4.�˻���ֵ" << endl
				<< "5.��ѯ����δǩ�տ��" << endl
				<< "6.�޸��˻���Ϣ" << endl
				<< "7.��ѯ�˺���Ϣ" << endl
				<< "8.����ѯ" << endl
				<< "9.�˳�" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				if (user->getSend().size() == 0)//�ļ�����Ϊ0
					cout << "��ǰ���ѷ��Ϳ����Ϣ" << endl;
				else
				{
					cout << "�ѷ��͵Ŀ�����£�" << endl;
					user->printPacket(user->getSend());
				}
				if (user->getReceive().size() == 0)//�ռ�����Ϊ0
					cout << "��ǰ�޽��ܿ����Ϣ" << endl;
				else
				{
					cout << "��ǩ�յĿ�����£�" << endl;
					user->printPacket(user->getReceive());
				}
			}
				  break;
			case 2: {
				int choice1 = 0;
				cout << "��ѡ���ѯ��ʽ��" << endl
					<< "1. ���ݿ�ݵ��Ž��в�ѯ" << endl
					<< "2. ���ݿ��ʱ����в�ѯ" << endl
					<< "3. �����û����в�ѯ" << endl;
				cin >> choice1;
				switch (choice1) {
				case 1:
				{
					string s;
					cout << "�������ݵ���" << endl;
					cin >> s;
					if (user->checkPacket(good, s, user->getSend()) || user->checkPacket(good, s, user->getReceive()))//���ռļ��в�ѯ
					{
						cout << "��ѯ�ɹ���" << endl;
						user->printPacket(good);
					}
					else
						cout << "��ѯʧ��" << endl;
					break;
				}
				case 2:
				{
					cout << "�������ѯʱ�䣨��.��.�գ�" << endl;
					array<int, 6> day = { 0 };
					cout << "�������꣺";
					cin >> day[0];
					cout << "�������£�";
					cin >> day[1];
					cout << "�������գ�";
					cin >> day[2];
					goods.clear();//�����ʱ����б�
					//��ѯ�����ڵ��ռļ�
					if (user->checkPacket(goods, day, 1, user->getSend()) || user->checkPacket(goods, day, 2, user->getReceive()))
					{
						cout << "�����շ�������£�" << endl;
						user->printPacket(goods);
					}
					else
						cout << "�����޿���շ���¼" << endl;
					break;
				}
				case 3:
				{
					cout << "�������û�����" << endl;
					cin >> username;
					goods.clear();//�����ʱ����б�
					if (user->checkPacket(goods, username, 1, user->getSend()))//��ѯ���û��ĵļļ�
					{
						cout << "��ѯ�ɹ���" << endl;
						cout << "���͸����û��Ŀ�����£�" << endl;
						user->printPacket(goods);
						goods.clear();
					}
					else
						cout << "�޷��͸����û��Ŀ��" << endl;
					if (user->checkPacket(goods, username, 2, user->getReceive()))//��ѯ���û����ռ�
					{
						cout << "��ѯ�ɹ���" << endl;
						cout << "�����ڸ��û��Ŀ�����£�" << endl;
						user->printPacket(goods);
					}
					else
						cout << "�������ڸ��û��Ŀ��" << endl;
					break;
				}
				}
			}
				  break;
			case 3:
				user->sendExpress(userList, companyList);//���Ϳ��
				break;
			case 4:
			{
				int num;
				cout << "�������ֵ���" << endl;
				cin >> num;
				user->setBalance(user->getBalance() + num);//��ֵ
				break;
			}
			case 5:
			{
				string s;
				int num = 0;
				bool judge = false;
				goods.clear();
				if (user->checkPacket(goods, State::Unsign, user->getReceive()))//��ѯδǩ�տ��
				{
					cout << "δǩ�տ�����£�" << endl;
					user->printPacket(goods);
					cout << "�Ƿ�ǩ�տ�ݣ�1.�ǣ�2.��" << endl;
					cin >> num;
					while (num == 1)//ǩ�տ��
					{
						Goods temp;
						cout << "�������ǩ�տ�ݵ���" << endl;
						cin >> s;
						for (auto i = goods.begin(); i != goods.end(); i++)
							if (i->getExpressNumber() == s)//�ҵ���Ӧ���
							{
								temp = *i;//�ҵ���Ӧ���
								temp.signExpress();
								goods.erase(i);
								judge = true;
								break;
							}
						if (judge)//ǩ�ճɹ����޸����ݿ��ڵ�״̬
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
							cout << "�ÿ�ݲ������ڴ�ǩ�տ���б���";
						if (goods.size() > 0)//���п��δǩ��
						{
							cout << "�Ƿ����ǩ�տ�ݣ�1.�ǣ�2.��" << endl;
							judge = false;
							cin >> num;
						}
						else
							break;
					}
				}
				else
					cout << "��δǩ�տ��" << endl;
			}
			break;
			case 6:
				user->changeMessage();//�޸��˺���Ϣ
				break;
			case 7:
				user->printUser();//��ӡ�˺���Ϣ
				break;
			case 8:
				cout << "��ǰ�� " << user->getBalance() << endl;//��ѯ���
				break;
			default:
				break;
			}
		}
		user->saveUser();//�洢�˺���Ϣ
	}
	delete user;//�����ڴ�
	user = nullptr; //��ֹҰָ��
}
/*
* ����Ա��¼����
*/
void Interctive::LoginManager()
{
	string username;
	string password;
	cout << "�������û���" << endl;
	cin >> username;
	cout << "����������" << endl;
	cin >> password;
	Manager* manager = new Manager(username, password);
	vector<User> user;//�û���Ϣ�б�
	vector<string> userList;
	vector<Courier> courier1;//��ȡ��˾���п��Ա��Ϣ
	vector<Courier> courier2;//��ȡ�����������Ա��Ϣ
	vector<Goods> goods;
	Goods good;
	Goods* goodPoint = nullptr;
	if (database->findManger(*manager))//��ѯ����Ա��Ϣ���������ݿ�
	{
		cout << "��¼�ɹ���" << endl;
		int choice = 1;
		manager->setPacket(database->findPackageByName(manager->getCompany(), 4));//��ȡ����Ա�������п��
		database->findUser(userList);
		manager->readAllUserName(userList);//��ȡ�û����б�
		for (auto s : userList)
			user.emplace_back(manager->readUser(s));//��ȡ�����û���Ϣ
		userList.clear();
		//manager->readAllCourierName(userList,manager->getCompany());//��ȡ���Ա���б�
		manager->readAllCourier(userList, manager->getCompany());
		for (auto s : userList)//��ȡ��˾���¿��Ա�б�
			courier1.emplace_back(manager->readCourier(s));
		manager->setCourier(courier1);
		userList.clear();
		manager->readAllCourier(userList, "0");
		for (auto s : userList)//��ȡ�޹������Ա�б�
			courier2.emplace_back(manager->readCourier(s));
		while (choice >= 1 && choice <= 7)
		{
			cout << "��ѡ��ִ�в�����" << endl
				<< "1.��ѯ���п����Ϣ" << endl
				<< "2.��ѯ�����û���Ϣ" << endl
				<< "3.��ѯ�˻����" << endl
				<< "4.��ѯָ�������Ϣ" << endl
				<< "5.��ѯ�������п��Ա��Ϣ" << endl
				<< "6.����������" << endl
				<< "7.���Ա����" << endl
				<< "8.�˳�" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				manager->printPacket(manager->getPacket());//��ѯ���п����Ϣ
				if (manager->getPacket().size() == 0)
					cout << "��ǰ�޿����Ϣ" << endl;
			}
				  break;
			case 2: {
				for (auto s : user)//��������û���Ϣ
					s.printUser();
				if (user.size() == 0)
					cout << "��ǰ���û���Ϣ" << endl;
			}
				  break;
			case 3: {
				cout << manager->getBalance() << endl;//��ѯ���
			}
				  break;
			case 4: {
				int choice1 = 0;
				do {
					cout << "��ѡ���ѯ��ʽ��" << endl
						<< "1. �����û����в�ѯ" << endl
						<< "2. ���ݿ�ݵ��Ž��в�ѯ" << endl
						<< "3. ���ݿ��ʱ����в�ѯ" << endl
						<< "4. ����Ͷ�ݿ��Ա���в�ѯ" << endl
						<< "5.�����ϸ�����" << endl;
					cin >> choice1;
					switch (choice1)
					{
					case 1:
					{
						int num;
						cout << "�������û�����" << endl;
						cin >> username;
						goods.clear();
						cout << "�������ѯ����(1.�ļ���,2.�ռ���)��";
						cin >> num;
						if (num == 1)
						{
							if (manager->checkPacket(goods, username, 1, manager->getPacket()))
							{
								cout << "��ѯ�ɹ���" << endl;
								cout << "���û������Ϳ�����£�" << endl;
								manager->printPacket(goods);
								goods.clear();
							}
							else
								cout << "���û��޼ļ���¼" << endl;
						}
						else {
							if (manager->checkPacket(goods, username, 2, manager->getPacket()))
							{
								cout << "��ѯ�ɹ���" << endl;
								cout << "���û������տ�����£�" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "���û����ռ���¼" << endl;
						}
					}
					break;
					case 2:
					{
						cout << "�������ݵ���:" << endl;
						cin >> username;
						if (manager->checkPacket(good, username, manager->getPacket()))
						{
							cout << "��ѯ�ɹ���" << endl;
							manager->printPacket(good);
						}
						else
							cout << "��ѯʧ��" << endl;
					}
					break;
					case 3:
					{
						cout << "�������ѯʱ�䣨��.��.�գ�" << endl;
						array<int, 6> day = { 0 };
						cout << "�������꣺";
						cin >> day[0];
						cout << "�������£�";
						cin >> day[1];
						cout << "�������գ�";
						cin >> day[2];
						goods.clear();
						int num;
						cout << "��ѡ���ѯ��ʽ��" << endl << "1.����ʱ��" << endl << "2.ǩ��ʱ��" << endl << "3.����ʱ��" << endl;
						cin >> num;
						switch (num) {
						case 1: {
							if (manager->checkPacket(goods, day, 1, manager->getPacket()))
							{
								cout << "�������з��Ϳ�ݼ�¼���£�" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "�����޿�ݷ��ͼ�¼" << endl;
						}break;
						case 2: {
							if (manager->checkPacket(goods, day, 2, manager->getPacket()))
							{
								cout << "��������ǩ�տ�ݼ�¼���£�" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "�����޿��ǩ�ռ�¼" << endl;
						}break;
						case 3: {
							if (manager->checkPacket(goods, day, 3, manager->getPacket()))
							{
								cout << "�����������տ�ݼ�¼���£�" << endl;
								manager->printPacket(goods);
							}
							else
								cout << "�����޿�����ռ�¼" << endl;
						}break;
						default:
							cout << "�Ƿ����룡" << endl;
							break;
						}
						break;
					}
					break;
					case 4:
					{
						cout << "��������Ա�˺�����" << endl;
						cin >> username;
						goods.clear();
						if (manager->checkPacket(goods, username, 3, manager->getPacket()))
						{
							int choice2;
							vector<Goods> temp;
							do {
								cout << "��ѡ���ѯ��ʽ��" << endl
									<< "1. �����ռ��˽��в�ѯ" << endl
									<< "2. ���ݼļ��˽��в�ѯ" << endl
									<< "3. ���ݿ��ʱ����в�ѯ" << endl
									<< "4. ���ݿ�ݵ��Ž��в�ѯ" << endl
									<< "5. ��ѯ���п����Ϣ" << endl
									<< "6. �����ϸ�����" << endl;
								cin >> choice2;
								switch (choice2) {
								case 1: {
									cout << "������ļ�������:" << endl;
									cin >> username;
									if (manager->checkPacket(temp, username, 1, goods))
									{
										cout << "��ѯ�ɹ���" << endl;
										cout << "���տ���� ���û��ļ���¼���£�" << endl;
										manager->printPacket(temp);
										temp.clear();
									}
									else
										cout << "���տ���� �޸��û��ļ���¼" << endl;
								} break;
								case 2: {
									cout << "�������ռ�������:" << endl;
									cin >> username;
									if (manager->checkPacket(temp, username, 2, goods))
									{
										cout << "��ѯ�ɹ���" << endl;
										cout << "���տ���� ���û��ռ���¼���£�" << endl;
										manager->printPacket(temp);
										temp.clear();
									}
									else
										cout << "���տ���� �޸��û��ռ���¼" << endl;
								} break;
								case 3: {
									cout << "�������ѯʱ�䣨��.��.�գ�" << endl;
									array<int, 6> day = { 0 };
									cout << "�������꣺";
									cin >> day[0];
									cout << "�������£�";
									cin >> day[1];
									cout << "�������գ�";
									cin >> day[2];
									temp.clear();
									int num;
									cout << "��ѡ���ѯ��ʽ��" << endl << "1.����ʱ��" << endl << "2.ǩ��ʱ��" << endl << "3.����ʱ��" << endl;
									cin >> num;
									switch (num) {
									case 1: {
										if (manager->checkPacket(temp, day, 1, goods))
										{
											cout << "���տ���и������з��Ϳ�ݼ�¼���£�" << endl;
											manager->printPacket(temp);
										}
										else
											cout << "���տ���и����޿�ݷ��ͼ�¼" << endl;
									}break;
									case 2: {
										if (manager->checkPacket(temp, day, 2, goods))
										{
											cout << "���տ���и�������ǩ�տ�ݼ�¼���£�" << endl;
											manager->printPacket(temp);
										}
										else
											cout << "���տ���и����޿��ǩ�ռ�¼" << endl;
									}break;
									case 3: {
										if (manager->checkPacket(temp, day, 3, goods))
										{
											cout << "���տ���и����������տ�ݼ�¼���£�" << endl;
											manager->printPacket(temp);
										}
										else
											cout << "���տ���и����޿�����ռ�¼" << endl;
									}break;
									default:
										cout << "�Ƿ����룡" << endl;
										break;
									}
									break;
								} break;
								case 4: {
									cout << "�������ݵ���:" << endl;
									cin >> username;
									if (manager->checkPacket(good, username, goods))
									{
										cout << "��ѯ�ɹ���" << endl;
										manager->printPacket(good);
									}
									else
										cout << "��ѯʧ��" << endl;
								} break;
								case 5: {
									manager->printPacket(goods);
								} break;
								}
								temp.clear();
							} while (choice2 >= 1 && choice2 <= 5);
						}
						else
							cout << "�ÿ��Ա�޿�����ռ�¼" << endl;
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
					cout << "��ǰ�޿��Ա��Ϣ" << endl;
			}
				  break;
			case 6: {
				int num = 1;
				string s;
				while (num == 1)
				{
					cout << "������������ݱ�ţ�" << endl;
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
							cout << "���������տ��Ա�˺�����" << endl;
							cin >> s;
							if (manager->findCourier(s))//��˾����Ѱ�Ҷ�Ӧ���Ա
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
								cout << "���Ա������" << endl;
						} while (!manager->findCourier(s));
						delete goodPoint;//��ʱ�ͷ��ڴ�
						goodPoint = nullptr;
					}
					else
						cout << "δ���տ���в����ڴ˱�ţ�" << endl;
					cout << "�Ƿ��������?(1.��,0.��" << endl;
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
					cout << "��ѡ�������" << endl << "1.��ӿ��Ա" << endl << "2.ɾ�����Ա" << endl
						<< "3.��ѯ���п���ӿ��Ա" << endl << "4.������һ����" << endl;
					cin >> num;
					judge = false;
					if (num == 1)
					{
						cout << "���������ӿ��Ա�û���" << endl;
						cin >> s;
						for (int i = 0; i < courier2.size(); i++)
						{
							if (s == courier2[i].getUserName())
							{
								manager->addCourier(courier2[i]);//����빫˾���¿��Ա
								courier2.erase(courier2.begin() + i);//�������б���ɾ��
								judge = true;
								break;
							}
						}
						if (!judge)
							cout << "���Ա������" << endl;
					}
					else if (num == 2)
					{
						cout << "�������ɾ�����Ա�û���" << endl;
						cin >> s;
						for (int i = 0; i < manager->getCourier().size(); i++)
						{
							if (s == manager->getCourier()[i].getUserName())
							{
								courier2.emplace_back(manager->decCourier(i));//������������Ա,�ӹ�˾���Ա�б���ɾ��
								judge = true;
								break;
							}
						}
						if (!judge)
							cout << "���Ա������" << endl;
					}
					else if (num == 3) {
						for (auto s : courier2)
							s.printCourier();
						if (courier2.size() == 0)
							cout << "��ǰ�޿��Ա��Ϣ" << endl;
						break;
					}
				}

			}
				  break;
			default:
				break;
			}
		}
		manager->saveAllCourier(manager->getCompany(), manager->getCourier());//�洢��˾���¿��Ա��Ϣ
		manager->saveAllCourier("0", courier2);//�洢�������Ա��Ϣ
	}
	delete manager;
	manager = nullptr;
}
/*
* ���Ա��¼����
*/
void Interctive::LoginCourier()
{
	string username;
	string password;
	cout << "�������û���" << endl;
	cin >> username;
	cout << "����������" << endl;
	cin >> password;
	Courier* courier = new Courier(username, password);
	if (courier->readCourier())
	{
		int choice = 1;
		courier->setAssigned(database->findPackageByName(username, 3));//��ȡ���¿��
		while (choice >= 1 && choice <= 6)
		{
			cout << "��ѡ��ִ�в�����" << endl
				<< "1.��ѯ���п��" << endl
				<< "2.��ѯָ�����" << endl
				<< "3.���տ��" << endl
				<< "4.�޸��˻�����" << endl
				<< "5.��ѯ�˺���Ϣ" << endl
				<< "6.����ѯ" << endl
				<< "7.�˳�" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1: {
				if (courier->getAssigned().size() == 0)//�ļ�����Ϊ0
					cout << "��ǰ�޿����Ϣ" << endl;
				else
				{
					cout << "����õĿ����Ϣ����:" << endl;
					courier->printPacket(courier->getAssigned());
				}
			}
				  break;
			case 2: {
				int num = 1;
				vector<Goods> temp;
				do {
					temp.clear();
					cout << "��ѡ��ִ�в���:" << endl;
					cout << "1.�����û�����ѯ���" << endl << "2.����ʱ���ѯ���" << endl
						<< "3.���ݿ�ݱ�Ų�ѯ���" << endl << "4.��ѯ����δ���տ��" << endl
						<< "5.��ѯ����δǩ�տ��" << endl << "6.��ѯ������ǩ�տ��" << endl
						<< "7.��ѯ���������տ��" << endl << "8.�����ϸ�����" << endl;
					cin >> num;
					switch (num) {
					case 1: {
						string s;
						cout << "�������û���" << endl;
						cin >> s;
						for (auto c : courier->getAssigned())
							if (c.getSender() == s || c.getRecipient() == s)
								temp.emplace_back(c);
						if (temp.empty())
							cout << "�޶�Ӧ���" << endl;
						else
						{
							cout << "���û����¿�����£�" << endl;
							courier->printPacket(temp);
						}
					}break;
					case 2: {
						cout << "�������ѯʱ�䣨��.��.�գ�" << endl;
						array<int, 6> day = { 0 };
						cout << "�������꣺";
						cin >> day[0];
						cout << "�������£�";
						cin >> day[1];
						cout << "�������գ�";
						cin >> day[2];
						//��ѯ�����ڵ��ռļ�
						int num;
						cout << "��ѡ���ѯ��ʽ��" << endl << "1.����ʱ��" << endl << "2.ǩ��ʱ��" << endl << "3.����ʱ��" << endl;
						cin >> num;
						switch (num) {
						case 1: {
							if (courier->checkPacket(temp, day, 1, courier->getAssigned()))
							{
								cout << "�������з��Ϳ�ݼ�¼���£�" << endl;
								courier->printPacket(temp);
							}
							else
								cout << "�����޿�ݷ��ͼ�¼" << endl;
						}break;
						case 2: {
							if (courier->checkPacket(temp, day, 2, courier->getAssigned()))
							{
								cout << "��������ǩ�տ�ݼ�¼���£�" << endl;
								courier->printPacket(temp);
							}
							else
								cout << "�����޿��ǩ�ռ�¼" << endl;
						}break;
						case 3: {
							if (courier->checkPacket(temp, day, 3, courier->getAssigned()))
							{
								cout << "�����������տ�ݼ�¼���£�" << endl;
								courier->printPacket(temp);
							}
							else
								cout << "�����޿�����ռ�¼" << endl;
						}break;
						default:
							cout << "�Ƿ����룡" << endl;
							break;
						}
					}break;
					case 3: {
						Goods temp;//�ֲ�����
						cout << "�������ݵ���:" << endl;
						cin >> username;
						if (courier->checkPacket(temp, username, courier->getAssigned()))
						{
							cout << "��ѯ�ɹ���" << endl;
							courier->printPacket(temp);
						}
						else
							cout << "��ѯʧ��" << endl; }break;
					case 4: {
						if (courier->checkPacket(temp, State::Uncollect, courier->getAssigned()))
						{
							cout << "δ���տ�����£�" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "��δ���տ��" << endl;
						}
					}break;
					case 5: {
						if (courier->checkPacket(temp, State::Unsign, courier->getAssigned()))
						{
							cout << "δǩ�տ�����£�" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "��δǩ�տ��" << endl;
						}
					}break;
					case 6: {
						if (courier->checkPacket(temp, State::Sign, courier->getAssigned()))
						{
							cout << "ǩ�տ�����£�" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "����ǩ�տ��" << endl;
						}
					}break;
					case 7: {
						if (courier->checkPacket(temp, State::Unsign, courier->getAssigned()) || courier->checkPacket(temp, State::Sign, courier->getAssigned()))
						{
							cout << "���տ�����£�" << endl;
							courier->printPacket(temp);
						}
						else {
							cout << "��δ���տ��" << endl;
						}
					}break;
					}
				} while (num >= 1 && num <= 7);
			}
				  break;
			case 3: {
				vector<Goods> temp;
				Goods tmp;
				string num;//��ݵ���
				int judge;//����ѭ���жϱ���
				double money;//��ݼ۸�
				do {
					temp.clear();
					if (courier->checkPacket(temp, State::Uncollect, courier->getAssigned()))
					{
						cout << "δ���տ�����£�" << endl;
						courier->printPacket(temp);
						cout << "����������տ�ݱ�ţ�" << endl;
						cin >> num;
						if (courier->findPacket(temp, num, tmp))
						{
							courier->collectExpress(tmp, money);//���տ��
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
						cout << "��δ���տ��" << endl;
						break;
					}
					cout << "�Ƿ�������գ�(1.�ǣ�2.��)" << endl;
					cin >> judge;
				} while (judge == 1);
			}
				  break;
			case 4: {
				courier->changeMessage();
			}
				  break;
			case 5: {
				courier->printCourier();//����˺���Ϣ
			}
				  break;
			case 6: {
				cout << "�˻��� " << courier->getBalance() << endl;
			}
				  break;
			}
		}
	}
}
/*
* �����˺��û����Ƿ��ظ�,����false˵�����ظ�
*/
bool Interctive::checkUsername(string username, int index)
{
	bool result = true;
	fstream fcheck;//�ļ������
	if (index == 1)
		fcheck.open("User/" + username + ".txt");
	else
		fcheck.open("Courier/" + username + ".txt");
	if (!fcheck)//������ͬ���˺�
		result = false;
	return result;
}
/*
*���绰����λ���Ƿ���ȷ,�绰������Ϊ11λ
*/
bool Interctive::checkNumber(string number)
{
	bool result = false;
	if (number.length() == 11)
		result = true;
	return result;
}
/*
* ��������Ƿ���Ϲ淶�����볤��Ϊ8~16λ
*/
bool Interctive::checkPaasword(string password)
{
	bool result = false;
	if (password.length() >= 8 && password.length() <= 16)
		result = true;
	return result;
}

