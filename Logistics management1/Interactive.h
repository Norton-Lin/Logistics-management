#pragma once
#include"Account.h"
#include"Database.h"
/*
* ����������
* �������û����н�������
*/
class Interctive 
{
private:
	Database* database;
public:
	Interctive();//���캯��
	~Interctive();//��������
	void inputAccountData(string& username,string& name,string& password,string& number,int judge);//�˻���������
	void RegisterUser();						//�û�ע�ắ��
	void RegisterCourier();						//���Աע�ắ��
	void Login();								//�û���¼����
	void LoginManager();						//����Ա��¼����
	void LoginCourier();						//���Ա��¼����
	bool checkUsername(string username,int judge);		//�����˺��û����Ƿ��ظ�,����false˵�����ظ�
	bool checkNumber(string number);			//���绰����λ���Ƿ���ȷ
	bool checkPaasword(string password);		//��������Ƿ���Ϲ淶
};
