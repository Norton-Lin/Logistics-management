#pragma once
#include"Account.h"
/**
* 数据库类，进行数据库操作
*/
class Database
{
private:
	MYSQL mysql;												//mysql连接
	MYSQL_RES* res;												//这个结构代表返回行的一个查询结果集
	MYSQL_ROW column;											//一个行数据的类型安全(type-safe)的表示，表示数据行的列

public:
	bool connectDatabase();										//连接数据库
	bool find(vector<Goods>& goods);							//查询所有快递信息
	vector<Goods> findPackageByName(string name, int index);		//寻找指定快递.1根据寄件人，2根据收件人,其他 根据公司
	//void findPackageByRecipient(vector<Goods>& goods, string name);//寻找指定快递
	void insertPackage(Goods goods);							//插入新快递
	void updatetPackage(Goods goods);							//更新快递数据
	void deletetPackage(Goods goods);							//删除快递数据
	bool findManger(Manager& manager);							//查询管理员数据
	void insertManager(Manager manager);						//插入管理员数据
	void updateManager(Manager manager);						//更新管理员数据
	void deleteManager(Manager manager);						//删除管理员数据
	void addBalance(string name, double money);								//用户签收后给对应公司管理员转账
	void insertUser(string username);                           //向用户表插入用户名
	void findUser(vector<string>& userList);					//得到用户名列表
	void findCompany(vector<string>& companyList);				//得到公司名列表
	void FreeConnect();											//释放数据库资源
};

