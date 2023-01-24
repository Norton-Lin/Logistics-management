#include"Database.h"
#include"Interactive.h"
/*
* 主函数
*/
int main() {
	int choice = 1;
	string username ;
	string password;
	Interctive inter;
	while (choice <= 5 && choice >= 1)
	{
		cout << "请选择进行的操作：" << endl
			<< "1.用户登录" << endl
			<< "2.管理员登录" << endl
			<< "3.用户注册" << endl
			<< "4.快递员注册" << endl
			<< "5.快递员登录" << endl
			<< "6.退出" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			inter.Login();
			break;
		case 2:
			inter.LoginManager();
			break;
		case 3:
			inter.RegisterUser();
			break;
		case 4:
			inter.RegisterCourier();
			break;
		case 5:
			inter.LoginCourier();
		default:
			cout << "感谢您的使用！" << endl;
			break;
		}
	}
	cin.get();
	cin.get();
	return 0;
 }
