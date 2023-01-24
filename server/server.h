#pragma once

#include <QtWidgets/QWidget>
#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include "Account.h"
#include "Database.h"
class server : public QWidget
{
    Q_OBJECT
public:
    explicit server(QWidget* parent = 0);
    ~server();
    void userWindow(QString data, QString& buffer, QStringList& list, int num);//用户操作
    void managerWindow(QString data,QString& buffer, QStringList& list,int num);//管理员操作
    void courierWindow(QString data, QString& buffer, QStringList& list, int num);
    void userRegister(QString data, QString& buffer, QStringList& list, int num);
    void courierRegister(QString data, QString& buffer, QStringList& list, int num);
    //快递员操作
    void login(QString data,QString& buffer, QStringList& list,int num);//登录操作

private slots:
    void slotNewConnection();
    void slotReadyRead();
    void closeConnection();
    void on_pushButton_send_clicked();
private:
    Ui::serverClass * ui;
    int choice = 0;//当前操作状态
    QTcpServer* m_tcpServer;//负责监听套接字
    QTcpSocket* m_tcpSocket;//负责通信
    Database* database;
    User* user;//用户账户
    Courier* courier;
    Manager* manager;
    vector<Goods> goods;
    vector<Courier> couriers;//无属快递员列表
    QList<Goods> LGoods;
    QList<User> LUser;
    QList<Courier> LCourier;
    vector<string> userList;//用户列表
};
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

