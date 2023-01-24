#include "Database.h"
/*
* 数据库连接函数
* 建立与数据库的连接
* @return bool型  true:成功  false:失败
*/
bool Database::connectDatabase()
{
	mysql_init(&mysql);//连接mysql
	//建立连接
	if (!(mysql_real_connect(&mysql, "localhost", "root", "20021213", "Logistics management", 3306, NULL, 0)))//连接失败
		return false;
	else
		return true;
}
/*
* 快递信息查询函数
* 查询所有快递信息
* @param vector<Goods>& 型，引用传递，参数goods用于存储查询到的数据
* @return bool 成功为true，失败为false
*/
bool Database::find(vector<Goods>& goods)
{
	string sql = "select * from goods";//sql语句，从goods表查询所有数据
	mysql_query(&mysql, "set names gbk");//设置编码gbk
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
		return false;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
		return false;
	}
	//获取字段的信息 
	Goods g;
	string message[4];
	for (int i = 0; i < 4; i++)//在已知字段数量的情况下获取字段名 
		message[i] = mysql_fetch_field(res)->name;//返回一个所有字段结构的数组
	for (int i = 0; i < 4; i++)//打印字段  
		cout << message[i] << endl;
	//打印获取的数据 
	while (column = mysql_fetch_row(res))//在已知字段数量情况下，获取并打印下一行 
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
		//cout << column[0] << column[1] << column[2] << column[3];//返回一个所有字段结构的数组
		goods.push_back(g);//将读取的数据压入goods列表
	}
	return true;
}
/*
* 快递信息查询函数
* 根据用户名称查询指定快递
* @param string型 name
* @param int型 index 标记参数：1 查询寄件人 ，2 查询收件人 ，3 查询快递公司
* @return vector<Goods>型
*/
vector<Goods> Database::findPackageByName(string name, int index)
{
	string sql;

	if (index == 1)//参数为1，传入的是寄件人
		sql = "select * from goods where sender = '" + name + "'";
	else if (index == 2)//参数为2，传入的是收件人
		sql = "select * from goods where recipient = '" + name + "'";
	else if (index == 3)//参数为3，传入的是快递员
		sql = "select * from goods where collecter = '" + name + "'";
	else //管理员查询
		sql = "select * from goods where company ='" + name + "'";
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
	}
	//获取字段的信息 
	Goods g;
	vector<Goods> goods;
	while (column = mysql_fetch_row(res))//在已知字段数量情况下，获取下一行 
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
		//cout << column[0] << column[1] << column[2] << column[3];//返回一个所有字段结构的数组
		goods.push_back(g);//将读取的数据压入goods列表
	}
	return goods;
}
/*
void Database::findPackageByRecipient(vector<Goods>& goods, string name)
{
	string sql = "select * from goods where recipient = " + name;
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
		return;
	}
	else
		cout << "查询成功" << endl;
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
		return;
	}
	cout << "结果行数为：" << mysql_affected_rows(&mysql) << endl;
	//获取字段的信息
	Goods g;
	string message[4];
	for (int i = 0; i < 4; i++)//在已知字段数量的情况下获取字段名
		message[i] = mysql_fetch_field(res)->name;//返回一个所有字段结构的数组
	for (int i = 0; i < 4; i++)//打印字段
		cout << message[i] << endl;
	//打印获取的数据
	while (column = mysql_fetch_row(res))//在已知字段数量情况下，获取并打印下一行
	{
		g.setState(column[0]);
		g.setExpressNumber(column[1]);
		g.setSendTime(column[2]);
		g.setReceiveTime(column[3]);
		g.setRecipient(column[4]);
		g.setSender(column[5]);
		g.setDecription(column[6]);
		//cout << column[0] << column[1] << column[2] << column[3];//返回一个所有字段结构的数组
		goods.push_back(g);//将读取的数据压入goods列表
	}
}
*/
/*
* 快递信息插入函数
* 向数据库中插入新快递信息
* @param Goods型 goods
*/
void Database::insertPackage(Goods goods)
{
	string sql = "insert into goods values('" + goods.getType(1) + "','" + goods.getState(1) + "','" + to_string(goods.getNumber()) +
		"','" + goods.getExpressNumber() + "','" + goods.getSendTime(1) + "','" + goods.getCollectTime(1) +
		"','" + goods.getReceiveTime(1) + "','" + goods.getSender() + "','" + goods.getCourier() +
		"','" + goods.getRecipient() + "','" + goods.getDescribtion() +
		+"','" + goods.getCompany() + "')";//sql插入语句，向goods表插入新数据
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "插入失败：" << mysql_error(&mysql) << endl;
		string message = mysql_error(&mysql);
	}
	else
		cout << "插入成功" << endl;
}
/*
* 快递信息修改函数
* 向数据库中修改已知快递信息
* @param Goods型 goods
*/
void Database::updatetPackage(Goods goods)
{
	string sql = "update goods set type = '" + goods.getType(1) + "',state = '" + goods.getState(1)
		+ "',number='" + to_string(goods.getNumber()) + "',sendTime='" + goods.getSendTime(1)
		+ "',collecttime='" + goods.getCollectTime(1) + "',ReceiveTime='" + goods.getReceiveTime(1)
		+ "',sender='" + goods.getSender() + "',collecter='" + goods.getCourier()
		+ "',recipient='" + goods.getRecipient() + "',description='" + goods.getDescribtion()
		+ "',company='" + goods.getCompany() + "'where expressnumber=" + goods.getExpressNumber();//sql更新语句，根据快递编码更新goods表中的快递信息
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "修改失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "修改成功" << endl;
}
/*
* 快递信息删除函数
* 从数据库中删除快递信息
* @param Goods型 goods
*/
void Database::deletetPackage(Goods goods)
{
	string sql = "delete from goods where expressnumber=" + goods.getExpressNumber();//sql删除语句，根据快递编码删除goods表中的对应信息
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "删除失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "删除成功" << endl;
}
/*
* 管理员信息查询函数
* 根据用户名和密码，从数据库中读取指定管理员信息
* @param Manager&型 manager,引用传递，用于存储获得的数据
*/
bool Database::findManger(Manager& manager)
{
	string sql = "select * from company where username='" + manager.getUserName() + "'and password=" + manager.getPassword();//sql查询语句，根据用户名和密码从compay表中查询管理员信息
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
		return false;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
		return false;
	}
	if (mysql_affected_rows(&mysql) == 0)//连接查询成功后，无结果，证明用户名或密码错误
	{
		cout << "用户名或密码错误" << endl;
		return false;
	}
	while (column = mysql_fetch_row(res))//在已知字段数量情况下，获取并打印下一行 
	{
		int balance;
		stringstream stream;//类型转换
		manager.setName(column[2]);
		manager.setNumber(column[3]);
		manager.setCompany(column[5]);
		stream << column[4];
		stream >> balance;//string转int
		manager.setBalance(balance);
	}
	return true;
}
/*
* 管理员信息插入函数
* 向数据库中插入新管理员信息
* @param Manager型 manager
*/
void Database::insertManager(Manager manager)
{
	string balance;
	stringstream stream;
	string sql = "insert into company values('" + manager.getUserName() + "'，'" + manager.getPassword() + "'，'"
		+ "'，'" + manager.getName() + "'，'" + manager.getNumber() + "'，'" + manager.getBalance(1)
		+ "'，'" + manager.getCompany() + "'）";//sql插入语句，向company表中插入管理员信息
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "插入失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "插入成功" << endl;
}
/*
* 管理员信息修改函数
* 向数据库中修改管理员信息
* @param Manager型 manager
*/
void Database::updateManager(Manager manager)
{
	string sql = "update company set username = '" + manager.getUserName() + "',password='" + manager.getPassword() +
		+"',name='" + manager.getName() + "',number='" + manager.getNumber() + "',balance='" + manager.getBalance(1)
		+ "where company='" + manager.getCompany();//sql修改语句，根据物流公司修改company表中的管理员信息
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "修改失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "修改成功" << endl;
}
/*
* 管理员信息删除函数
* 从数据库中删除新管理员信息
* @param Manager型 manager
*/
void Database::deleteManager(Manager manager)
{
	string sql = "delete from company where username =" + manager.getUserName();//sql删除语句，根据用户名从company表中删除管理员信息
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "删除失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "删除成功" << endl;

}
/*
* 管理员余额添加函数
* @param string型 name
* 根据公司名向管理员转账
*/
void Database::addBalance(string name, double money)
{
	string sql1 = "select balance from company where company ='" + name + "'";//sql查询语句，根据物流公司名从company表中查询对应公司信息
	int balance;
	stringstream stream;
	string temp = "";
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql1.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "查询成功" << endl;
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
	}
	cout << "结果行数为：" << mysql_affected_rows(&mysql) << endl;
	column = mysql_fetch_row(res);
	stream << column[0];
	stream >> balance;//获取原余额
	balance += money;//添加收入
	string sql2 = "update company set balance ='" + to_string(balance) + "'where company= '" + name + "'";//sql修改语句
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql2.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "修改失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "修改成功" << endl;

}
/*
* 用户信息插入函数
* 向数据库中插入新用户名
* @param string型 username
*/
void Database::insertUser(string username) {
	string sql = "insert into account values('" + username + "')";//sql查询语句，向account表中插入新用户名
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "插入失败：" << mysql_error(&mysql) << endl;
	}
	else
		cout << "插入成功" << endl;

}
/*
* 用户信息查询函数
* 从数据库中查询所有用户名
* @param vector<string>&型 userList 引用传递，存储获得的数据
*/
void Database::findUser(vector<string>& userList) {
	string sql = "select * from account";//sql查询语句，从account表中读取所有用户名
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
		return;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
		return;
	}
	while (column = mysql_fetch_row(res))//在已知字段数量情况下，获取并打印下一行 
		userList.push_back(column[0]);

}
/*
* 物流公司信息查询函数
* 从数据库中查询所有物流公司名
* @param vector<string>&型 companyList 引用传递，存储获得的数据
*/
void Database::findCompany(vector<string>& companyList)
{
	string sql = "select company from company";//sql查询语句，从company表中读取所有物流公司名
	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sql.data())) // 执行指定为一个空结尾的字符串的SQL查询。	
	{
		cout << "查询失败：" << mysql_error(&mysql) << endl;
		return;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		cout << "无法获取结果" << mysql_error(&mysql) << endl;
		return;
	}
	while (column = mysql_fetch_row(res))//在已知字段数量情况下，获取并打印下一行 
		companyList.push_back(column[0]);
}
/*
* 释放资源，关闭数据库
*/
void Database::FreeConnect()
{
	mysql_free_result(res);//释放一个结果集使用的内存
	mysql_close(&mysql);//关闭一个服务器
}
