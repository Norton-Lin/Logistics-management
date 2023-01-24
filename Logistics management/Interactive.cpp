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
/*
* ע�ắ�����û�����ע�����
*/
void Interctive::Register()
{
	User* user = new User();//�����û������
	string username;
	string name;
	string number;
	string password;
	string address;
	int balance = 0;
	int n;
	cout << "�������û�����" << endl;
	cin >> username;
	while (this->checkUsername(username))//����û����Ƿ����
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
	cout << "��������ϵ��ַ��" << endl;
	cin >> address;
	cout << "�����Ƿ���г�ֵ��" << endl << "1.��\t" << "0.��" << endl;
	cin >> n;
	if (n == 1)
	{
		cout << "�������ֵ����:" << endl;
		cin >> balance;
	}
	user->registerAccount(username,name,number,password,address,balance);//ע���û�
	user->saveUser();//�����û���Ϣ
	if(database->connectDatabase())
	   database->insertUser(username);
	//database->FreeConnect();
	delete user;
	user = nullptr;
//	delete database;
	//database = nullptr;
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
				<< "6.�޸��˻�����" << endl
				<< "7.��ѯ�˺���Ϣ" << endl
				<< "8.����ѯ" <<endl
				<< "9.�˳�" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
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
				break;
			}
			case 2:
			{
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
					if (user->checkPacket(goods, day, true, user->getSend()) || user->checkPacket(goods, day, false, user->getReceive()))
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
					if (user->checkPacket(goods, username, false, user->getSend()))//��ѯ���û��ĵļļ�
					{
						cout << "��ѯ�ɹ���" << endl;
						cout << "���͸����û��Ŀ�����£�" << endl;
						user->printPacket(goods);
						goods.clear();
					}
					else
						cout << "�޷��͸����û��Ŀ��" << endl;
					if (user->checkPacket(goods, username, true, user->getReceive()))//��ѯ���û����ռ�
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
				user->sendExpress(userList,companyList);//���Ϳ��
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
						Goods temp ;
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
						if(judge)//ǩ�ճɹ����޸����ݿ��ڵ�״̬
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
				cout <<"��ǰ�� " << user->getBalance() << endl;//��ѯ���
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
//	Database* database = new Database();
	vector<User> user;//�û���Ϣ�б�
	vector<string> userList;
	vector<Goods> goods;
	Goods good;
	if (database->findManger(*manager))//��ѯ����Ա��Ϣ���������ݿ�
	{
		cout << "��¼�ɹ���" << endl;
		int choice = 1;
		manager->setPacket(database->findPackageByName(manager->getCompany(), 3));//��ȡ����Ա�������п��
		database->findUser(userList);
		manager->readAllUserName(userList);//��ȡ�û����б�
		for (auto s : userList)
			user.emplace_back(manager->readUser(s));
		while (choice >= 1 && choice <= 4)
		{
			cout << "��ѡ��ִ�в�����" << endl
				<< "1.��ѯ���п����Ϣ" << endl
				<< "2.��ѯ�����û���Ϣ" << endl
				<< "3.��ѯ�˻����" << endl
				<< "4.��ѯָ�������Ϣ" << endl
				<< "5.�˳�" << endl;
			cin >> choice;
				switch (choice)
				{
				case 1:
					manager->printPacket(manager->getPacket());//��ѯ���п����Ϣ
					if (manager->getPacket().size() == 0)
						cout << "��ǰ�޿����Ϣ" << endl;
					break;
				case 2:
					for (auto s : user)//��������û���Ϣ
						s.printUser();
					if (user.size() == 0)
						cout << "��ǰ���û���Ϣ" << endl;
					break;
				case 3:
					cout << manager->getBalance() << endl;//��ѯ���
					break;
				case 4: {
					int choice1 = 0;
					cout << "��ѡ���ѯ��ʽ��" << endl
						<< "1. �����û����в�ѯ" << endl
						<< "2. ���ݿ�ݵ��Ž��в�ѯ" << endl
						<< "3. ���ݿ��ʱ����в�ѯ" << endl;
					cin >> choice1;
					switch (choice1)
					{
					case 1:
						cout << "�������û�����" << endl;
						cin >> username;
						goods.clear();
						if (manager->checkPacket(goods, username, true, manager->getPacket()))
						{
							cout << "��ѯ�ɹ���" << endl;
							cout << "���û������Ϳ�����£�" << endl;
							manager->printPacket(goods);
							goods.clear();
						}
						else
							cout << "���û��޼ļ���¼" << endl;
						if (manager->checkPacket(goods, username, false, manager->getPacket()))
							{
								cout << "��ѯ�ɹ���" << endl;
									cout << "���û������տ�����£�" << endl;
								manager->printPacket(goods);
							}
						else
							cout << "���û����ռ���¼" << endl;
						break;
					case 2:
						cout << "�������ݵ���:" << endl;
						cin >> username;
						if (manager->checkPacket(good, username, manager->getPacket()))
						{
							cout << "��ѯ�ɹ���" << endl;
							manager->printPacket(good);
						}
						else
							cout << "��ѯʧ��" << endl;
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
						if (manager->checkPacket(goods, day, true, manager->getPacket()))
						{
							cout << "�������п�ݼ�¼���£�" << endl;
							manager->printPacket(goods);
						}
						else
							cout << "�����޿���շ���¼" << endl;
						break;
					}
					}
				}
					break;
				default :
					break;
			    }
		}
	}
//	database->FreeConnect();
	delete manager;
	manager = nullptr;
//	delete database;
//	database = nullptr;
}
/*
* �����˺��û����Ƿ��ظ�,����false˵�����ظ�
*/
bool Interctive::checkUsername(string username)
{
	bool result = true;
	fstream fcheck;//�ļ������
	fcheck.open(username + ".txt");
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
	if (password.length()>= 8&&password.length() <= 16)
		result = true;
	return result;
}

