#pragma once
#include"Account.h"
/**
* ���ݿ��࣬�������ݿ����
*/
class Database
{
private:
	MYSQL mysql;												//mysql����
	MYSQL_RES* res;												//����ṹ�������е�һ����ѯ�����
	MYSQL_ROW column;											//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���

public:
	bool connectDatabase();										//�������ݿ�
	bool find(vector<Goods>& goods);							//��ѯ���п����Ϣ
	vector<Goods> findPackageByName(string name, int index);		//Ѱ��ָ�����.1���ݼļ��ˣ�2�����ռ���,���� ���ݹ�˾
	//void findPackageByRecipient(vector<Goods>& goods, string name);//Ѱ��ָ�����
	void insertPackage(Goods goods);							//�����¿��
	void updatetPackage(Goods goods);							//���¿������
	void deletetPackage(Goods goods);							//ɾ���������
	bool findManger(Manager& manager);							//��ѯ����Ա����
	void insertManager(Manager manager);						//�������Ա����
	void updateManager(Manager manager);						//���¹���Ա����
	void deleteManager(Manager manager);						//ɾ������Ա����
	void addBalance(string name, double money);								//�û�ǩ�պ����Ӧ��˾����Աת��
	void insertUser(string username);                           //���û�������û���
	void findUser(vector<string>& userList);					//�õ��û����б�
	void findCompany(vector<string>& companyList);				//�õ���˾���б�
	void FreeConnect();											//�ͷ����ݿ���Դ
};

