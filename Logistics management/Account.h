#pragma once
#include"head.h"
#include"Goods.h"
using namespace std;
/*
* 账号类
* 为一个基类
* 含基本账号信息与操作
*/
class Account
{
private:
	string userName; //用户名
	string password; //密码
	string name;	 //姓名
	string number;	 //电话号码
	int balance;	//余额
public:
	Account();																			//无参构造函数
	Account(string username, string password);											//有参构造函数
	string getUserName();																//获取用户名
	string getName();																	//获取姓名
	string getNumber();																	//获取电话号码
	string getPassword();																//获取密码
	int getBalance();																	//获取余额
	string getBalance(int index);														//获取字符串形式的余额
	void setUserName(string username);													//修改用户名
	void setName(string name);															//修改姓名
	void setNumber(string number);														//修改电话号码
	void setPassword(string password);													//修改密码
	void setBalance(int balance);														//修改余额
	void readAllUserName(vector<string>& userList);										//读取所有用户名
	void printPacket(vector<Goods> packet);												//输出名下所有快递信息
	void printPacket(Goods packet);														//输出单个快递信息
	bool checkPacket(Goods& good, string s, vector<Goods> goods);						//根据快递编号查询快递
	bool checkPacket(vector<Goods>& goods, State state, vector<Goods> source);			//根据快递状态查询快递
	bool checkPacket(vector<Goods>& goods, string s, bool index, vector<Goods> source);	//根据用户名查询快递信息
	bool checkPacket(vector<Goods>& goods, array<int, 6> s, bool index, vector<Goods> source);//根据时间查询快递信息
};
/*
* 用户类
* 继承账户类
* 内含用户操作
*/
class User : public Account
{
private: 
	string address;				    //地址
	vector<Goods> send;				//发送的快递
	vector<Goods> receive;		    //接收的快递
public:
	User();																				//无参构造函数
	User(string username,string password);												//有参构造函数
	User(string username, string name, string number, string password, string address); //有参构造函数
	string getAddress();																//获取地址
	vector<Goods> getSend();															//获取用户发送的快递
	vector<Goods> getReceive();															//获取用户接受的快递
	void setAddress(string address);													//修改地址
	void registerAccount(string username, string name, string number, string password, string address,int balance);		//有参注册函数
	void registerAccount();																//无参注册函数
	void sendExpress(vector<string> userList,vector<string> companyList);				//发送快递
	void addSend(Goods good);															//增加发送的快递
	void addReceive(Goods good);														//增加接受的快递
	void setSend(vector<Goods> send);													//修改发送快递列表
	void setReceive(vector<Goods> receive);												//修改接收快递列表
	void setReceive(Goods good,int index);												//修改指定位置的接收快递信息
	void saveUser();																	//将用户数据保存入文件	
	bool readUser();																	//从文件中读取用户数据
	void printUser();																	//输出用户的所有信息
	void changeMessage();																//修改账号信息
	~User();																			//析构函数
};
/*
* 管理员类
* 继承账户类
* 内含管理员操作
*/
class Manager : public Account
{
private:
	string company;					//所属物流公司
	vector<Goods> packet;			//物流公司名下所有快递
public:
	Manager();															//无参构造函数
	Manager(string username, string password);							//有参构造函数
	string getCompany();												//获取管理员所在公司
	vector<Goods> getPacket();											//查询所有快递信息
	void setCompany(string company);									//设置管理员所在公司
	void setPacket(vector<Goods> packet);								//修改快递列表信息
	User readUser(string username);										//读取对应用户信息
};
