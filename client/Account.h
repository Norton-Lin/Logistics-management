#pragma once
#include"head.h"
#include"Goods.h"
class Courier;
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
	double balance;	//���
public:
	Account();																			//�޲ι��캯��
	Account(string username, string password);											//�вι��캯��
	string getUserName();																//��ȡ�û���
	string getName();																	//��ȡ����
	string getNumber();																	//��ȡ�绰����
	string getPassword();																//��ȡ����
	double getBalance();																	//��ȡ���
	string getBalance(double index);														//��ȡ�ַ�����ʽ�����
	void setUserName(string username);													//�޸��û���
	void setName(string name);															//�޸�����
	void setNumber(string number);														//�޸ĵ绰����
	void setPassword(string password);													//�޸�����
	void setBalance(double balance);														//�޸����
//	void readAllUserName(vector<string>& userList);										//��ȡ�����û���
//	void saveUserList(string username);//���û��������û��б�
//	void readAllCourier(vector<string>& courierList, string company);					//��ȡ��Ӧ���п��Ա
//	void printPacket(vector<Goods> packet);												//����������п����Ϣ
//	void printPacket(Goods packet);														//������������Ϣ
//	bool checkPacket(Goods& good, string s, vector<Goods> goods);						//���ݿ�ݱ�Ų�ѯ���
//	bool checkPacket(vector<Goods>& goods, State state, vector<Goods> source);			//���ݿ��״̬��ѯ���
//	bool checkPacket(vector<Goods>& goods, string s, int index, vector<Goods> source);	//�����û�����ѯ�����Ϣ
//	bool checkPacket(vector<Goods>& goods, array<int, 6> s, int index, vector<Goods> source);//����ʱ���ѯ�����Ϣ
//	void registerAccount(string username, string name, string number, string password, double balance);		//�в�ע�ắ��
//	bool findPacket(vector<Goods> goods, string s, Goods& good);                                      //���ݿ�ݵ������б���Ѱ�ҿ��
	static QString sToq(const string& s);//Qstringתstring
	static string qTos(const QString& s);//stringתQstring
	static bool checkUsername(string username, int index);//����û����Ƿ����
	static bool checkPassword(string password);//У�������Ƿ���Ϲ淶
	static bool checkNumber(string number);//У��绰�����Ƿ���Ϲ淶

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
	User(string username, string password);												//�вι��캯��
	User(string username, string name, string number, string password, string address); //�вι��캯��
	string getAddress();																//��ȡ��ַ
	vector<Goods> getSend();															//��ȡ�û����͵Ŀ��
	vector<Goods> getReceive();															//��ȡ�û����ܵĿ��
	void setAddress(string address);													//�޸ĵ�ַ
//	void registerAccount(string username, string name, string number, string password, string address, double balance);		//�в�ע�ắ��
//	void registerAccount();																//�޲�ע�ắ��
//	void sendExpress(vector<string> userList, vector<string> companyList);				//���Ϳ��
	void addSend(Goods* good);															//���ӷ��͵Ŀ��
	void addReceive(Goods good);														//���ӽ��ܵĿ��
	void setSend(vector<Goods> send);													//�޸ķ��Ϳ���б�
	void setReceive(vector<Goods> receive);												//�޸Ľ��տ���б�
	void setReceive(Goods good, int index);												//�޸�ָ��λ�õĽ��տ����Ϣ
//	void saveUser();																	//���û����ݱ������ļ�	
//	bool readUser();																	//���ļ��ж�ȡ�û�����
//	void printUser();																	//����û���������Ϣ
//	void changeMessage();																//�޸��˺���Ϣ
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
	vector<Courier> courier;        //������˾�������Ա�б�
public:
	Manager();															//�޲ι��캯��
	Manager(string username, string password);							//�вι��캯��
	string getCompany();												//��ȡ����Ա���ڹ�˾
	vector<Goods> getPacket();											//��ѯ���п����Ϣ
	vector<Courier> getCourier();//��ȡ�������п��Ա��Ϣ
	void setCompany(string company);									//���ù���Ա���ڹ�˾
	void setPacket(vector<Goods> packet);								//�޸Ŀ���б���Ϣ
	void setPacket(Goods good, int index);//�޸�ָ�����
//	User readUser(string username);										//��ȡ��Ӧ�û���Ϣ
//	Courier readCourier(string username);								//��ȡ��Ӧ���Ա��Ϣ
	void setCourier(vector<Courier> courier);							//���ù�˾���¿��Ա
//	void addCourier(Courier& courier);									//��ӿ��Ա
//	Courier decCourier(int index);											//ɾ�����Ա
//	bool findCourier(string username);                                  //Ѱ�ҹ�˾���¿��Ա
//	void saveAllCourier(string company, vector<Courier> courier);												//�洢����˾���Ա�б�
};
/*
* ���Ա��
* �̳��˺���
* �ں����Ա����
*/
class Courier :public Account {
private:
	string company;												//����������˾��һ�����Աֻ������һ����ݹ�˾
	vector<Goods> assigned;										//�����䵽�Ŀ���б�
public:
	Courier();
	Courier(string username, string password);
	string getCompany();										//��ȡ���Ա����������˾
	vector<Goods> getAssigned();								//��ȡ�����䵽�Ŀ���б�
	void setCompany(string company);							//���ÿ��Ա����������˾
	void setAssigned(vector<Goods> goods);						//���ñ����䵽�Ŀ���б�
//	void collectExpress(Goods& good, double& money);							//���տ��
//	void saveCourier();											//�����Ա���ݱ������ļ�	
//	void saveCourierToList();									//��ӿ��Ա������Ӧ������
//	bool readCourier();											//���ļ��ж�ȡ���Ա����
//	void printCourier();                                        //������Ա��Ϣ
//	void changeMessage();//�޸Ŀ��Ա�˺���Ϣ
	void setPacket(Goods good, int index);//�޸�ָ�����
};
