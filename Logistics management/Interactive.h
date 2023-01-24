#pragma once
#include"Account.h"
#include"Database.h"
/*
* 交互操作类
* 用于与用户进行交互操作
*/
class Interctive 
{
private:
	Database* database;
public:
	Interctive();//构造函数
	~Interctive();//析构函数
	void Register();						//用户注册函数
	void Login();							//用户登录函数
	void LoginManager();					//管理员登录函数
	bool checkUsername(string username);	//查验账号用户名是否重复,返回false说明不重复
	bool checkNumber(string number);		//检查电话号码位数是否正确
	bool checkPaasword(string password);	//检查密码是否符合规范
};
