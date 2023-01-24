#pragma once
#include"head.h"
#include"Goods.h"
using namespace std;
/*
* �˺���
* Ϊһ������
* �������˺���Ϣ�����
*/
class Account
{
private:
	string userName; //�û���
	string password; //����
	string name;	 //����
	string number;	 //�绰����
	int balance;	//���
public:
	Account();																			//�޲ι��캯��
	Account(string username, string password);											//�вι��캯��
	string getUserName();																//��ȡ�û���
	string getName();																	//��ȡ����
	string getNumber();																	//��ȡ�绰����
	string getPassword();																//��ȡ����
	int getBalance();																	//��ȡ���
	string getBalance(int index);														//��ȡ�ַ�����ʽ�����
	void setUserName(string username);													//�޸��û���
	void setName(string name);															//�޸�����
	void setNumber(string number);														//�޸ĵ绰����
	void setPassword(string password);													//�޸�����
	void setBalance(int balance);														//�޸����
	void readAllUserName(vector<string>& userList);										//��ȡ�����û���
	void printPacket(vector<Goods> packet);												//����������п����Ϣ
	void printPacket(Goods packet);														//������������Ϣ
	bool checkPacket(Goods& good, string s, vector<Goods> goods);						//���ݿ�ݱ�Ų�ѯ���
	bool checkPacket(vector<Goods>& goods, State state, vector<Goods> source);			//���ݿ��״̬��ѯ���
	bool checkPacket(vector<Goods>& goods, string s, bool index, vector<Goods> source);	//�����û�����ѯ�����Ϣ
	bool checkPacket(vector<Goods>& goods, array<int, 6> s, bool index, vector<Goods> source);//����ʱ���ѯ�����Ϣ
};
/*
* �û���
* �̳��˻���
* �ں��û�����
*/
class User : public Account
{
private: 
	string address;				    //��ַ
	vector<Goods> send;				//���͵Ŀ��
	vector<Goods> receive;		    //���յĿ��
public:
	User();																				//�޲ι��캯��
	User(string username,string password);												//�вι��캯��
	User(string username, string name, string number, string password, string address); //�вι��캯��
	string getAddress();																//��ȡ��ַ
	vector<Goods> getSend();															//��ȡ�û����͵Ŀ��
	vector<Goods> getReceive();															//��ȡ�û����ܵĿ��
	void setAddress(string address);													//�޸ĵ�ַ
	void registerAccount(string username, string name, string number, string password, string address,int balance);		//�в�ע�ắ��
	void registerAccount();																//�޲�ע�ắ��
	void sendExpress(vector<string> userList,vector<string> companyList);				//���Ϳ��
	void addSend(Goods good);															//���ӷ��͵Ŀ��
	void addReceive(Goods good);														//���ӽ��ܵĿ��
	void setSend(vector<Goods> send);													//�޸ķ��Ϳ���б�
	void setReceive(vector<Goods> receive);												//�޸Ľ��տ���б�
	void setReceive(Goods good,int index);												//�޸�ָ��λ�õĽ��տ����Ϣ
	void saveUser();																	//���û����ݱ������ļ�	
	bool readUser();																	//���ļ��ж�ȡ�û�����
	void printUser();																	//����û���������Ϣ
	void changeMessage();																//�޸��˺���Ϣ
	~User();																			//��������
};
/*
* ����Ա��
* �̳��˻���
* �ں�����Ա����
*/
class Manager : public Account
{
private:
	string company;					//����������˾
	vector<Goods> packet;			//������˾�������п��
public:
	Manager();															//�޲ι��캯��
	Manager(string username, string password);							//�вι��캯��
	string getCompany();												//��ȡ����Ա���ڹ�˾
	vector<Goods> getPacket();											//��ѯ���п����Ϣ
	void setCompany(string company);									//���ù���Ա���ڹ�˾
	void setPacket(vector<Goods> packet);								//�޸Ŀ���б���Ϣ
	User readUser(string username);										//��ȡ��Ӧ�û���Ϣ
};
