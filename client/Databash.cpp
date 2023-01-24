#include "Database.h"
/*
* ���ݿ����Ӻ���
* ���������ݿ������
* @return bool��  true:�ɹ�  false:ʧ��
*/
bool Database::connectDatabase()
{
	mysql_init(&mysql);//����mysql
	//��������
	if (!(mysql_real_connect(&mysql, "localhost", "root", "20021213", "Logistics management", 3306, NULL, 0)))//����ʧ��
		return false;
	else
		return true;
}
/*
* �����Ϣ��ѯ����
* ��ѯ���п����Ϣ
* @param vector<Goods>& �ͣ����ô��ݣ�����goods���ڴ洢��ѯ��������
* @return bool �ɹ�Ϊtrue��ʧ��Ϊfalse
*/
bool Database::find(vector<Goods>& goods)
{
	string sql = "select * from goods";//sql��䣬��goods���ѯ��������
	mysql_query(&mysql, "set names gbk");//���ñ���gbk
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
		return false;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
		return false;
	}
	//��ȡ�ֶε���Ϣ 
	Goods g;
	string message[4];
	for (int i = 0; i < 4; i++)//����֪�ֶ�����������»�ȡ�ֶ��� 
		message[i] = mysql_fetch_field(res)->name;//����һ�������ֶνṹ������
	for (int i = 0; i < 4; i++)//��ӡ�ֶ�  
		cout << message[i] << endl;
	//��ӡ��ȡ������ 
	while (column = mysql_fetch_row(res))//����֪�ֶ���������£���ȡ����ӡ��һ�� 
	{
		g.setType(column[0]);
		g.setState(column[1]);
		g.setNumber(atoi(column[2]));
		g.setExpressNumber(column[3]);
		g.setSendTime(column[4]);
		g.setCollectTime(column[5]);
		g.setReceiveTime(column[6]);
		g.setSender(column[7]);
		g.setCourier(column[8]);
		g.setRecipient(column[9]);
		g.setDecription(column[10]);
		g.setCompany(column[11]);
		//cout << column[0] << column[1] << column[2] << column[3];//����һ�������ֶνṹ������
		goods.push_back(g);//����ȡ������ѹ��goods�б�
	}
	return true;
}
/*
* �����Ϣ��ѯ����
* �����û����Ʋ�ѯָ�����
* @param string�� name
* @param int�� index ��ǲ�����1 ��ѯ�ļ��� ��2 ��ѯ�ռ��� ��3 ��ѯ��ݹ�˾
* @return vector<Goods>��
*/
vector<Goods> Database::findPackageByName(string name, int index)
{
	string sql;

	if (index == 1)//����Ϊ1��������Ǽļ���
		sql = "select * from goods where sender = '" + name + "'";
	else if (index == 2)//����Ϊ2����������ռ���
		sql = "select * from goods where recipient = '" + name + "'";
	else if (index == 3)//����Ϊ3��������ǿ��Ա
		sql = "select * from goods where collecter = '" + name + "'";
	else //����Ա��ѯ
		sql = "select * from goods where company ='" + name + "'";
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
	}
	//��ȡ�ֶε���Ϣ 
	Goods g;
	vector<Goods> goods;
	while (column = mysql_fetch_row(res))//����֪�ֶ���������£���ȡ��һ�� 
	{
		g.setType(column[0]);
		g.setState(column[1]);
		g.setNumber(atoi(column[2]));
		g.setExpressNumber(column[3]);
		g.setSendTime(column[4]);
		g.setCollectTime(column[5]);
		g.setReceiveTime(column[6]);
		g.setSender(column[7]);
		g.setCourier(column[8]);
		g.setRecipient(column[9]);
		g.setDecription(column[10]);
		g.setCompany(column[11]);
		//cout << column[0] << column[1] << column[2] << column[3];//����һ�������ֶνṹ������
		goods.push_back(g);//����ȡ������ѹ��goods�б�
	}
	return goods;
}
/*
void Database::findPackageByRecipient(vector<Goods>& goods, string name)
{
	string sql = "select * from goods where recipient = " + name;
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
		return;
	}
	else
		cout << "��ѯ�ɹ�" << endl;
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
		return;
	}
	cout << "�������Ϊ��" << mysql_affected_rows(&mysql) << endl;
	//��ȡ�ֶε���Ϣ
	Goods g;
	string message[4];
	for (int i = 0; i < 4; i++)//����֪�ֶ�����������»�ȡ�ֶ���
		message[i] = mysql_fetch_field(res)->name;//����һ�������ֶνṹ������
	for (int i = 0; i < 4; i++)//��ӡ�ֶ�
		cout << message[i] << endl;
	//��ӡ��ȡ������
	while (column = mysql_fetch_row(res))//����֪�ֶ���������£���ȡ����ӡ��һ��
	{
		g.setState(column[0]);
		g.setExpressNumber(column[1]);
		g.setSendTime(column[2]);
		g.setReceiveTime(column[3]);
		g.setRecipient(column[4]);
		g.setSender(column[5]);
		g.setDecription(column[6]);
		//cout << column[0] << column[1] << column[2] << column[3];//����һ�������ֶνṹ������
		goods.push_back(g);//����ȡ������ѹ��goods�б�
	}
}
*/
/*
* �����Ϣ���뺯��
* �����ݿ��в����¿����Ϣ
* @param Goods�� goods
*/
void Database::insertPackage(Goods goods)
{
	string sql = "insert into goods values('" + goods.getType(1) + "','" + goods.getState(1) + "','" + to_string(goods.getNumber()) +
		"','" + goods.getExpressNumber() + "','" + goods.getSendTime(1) + "','" + goods.getCollectTime(1) +
		"','" + goods.getReceiveTime(1) + "','" + goods.getSender() + "','" + goods.getCourier() +
		"','" + goods.getRecipient() + "','" + goods.getDescribtion() +
		+"','" + goods.getCompany() + "')";//sql������䣬��goods�����������
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "����ʧ�ܣ�" << mysql_error(&mysql) << endl;
		string message = mysql_error(&mysql);
	}
	else
		cout << "����ɹ�" << endl;
}
/*
* �����Ϣ�޸ĺ���
* �����ݿ����޸���֪�����Ϣ
* @param Goods�� goods
*/
void Database::updatetPackage(Goods goods)
{
	string sql = "update goods set type = '" + goods.getType(1) + "',state = '" + goods.getState(1)
		+ "',number='" + to_string(goods.getNumber()) + "',sendTime='" + goods.getSendTime(1)
		+ "',collecttime='" + goods.getCollectTime(1) + "',ReceiveTime='" + goods.getReceiveTime(1)
		+ "',sender='" + goods.getSender() + "',collecter='" + goods.getCourier()
		+ "',recipient='" + goods.getRecipient() + "',description='" + goods.getDescribtion()
		+ "',company='" + goods.getCompany() + "'where expressnumber=" + goods.getExpressNumber();//sql������䣬���ݿ�ݱ������goods���еĿ����Ϣ
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "�޸ĳɹ�" << endl;
}
/*
* �����Ϣɾ������
* �����ݿ���ɾ�������Ϣ
* @param Goods�� goods
*/
void Database::deletetPackage(Goods goods)
{
	string sql = "delete from goods where expressnumber=" + goods.getExpressNumber();//sqlɾ����䣬���ݿ�ݱ���ɾ��goods���еĶ�Ӧ��Ϣ
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "ɾ��ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "ɾ���ɹ�" << endl;
}
/*
* ����Ա��Ϣ��ѯ����
* �����û��������룬�����ݿ��ж�ȡָ������Ա��Ϣ
* @param Manager&�� manager,���ô��ݣ����ڴ洢��õ�����
*/
bool Database::findManger(Manager& manager)
{
	string sql = "select * from company where username='" + manager.getUserName() + "'and password=" + manager.getPassword();//sql��ѯ��䣬�����û����������compay���в�ѯ����Ա��Ϣ
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
		return false;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
		return false;
	}
	if (mysql_affected_rows(&mysql) == 0)//���Ӳ�ѯ�ɹ����޽����֤���û������������
	{
		cout << "�û������������" << endl;
		return false;
	}
	while (column = mysql_fetch_row(res))//����֪�ֶ���������£���ȡ����ӡ��һ�� 
	{
		int balance;
		stringstream stream;//����ת��
		manager.setName(column[2]);
		manager.setNumber(column[3]);
		manager.setCompany(column[5]);
		stream << column[4];
		stream >> balance;//stringתint
		manager.setBalance(balance);
	}
	return true;
}
/*
* ����Ա��Ϣ���뺯��
* �����ݿ��в����¹���Ա��Ϣ
* @param Manager�� manager
*/
void Database::insertManager(Manager manager)
{
	string balance;
	stringstream stream;
	string sql = "insert into company values('" + manager.getUserName() + "'��'" + manager.getPassword() + "'��'"
		+ "'��'" + manager.getName() + "'��'" + manager.getNumber() + "'��'" + manager.getBalance(1)
		+ "'��'" + manager.getCompany() + "'��";//sql������䣬��company���в������Ա��Ϣ
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "����ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "����ɹ�" << endl;
}
/*
* ����Ա��Ϣ�޸ĺ���
* �����ݿ����޸Ĺ���Ա��Ϣ
* @param Manager�� manager
*/
void Database::updateManager(Manager manager)
{
	string sql = "update company set username = '" + manager.getUserName() + "',password='" + manager.getPassword() +
		+"',name='" + manager.getName() + "',number='" + manager.getNumber() + "',balance='" + manager.getBalance(1)
		+ "where company='" + manager.getCompany();//sql�޸���䣬����������˾�޸�company���еĹ���Ա��Ϣ
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "�޸ĳɹ�" << endl;
}
/*
* ����Ա��Ϣɾ������
* �����ݿ���ɾ���¹���Ա��Ϣ
* @param Manager�� manager
*/
void Database::deleteManager(Manager manager)
{
	string sql = "delete from company where username =" + manager.getUserName();//sqlɾ����䣬�����û�����company����ɾ������Ա��Ϣ
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "ɾ��ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "ɾ���ɹ�" << endl;

}
/*
* ����Ա�����Ӻ���
* @param string�� name
* ���ݹ�˾�������Աת��
*/
void Database::addBalance(string name, double money)
{
	string sql1 = "select balance from company where company ='" + name + "'";//sql��ѯ��䣬����������˾����company���в�ѯ��Ӧ��˾��Ϣ
	int balance;
	stringstream stream;
	string temp = "";
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql1.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "��ѯ�ɹ�" << endl;
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
	}
	cout << "�������Ϊ��" << mysql_affected_rows(&mysql) << endl;
	column = mysql_fetch_row(res);
	stream << column[0];
	stream >> balance;//��ȡԭ���
	balance += money;//�������
	string sql2 = "update company set balance ='" + to_string(balance) + "'where company= '" + name + "'";//sql�޸����
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql2.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "�޸ĳɹ�" << endl;

}
/*
* �û���Ϣ���뺯��
* �����ݿ��в������û���
* @param string�� username
*/
void Database::insertUser(string username) {
	string sql = "insert into account values('" + username + "')";//sql��ѯ��䣬��account���в������û���
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "����ʧ�ܣ�" << mysql_error(&mysql) << endl;
	}
	else
		cout << "����ɹ�" << endl;

}
/*
* �û���Ϣ��ѯ����
* �����ݿ��в�ѯ�����û���
* @param vector<string>&�� userList ���ô��ݣ��洢��õ�����
*/
void Database::findUser(vector<string>& userList) {
	string sql = "select * from account";//sql��ѯ��䣬��account���ж�ȡ�����û���
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
		return;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
		return;
	}
	while (column = mysql_fetch_row(res))//����֪�ֶ���������£���ȡ����ӡ��һ�� 
		userList.push_back(column[0]);

}
/*
* ������˾��Ϣ��ѯ����
* �����ݿ��в�ѯ����������˾��
* @param vector<string>&�� companyList ���ô��ݣ��洢��õ�����
*/
void Database::findCompany(vector<string>& companyList)
{
	string sql = "select company from company";//sql��ѯ��䣬��company���ж�ȡ����������˾��
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
	{
		cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << endl;
		return;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "�޷���ȡ���" << mysql_error(&mysql) << endl;
		return;
	}
	while (column = mysql_fetch_row(res))//����֪�ֶ���������£���ȡ����ӡ��һ�� 
		companyList.push_back(column[0]);
}
/*
* �ͷ���Դ���ر����ݿ�
*/
void Database::FreeConnect()
{
	mysql_free_result(res);//�ͷ�һ�������ʹ�õ��ڴ�
	mysql_close(&mysql);//�ر�һ��������
}
