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
	void Register();						//�û�ע�ắ��
	void Login();							//�û���¼����
	void LoginManager();					//����Ա��¼����
	bool checkUsername(string username);	//�����˺��û����Ƿ��ظ�,����false˵�����ظ�
	bool checkNumber(string number);		//���绰����λ���Ƿ���ȷ
	bool checkPaasword(string password);	//��������Ƿ���Ϲ淶
};
