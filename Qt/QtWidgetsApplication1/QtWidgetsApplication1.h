#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include"UserWindow.h"
#include"CourierWindow.h"
#include"ManagerWindow.h"
#include"CourierRegisterWindow.h"
#include"UserRegisterWindow.h"
#include <QtWidgets/qmessagebox.h>
/*
* ��ʼ����
*/
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1Class ui;//������ui����
    UserWindow* userWindow;//�û���������
    ManagerWindow* managerWindow;//����Ա��������
    CourierWindow* courierWindow;//���Ա��������
    UserRegisterWindow* userRegisterWindow;//�û�ע�����
    CourierRegisterWindow* courierRegisterWindow;//���Աע�����
private slots:
    void on_userLogin_clicked();//�û���¼��ť����ź�
    void on_managerLogin_clicked();//����Ա��¼��ť����ź�
    void on_courierLogin_clicked();//���Ա��¼��ť����ź�
    void on_userRegister_clicked();//�û�ע�ᰴť����ź�
    void on_courierRegister_clicked();//���Աע�ᰴť����ź�

};
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif