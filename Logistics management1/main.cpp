#include"Database.h"
#include"Interactive.h"
/*
* ������
*/
int main() {
	int choice = 1;
	string username ;
	string password;
	Interctive inter;
	while (choice <= 5 && choice >= 1)
	{
		cout << "��ѡ����еĲ�����" << endl
			<< "1.�û���¼" << endl
			<< "2.����Ա��¼" << endl
			<< "3.�û�ע��" << endl
			<< "4.���Աע��" << endl
			<< "5.���Ա��¼" << endl
			<< "6.�˳�" << endl;
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
			cout << "��л����ʹ�ã�" << endl;
			break;
		}
	}
	cin.get();
	cin.get();
	return 0;
 }
