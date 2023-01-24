#include "client.h"

client::client(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::clientClass)
{
    ui->setupUi(this);
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(0);
    //1.创建套接字
    tcp = new QTcpSocket(this);
    //2.连接服务器
    tcp->connectToHost(QHostAddress("127.0.0.1"), 5200);
    //3.通过信号接收服务器数据
    connect(tcp, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    item_t = new QTreeWidgetItem;
    connect(ui->ul, &QPushButton::clicked, this, &client::on_Userlogin_clicked);//用户登录按钮槽连接
    connect(ui->ml, &QPushButton::clicked, this, &client::on_Managerlogin_clicked);//管理员登录按钮槽连接
    connect(ui->cl, &QPushButton::clicked, this, &client::on_Courierlogin_clicked);//快递员登录按钮槽连接
    connect(ui->ur, &QPushButton::clicked, this, &client::on_UserRegister_clicked);//用户注册按钮槽连接
    connect(ui->cr, &QPushButton::clicked, this, &client::on_CourierRegister_clicked);//快递员注册按钮槽连接
    connect(ui->back,&QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//用户登录界面退出按钮槽连接
    connect(ui->back_2, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//用户登录界面退出按钮槽连接
    connect(ui->back_3, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//用户登录界面退出按钮槽连接
    init_UserWindow();
    init_ManagerWindow();
    init_CourierWindow();
    init_UserRegister();
    init_CourierRegister();
    connect(ui->back_6, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//返回主界面
    connect(ui->back_7, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//返回主界面
    connect(ui->back_8, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//返回主界面
    QString qss;
    QFile file(":/qss/lightblue.css");
    if (file.open(QFile::ReadOnly))
    {
        //用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
        qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
client::~client()
{
    delete tcp;
    tcp = nullptr;
    delete item_t;
    item_t = nullptr;
    delete ui;
}
/**
* 接受服务端数据
*/
void client::slotReadyRead()
{
    QString data = tcp->readAll();;//接受校验数据
    QStringList List1 = data.split("/");
    stringstream stream;
    int num;
    if (windowChoice != 0)//初始界面无判断
    {
        if (!tag)//未登录，进行登录校验
        {
            if (data[0] == "1")//用户登录校验成功
            {
                tag = true;
                stream << Account::qTos(List1[6]);
                stream >> Balance;
                delete user;
                user = nullptr;
                user = new User(Account::qTos(List1[1]), Account::qTos(List1[3]),
                    Account::qTos(List1[4]), Account::qTos(List1[2]), Account::qTos(List1[5]));
                user->setBalance(Balance);
                ui->stackedWidget->setCurrentIndex(windowChoice);//进入对应操作界面
                this->setFixedSize(1660, 1030);
                move(125, 0);
            }
            else if (data[0] == "2") {
                tag = true;
                stream << Account::qTos(List1[6]);
                stream >> Balance;
                manager->setName(Account::qTos(List1[3]));
                manager->setNumber(Account::qTos(List1[4]));
                manager->setCompany(Account::qTos(List1[5]));
                manager->setBalance(Balance);
                ui->stackedWidget->setCurrentIndex(windowChoice);//进入对应操作界面
                this->setFixedSize(1660, 1030);
                move(125, 0);
            }
            else if (data[0] == "3") {
                tag = true;
                stream << Account::qTos(List1[6]);
                stream >> Balance;
                courier->setName(Account::qTos(List1[3]));
                courier->setNumber(Account::qTos(List1[4]));
                courier->setCompany(Account::qTos(List1[5]));
                courier->setBalance(Balance);
                ui->stackedWidget->setCurrentIndex(windowChoice);//进入对应操作界面
                this->setFixedSize(1660, 1030);
                move(125, 0);
            }
            else if (data[0] == "4" || data[0] == "5")
                tag = true;
            else//失败提示
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "账号或密码错误！ ");
                message.exec();
            }
        }
        else {
            switch (showChoice)
            {
            case 0://快递查询窗口
            {
                LGoods.clear();
                for (auto s : List1)
                {
                    Goods temp;
                    QStringList List2 = s.split("*");
                    stream.clear();
                    if (List2.size() != 12)
                        break;
                    temp.setExpressNumber(Account::qTos(List2[0]));
                    temp.setType(Account::qTos(List2[1]));
                    temp.setState(Account::qTos(List2[2]));
                    stream << Account::qTos(List2[3]);
                    stream >> num;
                    temp.setNumber(num);
                    temp.setSendTime(Account::qTos(List2[4]));
                    temp.setCollectTime(Account::qTos(List2[5]));
                    temp.setReceiveTime(Account::qTos(List2[6]));
                    temp.setSender(Account::qTos(List2[7]));
                    temp.setCourier(Account::qTos(List2[8]));
                    temp.setRecipient(Account::qTos(List2[9]));
                    temp.setDecription(Account::qTos(List2[10]));
                    temp.setCompany(Account::qTos(List2[11]));
                    LGoods.push_back(temp);
                }
            }break;
            case 1://用户信息窗口
            {
                LUsers.clear();
                if (windowChoice == 6&&List1.size()!=0)//当用户操作时启用
                {
                    QStringList List2 = List1[0].split("*");
                    user->setPassword(Account::qTos(List2[1]));
                    user->setName(Account::qTos(List2[2]));
                    user->setNumber(Account::qTos(List2[3]));
                    user->setAddress(Account::qTos(List2[4]));
                    stream.clear();
                    stream << Account::qTos(List2[5]);
                    stream >> Balance;
                    user->setBalance(Balance);
                }
                for (auto s : List1)
                {
                    User temp;
                    stream.clear();
                    QStringList List2 = s.split("*");
                    if (List2.size() != 6)
                        break;
                    temp.setUserName(Account::qTos(List2[0]));
                    temp.setPassword(Account::qTos(List2[1]));
                    temp.setName(Account::qTos(List2[2]));
                    temp.setNumber(Account::qTos(List2[3]));
                    temp.setAddress(Account::qTos(List2[4]));
                    stream << Account::qTos(List2[5]);
                    stream >> Balance;
                    temp.setBalance(Balance);
                    LUsers.push_back(temp);
                }
                
            }break;
            case 2://快递员信息窗口
            {
                LCourier.clear();
                if (windowChoice == 8 && List1.size() != 0)//当快递员操作时启用
                {
                    QStringList List2 = List1[0].split("*");
                    courier->setPassword(Account::qTos(List2[1]));
                    courier->setName(Account::qTos(List2[2]));
                    courier->setNumber(Account::qTos(List2[3]));
                    courier->setCompany(Account::qTos(List2[4]));
                    stream.clear();
                    stream << Account::qTos(List2[5]);
                    stream >> Balance;
                    courier->setBalance(Balance);
                }
                for (auto s : List1)
                {
                    Courier temp;
                    stream.clear();
                    QStringList List2 = s.split("*");
                    if (List2.size() != 6)
                        break;
                    temp.setUserName(Account::qTos(List2[0]));
                    temp.setPassword(Account::qTos(List2[1]));
                    temp.setName(Account::qTos(List2[2]));
                    temp.setNumber(Account::qTos(List2[3]));
                    temp.setCompany(Account::qTos(List2[4]));
                    stream << Account::qTos(List2[5]);
                    stream >> Balance;
                    temp.setBalance(Balance);
                    LCourier.push_back(temp);
                }
            }break;
            case 3://余额查询
            {
                stream << Account::qTos(List1[0]);
                stream >> Balance;
            }break;
            case 4://管理员信息查询
            {
                manager->setPassword(Account::qTos(List1[1]));
                manager->setName(Account::qTos(List1[2]));
                manager->setNumber(Account::qTos(List1[3]));
                manager->setCompany(Account::qTos(List1[4]));
                stream.clear();
                stream << Account::qTos(List1[5]);
                stream >> num;
                manager->setBalance(num);
            }break;
            case 5:
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", List1[0]);
                message.exec();
            }break;
            case 6: {
                if(windowChoice==4)
                ui->tip1_1->setText(List1[0]);
                else
                ui->tip1_2->setText(List1[0]);
            }break;
            }
        }
    }
}
/*
* 返回主页面前，清空账号数据
*/
void client::messageClear()
{
    LGoods.clear();
    LUsers.clear();
    LCourier.clear();
    Balance = 0;
    tag = false;
    if (user != nullptr)
    {
        delete user;
        user = nullptr;
    }
    if (manager != nullptr)
    {
        delete manager;
        manager = nullptr;
    }
    if (courier != nullptr)
    {
        delete courier;
        courier = nullptr;
    }
    ui->tableWidget->clear();//及时情况数据表格
    ui->tableWidget_2->clear();
    ui->tableWidget_3->clear();
    ui->lineEdit->clear();//清空搜索栏信息
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->username1->clear();
    ui->password1->clear();
    ui->username2->clear();
    ui->password2->clear();
    ui->username3->clear();
    ui->password3->clear();
    ui->username_5->clear();
    ui->password_5->clear();
    ui->confirmPassword_5->clear();
    ui->name_5->clear();
    ui->number_5->clear();
    ui->username_4->clear();
    ui->password_4->clear();
    ui->confirmPassword_4->clear();
    ui->name_4->clear();
    ui->number_4->clear();
    ui->address_4->clear();
    this->setFixedSize(600, 500);
    move(650, 250);
}
/*
* 转到用户登录页面
*/
void client::on_Userlogin_clicked()
{
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(1);
}
/*
* 转到管理员登录页面
*/
void client::on_Managerlogin_clicked()
{
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(2);
}
/*
* 转到快递员登录界面
*/
void client::on_Courierlogin_clicked()
{
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(3);
}
/*
* 转到用户注册界面
*/
void client::on_UserRegister_clicked()
{
    this->setFixedSize(700, 600);
    ui->stackedWidget->setCurrentIndex(4);
    QString buffer = "4";
    windowChoice = 4;
    tcp->write(buffer.toUtf8());//发送转移信号
    tcp->flush();
}
/*
* 转到快递员注册界面
*/
void client::on_CourierRegister_clicked()
{
    this->setFixedSize(700, 600);
    ui->stackedWidget->setCurrentIndex(5);
    QString buffer = "5";
    windowChoice = 5;
    tcp->write(buffer.toUtf8());//发送转移信号
    tcp->flush();
}
/*
* 用户登录页面，登录按钮
*/
void client::on_UserLoginWindow_login()
{
    QString buffer;
    user = new User(Account::qTos(ui->username1->text()), Account::qTos(ui->password1->text()));
    buffer.append("1*");
    buffer.append(ui->username1->text() + "*");
    buffer.append(ui->password1->text());
    ui->username_9->setText(Account::sToq(user->getUserName()));
    tcp->write(buffer.toUtf8());
    tcp->flush();
    windowChoice = 6;
}
/*
* 用户操作窗口 搜索按钮
*/
void client::on_findAllMessage_user()
{
    if (item_t->checkState(0) == Qt::Checked)
    {
        if (showChoice == 0)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(1); //设置行数
            ui->tableWidget->setColumnCount(12); //设置列数
            QStringList header;
            header << "快递单号" << "快递类型" << "快递状态" << "数量（kg/本）" << "发送时间" << "揽收时间"
                << "签收时间" << "寄件人" << "快递员" << "收件人" << "快递描述" << "承运公司";
            ui->tableWidget->setHorizontalHeaderLabels(header);
            ui->tableWidget->setRowCount(LGoods.size());
            if (LGoods.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递信息！ ");
                message.exec();
            }
            else
            {
                for (int i = 0; i < LGoods.size(); i++)
                {
                    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(Account::sToq(LGoods[i].getExpressNumber())));
                    ui->tableWidget->setItem(i, 1, new QTableWidgetItem(Account::sToq(LGoods[i].getType(2))));
                    ui->tableWidget->setItem(i, 2, new QTableWidgetItem(Account::sToq(LGoods[i].getState(2))));
                    ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(LGoods[i].getNumber())));
                    ui->tableWidget->setItem(i, 4, new QTableWidgetItem(Account::sToq(LGoods[i].getSendTime(1))));
                    ui->tableWidget->setItem(i, 5, new QTableWidgetItem(Account::sToq(LGoods[i].getCollectTime(1))));
                    ui->tableWidget->setItem(i, 6, new QTableWidgetItem(Account::sToq(LGoods[i].getReceiveTime(1))));
                    ui->tableWidget->setItem(i, 7, new QTableWidgetItem(Account::sToq(LGoods[i].getSender())));
                    ui->tableWidget->setItem(i, 8, new QTableWidgetItem(Account::sToq(LGoods[i].getCourier())));
                    ui->tableWidget->setItem(i, 9, new QTableWidgetItem(Account::sToq(LGoods[i].getRecipient())));
                    ui->tableWidget->setItem(i, 10, new QTableWidgetItem(Account::sToq(LGoods[i].getDescribtion())));
                    ui->tableWidget->setItem(i, 11, new QTableWidgetItem(Account::sToq(LGoods[i].getCompany())));
                }
            }
        }
        else if(showChoice==1) {
            ui->tableWidget->setRowCount(1); //设置行数
            ui->tableWidget->setColumnCount(6); //设置列数
            QStringList header;
            header << "用户名" << "密码" << "姓名" << "电话号码" << "地址" << "余额";
            ui->tableWidget->setHorizontalHeaderLabels(header);
            ui->tableWidget->setRowCount(1);
            for (int i = 0; i < LUsers.size(); i++)
            {
                ui->tableWidget->setItem(0, 0, new QTableWidgetItem(Account::sToq(LUsers[i].getUserName())));
                ui->tableWidget->setItem(0, 1, new QTableWidgetItem(Account::sToq(LUsers[i].getPassword())));
                ui->tableWidget->setItem(0, 2, new QTableWidgetItem(Account::sToq(LUsers[i].getName())));
                ui->tableWidget->setItem(0, 3, new QTableWidgetItem(Account::sToq(LUsers[i].getNumber())));
                ui->tableWidget->setItem(0, 4, new QTableWidgetItem(Account::sToq(LUsers[i].getBalance(1))));
                ui->tableWidget->setItem(0, 5, new QTableWidgetItem(Account::sToq(LUsers[i].getAddress())));
            }
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "当前余额： " + Account::sToq(to_string(Balance)) + "元");
            message.exec();
        }
        item_t->setCheckState(0, Qt::Unchecked);
    }
}
/*
* 用户操作窗口树表选择
*/
void client::on_userWindowcheck_clicked(QTreeWidgetItem* item, int column)
{
    showChoice = 0;
    QString buffer;//待发送指令与数据集
    stringstream stream;
    int num;
    stream << Account::qTos(item->text(1));
    stream >> num;
    if (item_t != item)
        item_t->setCheckState(0, Qt::Unchecked);//取消上个按钮的选中（避免多选）
    if (item->checkState(0) == Qt::Checked)
        buffer.append(item->text(1) + "*");
    if (num == 3 || (num >= 9 && num <= 11))//发送编号、姓名参数
        buffer.append(ui->lineEdit->text());
    else if (num >= 5 && num <= 7)//发送时间参数
        buffer.append(ui->year->text() + "*"
            + ui->month->text() + "*"
            + ui->day->text());
    if (num == 13)
        showChoice = 1;
    if (num == 14)
        showChoice = 3;
    tcp->write(buffer.toUtf8());//发送查询指令
    tcp->flush();
    item_t = item;
}
/*
* 用户操作窗口 修改账号信息按钮
*/
void client::on_userWindowChangeMessage_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入:"));
    // 修改密码
    QString password = QString("新密码（8~16位）: ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Password);
    lineEdit1->setText(Account::sToq(user->getPassword()));
    form.addRow(password, lineEdit1);
    //请确认新密码
    QLineEdit* lineEdit5 = new QLineEdit(&dialog);
    lineEdit5->setEchoMode(QLineEdit::Password);
    lineEdit5->setText(Account::sToq(user->getPassword()));
    form.addRow(password, lineEdit5);
    // 修改姓名
    QString name = QString("新姓名: ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setText(Account::sToq(user->getName()));
    form.addRow(name, lineEdit2);
    //修改电话号码
    QString number = QString("新电话号码（11位）: ");
    QLineEdit* lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setText(Account::sToq(user->getNumber()));
    form.addRow(number, lineEdit3);
    //修改地址
    QString address = QString("新地址: ");
    QLineEdit* lineEdit4 = new QLineEdit(&dialog);
    lineEdit4->setText(Account::sToq(user->getAddress()));
    form.addRow(address, lineEdit4);
    // 添加OK键和Cancel键
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // 当OK键被按下
    if (dialog.exec() == QDialog::Accepted) {
        if (lineEdit1->text() != lineEdit5->text())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "两次密码不一致！！ ");
            message.exec();
        }
        else if (lineEdit1->text().size() > 16 || lineEdit1->text().size() < 8)
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "密码长度不符合规范 ！！");
            message.exec();
        }
        else if (11 != lineEdit3->text().size())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "电话号码长度不符合规范 ！！");
            message.exec();
        }
        else if (lineEdit1->text().contains("*") || lineEdit2->text().contains("*") ||
            lineEdit3->text().contains("*") || lineEdit4->text().contains("*"))
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "各项信息中不可包括 * 字符！！ ");
            message.exec();
        }
        else {
            user->setPassword(Account::qTos(lineEdit1->text()));
            user->setName(Account::qTos(lineEdit2->text()));
            user->setNumber(Account::qTos(lineEdit3->text()));
            user->setAddress(Account::qTos(lineEdit4->text()));
            QString buffer;
            buffer.append(Account::sToq("15*" + user->getPassword() + "*"
                + user->getName() + "*" + user->getNumber() + "*" + user->getAddress()));
            tcp->write(buffer.toUtf8());
            tcp->flush();
            showChoice = 5;
        //    QMessageBox message(QMessageBox::NoIcon, "Tip", "修改成功！");
           // message.exec();
        }
    }
}
/*
* 发送快递
*/
void client::on_sendExpress_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入:"));
    // 设置快递类型
    QString type = QString("快递类型： ");
    QComboBox* combox1 = new QComboBox(&dialog);
    combox1->addItem("普通快递");
    combox1->addItem("书本");
    combox1->addItem("易碎品");
    form.addRow(type, combox1);
    //请输入物品描述
    QString description = QString("物品描述: ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    form.addRow(description, lineEdit1);
    //修改电话号码
    QString name = QString("收件人用户名: ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    form.addRow(name, lineEdit2);
    // 设置快递类型
    QString company = QString("快递公司： ");
    QComboBox* combox2 = new QComboBox(&dialog);
    combox2->addItem("顺丰");
    combox2->addItem("邮政");
    combox2->addItem("京东");
    combox2->addItem("韵达");
    combox2->addItem("申通");
    combox2->addItem("圆通");
    form.addRow(company, combox2);
    //输入商品量（本/kg)
    QString num = QString("快递重量/数量（不足1kg按1kg计算）： ");
    QLineEdit* lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setValidator(new QIntValidator(1, 100, this));
    form.addRow(num, lineEdit3);
    // 添加OK键和Cancel键
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // 当OK键被按下
    if (dialog.exec() == QDialog::Accepted)
    {
        if (lineEdit1->text().isEmpty() || lineEdit1->text().isEmpty() || lineEdit1->text().isEmpty())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "各项信息中不可为空！！ ");
            message.exec();
        }
        else if (lineEdit1->text().contains("*") || lineEdit2->text().contains("*") || lineEdit3->text().contains("*"))
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "各项信息中不可包括 * 字符！！ ");
            message.exec();
        }
        else {
            QString buffer;
            buffer.append("16*");
            buffer.append(combox1->currentText() + "*" + lineEdit1->text() + "*" +
                lineEdit2->text() + "*" + combox2->currentText() + "*" +
                Account::sToq(to_string(combox1->currentIndex())) + "*" + lineEdit3->text());
            tcp->write(buffer.toUtf8());
            tcp->flush();
        }
    }
    showChoice= 5;
}
/*
* 签收快递
*/
void client::on_signExpress_clicked()
{
    QString buffer;
    buffer.append("17*");
    buffer.append(ui->lineEdit->text());
    tcp->write(buffer.toUtf8());
    tcp->flush();
    showChoice = 5;
}
/*
* 账户充值
*/
void client::on_recharge_clicked()
{
    bool judge;
    // 获取整数
    double value = QInputDialog::getDouble(this, tr("充值栏"), tr("请充值："), 100, 0, 1000, 10, &judge);
    if (judge)
    {
        user->setBalance(user->getBalance() + value);
        QString buffer = "18*" + QString::number(value);
        tcp->write(buffer.toUtf8());
        tcp->flush();
    }
    showChoice = 5;
}
/*
* 管理员登录页面，登录按钮
*/
void client::on_ManagerLoginWindow_login()
{
    QString buffer;
    manager = new Manager(Account::qTos(ui->username2->text()), Account::qTos(ui->password2->text()));
    buffer.append("2*");
    buffer.append(ui->username2->text() + "*");
    buffer.append(ui->password2->text());
    ui->username_10->setText(Account::sToq(manager->getUserName()));
    tcp->write(buffer.toUtf8());
    tcp->flush();
    windowChoice = 7;
}
/*
* 管理员操作窗口 搜索按钮
*/
void client::on_findAllMessage_manager()
{
    if (item_t->checkState(0) == Qt::Checked)
    {
        if (showChoice == 0)
        {
            ui->tableWidget_2->clear();
            ui->tableWidget_2->setRowCount(1); //设置行数
            ui->tableWidget_2->setColumnCount(12); //设置列数
            QStringList header;
            header << "快递单号" << "快递类型" << "快递状态" << "数量（kg/本）" << "发送时间" << "揽收时间"
                << "签收时间" << "寄件人" << "快递员" << "收件人" << "快递描述" << "承运公司";
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setRowCount(LGoods.size());
            if (LGoods.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递信息！ ");
                message.exec();
            }
            else
            {
                for (int i = 0; i < LGoods.size(); i++)
                {
                    ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(Account::sToq(LGoods[i].getExpressNumber())));
                    ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(Account::sToq(LGoods[i].getType(2))));
                    ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(Account::sToq(LGoods[i].getState(2))));
                    ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(QString::number(LGoods[i].getNumber())));
                    ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(Account::sToq(LGoods[i].getSendTime(1))));
                    ui->tableWidget_2->setItem(i, 5, new QTableWidgetItem(Account::sToq(LGoods[i].getCollectTime(1))));
                    ui->tableWidget_2->setItem(i, 6, new QTableWidgetItem(Account::sToq(LGoods[i].getReceiveTime(1))));
                    ui->tableWidget_2->setItem(i, 7, new QTableWidgetItem(Account::sToq(LGoods[i].getSender())));
                    ui->tableWidget_2->setItem(i, 8, new QTableWidgetItem(Account::sToq(LGoods[i].getCourier())));
                    ui->tableWidget_2->setItem(i, 9, new QTableWidgetItem(Account::sToq(LGoods[i].getRecipient())));
                    ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem(Account::sToq(LGoods[i].getDescribtion())));
                    ui->tableWidget_2->setItem(i, 11, new QTableWidgetItem(Account::sToq(LGoods[i].getCompany())));
                }
            }
        }
        else if (showChoice == 1) {
            ui->tableWidget_2->setRowCount(1); //设置行数
            ui->tableWidget_2->setColumnCount(6); //设置列数
            QStringList header;
            header << "用户名" << "密码" << "姓名" << "电话号码" << "余额" << "地址";
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setRowCount(LUsers.size());
            if (LUsers.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "无用户信息！ ");
                message.exec();
            }
            for (int i = 0; i < LUsers.size(); i++)
            {
                ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(Account::sToq(LUsers[i].getUserName())));
                ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(Account::sToq(LUsers[i].getPassword())));
                ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(Account::sToq(LUsers[i].getName())));
                ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(Account::sToq(LUsers[i].getNumber())));
                ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(Account::sToq(LUsers[i].getBalance(1))));
                ui->tableWidget_2->setItem(i, 5, new QTableWidgetItem(Account::sToq(LUsers[i].getAddress())));
            }
        }
        else if(showChoice==2) {
            ui->tableWidget_2->setRowCount(1); //设置行数
            ui->tableWidget_2->setColumnCount(6); //设置列数
            QStringList header;
            header << "用户名" << "密码" << "姓名" << "电话号码" << "余额" << "快递公司" ;
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setRowCount(LCourier.size());
            if (LCourier.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递员信息！ ");
                message.exec();
            }
            for (int i = 0; i < LCourier.size(); i++)
            {
                ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(Account::sToq(LCourier[i].getUserName())));
                ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(Account::sToq(LCourier[i].getPassword())));
                ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(Account::sToq(LCourier[i].getName())));
                ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(Account::sToq(LCourier[i].getNumber())));
                ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(Account::sToq(LCourier[i].getBalance(1))));
                ui->tableWidget_2->setItem(i, 5, new QTableWidgetItem(Account::sToq(LCourier[i].getCompany())));
            }
        }
        else if (showChoice == 4)
        {
            ui->tableWidget_2->setRowCount(1); //设置行数
            ui->tableWidget_2->setColumnCount(6); //设置列数
            QStringList header;
            header << "用户名" << "密码" << "姓名" << "电话号码" << "余额" << "快递公司";
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem(Account::sToq(manager->getUserName())));
            ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(Account::sToq(manager->getPassword())));
            ui->tableWidget_2->setItem(0, 2, new QTableWidgetItem(Account::sToq(manager->getName())));
            ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem(Account::sToq(manager->getNumber())));
            ui->tableWidget_2->setItem(0, 4, new QTableWidgetItem(Account::sToq(manager->getBalance(1))));
            ui->tableWidget_2->setItem(0, 5, new QTableWidgetItem(Account::sToq(manager->getCompany())));                                                                
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "当前余额： " + Account::sToq(to_string(Balance)) + "元");
            message.exec();
        }
        item_t->setCheckState(0, Qt::Unchecked);
    }
}
/*
* 管理员操作窗口树表选择
*/
void client::on_managerWindowcheck_clicked(QTreeWidgetItem* item, int column) {
    showChoice = 0;
    QString buffer;//待发送指令与数据集
    stringstream stream;
    int num;
    stream << Account::qTos(item->text(1));
    stream >> num;
    if (item_t != item)
        item_t->setCheckState(0, Qt::Unchecked);//取消上个按钮的选中（避免多选）
    if (item->checkState(0) == Qt::Checked)
        buffer.append(item->text(1) + "*");
    if (num == 3 || (num >= 9 && num <= 11)||num==17||num==19)//发送编号、姓名参数
        buffer.append(ui->lineEdit_2->text());
    else if (num >= 5 && num <= 7)//发送时间参数
        buffer.append(ui->year_2->text() + "*"
            + ui->month_2->text() + "*"
            + ui->day_2->text());
    if (num <= 15)
        showChoice = 0;
    else if (num <= 17)
        showChoice = 1;
    else if (num <= 20)
        showChoice = 2;
    else if (num == 21)
        showChoice = 4;
    else if (num == 22)
        showChoice = 3;
    else
        showChoice = 5;
    tcp->write(buffer.toUtf8());//发送查询指令
    tcp->flush();
    item_t = item;
}
/*
* 快递员添加
*/
void client::on_addCourier_clicked()
{
    QString buffer = "24*";
    buffer.append(ui->lineEdit_2->text());
    tcp->write(buffer.toUtf8());
    tcp->flush();
    showChoice = 5;
}
/*
* 快递员删除
*/
void client::on_deleteCourier_clicked()
{
    QString buffer = "25*";
    buffer.append(ui->lineEdit_2->text());
    tcp->write(buffer.toUtf8());
    tcp->flush();
    showChoice = 5;
}
/*
* 快递任务分配
*/
void client::on_distributionExpress_clicked()
{
    QString buffer = "26*";
    Goods good;//待签收快递
    QDialog dialog(this);
    dialog.setObjectName("快递分配");
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入:"));
    // 设置快递类型
    QString expressNumber = QString("快递编号： ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    form.addRow(expressNumber, lineEdit1);

    QString name = QString("快递员用户名： ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    form.addRow(name, lineEdit2);
    // 添加OK键和Cancel键
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // 当OK键被按下
    if (dialog.exec() == QDialog::Accepted)
    {
        buffer.append(lineEdit1->text()+"*");
        buffer.append(lineEdit2->text());
        tcp->write(buffer.toUtf8());
        tcp->flush();
        showChoice = 5;
    }
}
/*
*/
void client::on_CourierLoginWindow_login()
{
    QString buffer;
    courier = new Courier(Account::qTos(ui->username3->text()), Account::qTos(ui->password3->text()));
    buffer.append("3*");
    buffer.append(ui->username3->text() + "*");
    buffer.append(ui->password3->text());
    ui->username_11->setText(Account::sToq(courier->getUserName()));
    tcp->write(buffer.toUtf8());
    tcp->flush();
    windowChoice = 8;
}
/*
* 快递员操作窗口 搜索按钮
*/
void client::on_findAllMessage_courier()
{
    if (item_t->checkState(0) == Qt::Checked)
    {
        if (showChoice == 0)
        {
            ui->tableWidget_3->clear();
            ui->tableWidget_3->setRowCount(1); //设置行数
            ui->tableWidget_3->setColumnCount(12); //设置列数
            QStringList header;
            header << "快递单号" << "快递类型" << "快递状态" << "数量（kg/本）" << "发送时间" << "揽收时间"
                << "签收时间" << "寄件人" << "快递员" << "收件人" << "快递描述" << "承运公司";
            ui->tableWidget_3->setHorizontalHeaderLabels(header);
            ui->tableWidget_3->setRowCount(LGoods.size());
            if (LGoods.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "无快递信息！ ");
                message.exec();
            }
            else
            {
                for (int i = 0; i < LGoods.size(); i++)
                {
                    ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(Account::sToq(LGoods[i].getExpressNumber())));
                    ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(Account::sToq(LGoods[i].getType(2))));
                    ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(Account::sToq(LGoods[i].getState(2))));
                    ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(QString::number(LGoods[i].getNumber())));
                    ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(Account::sToq(LGoods[i].getSendTime(1))));
                    ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(Account::sToq(LGoods[i].getCollectTime(1))));
                    ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(Account::sToq(LGoods[i].getReceiveTime(1))));
                    ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(Account::sToq(LGoods[i].getSender())));
                    ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(Account::sToq(LGoods[i].getCourier())));
                    ui->tableWidget_3->setItem(i, 9, new QTableWidgetItem(Account::sToq(LGoods[i].getRecipient())));
                    ui->tableWidget_3->setItem(i, 10, new QTableWidgetItem(Account::sToq(LGoods[i].getDescribtion())));
                    ui->tableWidget_3->setItem(i, 11, new QTableWidgetItem(Account::sToq(LGoods[i].getCompany())));
                }
            }
        }
        else if (showChoice == 2) {
            ui->tableWidget_3->setRowCount(1); //设置行数
            ui->tableWidget_3->setColumnCount(6); //设置列数
            QStringList header;
            header << "用户名" << "密码" << "姓名" << "电话号码" << "余额" << "快递公司";
            ui->tableWidget_3->setHorizontalHeaderLabels(header);
            ui->tableWidget_3->setRowCount(LCourier.size());
            for (int i = 0; i < LCourier.size(); i++)
            {
                ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(Account::sToq(LCourier[i].getUserName())));
                ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(Account::sToq(LCourier[i].getPassword())));
                ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(Account::sToq(LCourier[i].getName())));
                ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(Account::sToq(LCourier[i].getNumber())));
                ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(Account::sToq(LCourier[i].getBalance(1))));
                ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(Account::sToq(LCourier[i].getCompany())));
            }
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "当前余额： " + Account::sToq(to_string(Balance)) + "元");
            message.exec();
        }
        item_t->setCheckState(0, Qt::Unchecked);
    }
}
/*
* 快递员操作窗口树表选择
*/
void client::on_courierWindowcheck_clicked(QTreeWidgetItem* item, int column)
{
    showChoice = 0;
    QString buffer;//待发送指令与数据集
    stringstream stream;
    int num;
    stream << Account::qTos(item->text(1));
    stream >> num;
    if (item_t != item)
        item_t->setCheckState(0, Qt::Unchecked);//取消上个按钮的选中（避免多选）
    if (item->checkState(0) == Qt::Checked)
        buffer.append(item->text(1) + "*");
    if (num == 3 || (num >= 9 && num <= 11))//发送编号、姓名参数
        buffer.append(ui->lineEdit_3->text());
    else if (num >= 5 && num <= 7)//发送时间参数
        buffer.append(ui->year_3->text() + "*"
            + ui->month_3->text() + "*"
            + ui->day_3->text());
    if (num == 16)
        showChoice = 2;
    else if (num == 17)
        showChoice = 3;
    tcp->write(buffer.toUtf8());//发送查询指令
    tcp->flush();
    item_t = item;
}
/*
* 快递员操作窗口 修改账号信息按钮
*/
void client::on_courierWindowChangeMessage_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入:"));
    // 修改密码
    QString password = QString("新密码（8~16位）: ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Password);
    lineEdit1->setText(Account::sToq(courier->getPassword()));
    form.addRow(password, lineEdit1);
    //请确认新密码
    QLineEdit* lineEdit5 = new QLineEdit(&dialog);
    lineEdit5->setEchoMode(QLineEdit::Password);
    lineEdit5->setText(Account::sToq(courier->getPassword()));
    form.addRow(password, lineEdit5);
    // 修改姓名
    QString name = QString("新姓名: ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setText(Account::sToq(courier->getName()));
    form.addRow(name, lineEdit2);
    //修改电话号码
    QString number = QString("新电话号码（11位）: ");
    QLineEdit* lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setText(Account::sToq(courier->getNumber()));
    form.addRow(number, lineEdit3);
    //公司和余额不可修改
    // 添加OK键和Cancel键
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // 当OK键被按下
    if (dialog.exec() == QDialog::Accepted) {
        if (lineEdit1->text() != lineEdit5->text())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "两次密码不一致！！ ");
            message.exec();
        }
        else if (lineEdit1->text().size() > 16 || lineEdit1->text().size() < 8)
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "密码长度不符合规范 ！！");
            message.exec();
        }
        else if (11 != lineEdit3->text().size())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "电话号码长度不符合规范 ！！");
            message.exec();
        }
        else if (lineEdit1->text().contains("*") || lineEdit2->text().contains("*") ||
            lineEdit3->text().contains("*"))
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "各项信息中不可包括 * 字符！！ ");
            message.exec();
        }
    }
        else {
            courier->setPassword(Account::qTos(lineEdit1->text()));
            courier->setName(Account::qTos(lineEdit2->text()));
            courier->setNumber(Account::qTos(lineEdit3->text()));
            QString buffer;
            buffer.append(Account::sToq("18*" + courier->getPassword() + "*"
                + courier->getName() + "*" + courier->getNumber()));
            tcp->write(buffer.toUtf8());
            tcp->flush();
            QMessageBox message(QMessageBox::NoIcon, "Tip", "修改成功！");
            message.exec();
        }
        showChoice = 5;
}
   
/*
* 快递操作窗口 揽收快递
*/
void client::on_collectExpress_clicked()
{
    QString buffer = "19*";
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入:"));
    // 设置快递类型
    QString expressNumber = QString("快递单号： ");
    QLineEdit* lineEdit = new QLineEdit(&dialog);
    form.addRow(expressNumber, lineEdit);
    // 添加OK键和Cancel键
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // 当OK键被按下
    if (dialog.exec() == QDialog::Accepted)
    {
        buffer.append(lineEdit->text());
        tcp->write(buffer.toUtf8());
        tcp->flush();
        showChoice = 5;
    }
}

/**
* 返回主界面
*/
void client::on_returnChooseWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//返回主页面
    messageClear();//清空原数据
    tcp->write(QString::number(windowChoice+20).toUtf8());
    tcp->flush();
    windowChoice = 0;
}
/*
* 初始化用户界面
*/
void client::init_UserWindow()
{
    connect(ui->login1, &QPushButton::clicked, this, &client::on_UserLoginWindow_login);//用户登录界面登录按钮槽连接
    connect(ui->search, &QPushButton::clicked, this, &client::on_findAllMessage_user);//用户操作界面搜索按钮槽连接
    connect(ui->changeMessage1, &QPushButton::clicked, this, &client::on_userWindowChangeMessage_clicked);//用户操作界面修改信息按钮
    connect(ui->sendExpress, SIGNAL(clicked()), this, SLOT(on_sendExpress_clicked()), Qt::UniqueConnection);//发送快递按钮槽连接
    connect(ui->recharge, SIGNAL(clicked()), this, SLOT(on_recharge_clicked()), Qt::UniqueConnection);//充值按钮槽连接
    connect(ui->sign, &QPushButton::clicked, this, &client::on_signExpress_clicked);//签收按钮槽连接
    //界面初始化代码块（树表）用户操作界面
    {
        QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget);
        topItem1->setText(0, "1.查询所有快递信息");
        topItem1->setText(1, "1");
        topItem1->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem1);

        QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget);
        topItem2->setText(0, "2. 查询指定快递信息");
        topItem2->setText(1, "2");
        ui->treeWidget->addTopLevelItem(topItem2);

        QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
        item21->setText(0, "2.1 根据快递编号查询");
        item21->setCheckState(0, Qt::Unchecked);
        item21->setText(1, "3");

        QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
        item22->setText(0, "2.2 根据快递时间查询");
        item22->setText(1, "4");

        QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
        item221->setText(0, "2.2.1 根据寄件时间查询");
        item221->setCheckState(0, Qt::Unchecked);
        item221->setText(1, "5");

        QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
        item222->setText(0, "2.2.2 根据揽收时间查询");
        item222->setCheckState(0, Qt::Unchecked);
        item222->setText(1, "6");

        QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
        item223->setText(0, "2.2.3根据收件时间查询");
        item223->setCheckState(0, Qt::Unchecked);
        item223->setText(1, "7");

        QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
        item23->setText(0, "2.3 根据用户查询");
        item23->setText(1, "8");

        QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
        item231->setText(0, "2.3.1根据寄件人查询");
        item231->setCheckState(0, Qt::Unchecked);
        item231->setText(1, "9");

        QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
        item232->setText(0, "2.3.2根据快递员查询");
        item232->setCheckState(0, Qt::Unchecked);
        item232->setText(1, "10");

        QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
        item233->setText(0, "2.3.3根据收件人查询");
        item233->setCheckState(0, Qt::Unchecked);
        item233->setText(1, "11");

        QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget);
        topItem3->setText(0, "3. 查询所有未签收快递信息");
        topItem3->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem3);
        topItem3->setText(1, "12");

        QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
        topItem4->setText(0, "4. 查询用户信息");
        topItem4->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem4);
        topItem4->setText(1, "13");

        QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget);
        topItem5->setText(0, "5. 查询余额");
        topItem5->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem5);
        topItem5->setText(1, "14");
        connect(ui->treeWidget, &QTreeWidget::itemClicked, this,
            &client::on_userWindowcheck_clicked);
    }
}
/*
* 初始化快递员界面
*/
void client::init_CourierWindow()
{
    connect(ui->login_3, &QPushButton::clicked, this, &client::on_CourierLoginWindow_login);//快递员登录界面登录按钮槽连接
    connect(ui->search_3, &QPushButton::clicked, this, &client::on_findAllMessage_courier);//快递员操作界面搜索按钮槽连接
    connect(ui->collect, SIGNAL(clicked()), this, SLOT(on_collectExpress_clicked()), Qt::UniqueConnection);//快递员操作界面，揽收快递;;
    connect(ui->changeMessage3, &QPushButton::clicked, this, &client::on_courierWindowChangeMessage_clicked);//用户操作界面修改信息按钮
    //界面初始化代码块（树表）快递员操作界面
    {
        QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem1->setText(0, "1.查询所有快递信息");
        topItem1->setText(1, "1");
        topItem1->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_3->addTopLevelItem(topItem1);

        QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem2->setText(0, "2. 查询指定快递信息");
        topItem2->setText(1, "2");
        ui->treeWidget_3->addTopLevelItem(topItem2);

        QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
        item21->setText(0, "2.1 根据快递编号查询");
        item21->setCheckState(0, Qt::Unchecked);
        item21->setText(1, "3");

        QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
        item22->setText(0, "2.2 根据快递时间查询");
        item22->setText(1, "4");

        QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
        item221->setText(0, "2.2.1 根据寄件时间查询");
        item221->setCheckState(0, Qt::Unchecked);
        item221->setText(1, "5");

        QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
        item222->setText(0, "2.2.2 根据揽收时间查询");
        item222->setCheckState(0, Qt::Unchecked);
        item222->setText(1, "6");

        QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
        item223->setText(0, "2.2.3根据收件时间查询");
        item223->setCheckState(0, Qt::Unchecked);
        item223->setText(1, "7");

        QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
        item23->setText(0, "2.3 根据用户查询");
        item23->setText(1, "8");

        QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
        item231->setText(0, "2.3.1根据寄件人查询");
        item231->setCheckState(0, Qt::Unchecked);
        item231->setText(1, "9");

        QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
        item232->setText(0, "2.3.2根据快递员查询");
        item232->setCheckState(0, Qt::Unchecked);
        item232->setText(1, "10");

        QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
        item233->setText(0, "2.3.3根据收件人查询");
        item233->setCheckState(0, Qt::Unchecked);
        item233->setText(1, "11");

        QTreeWidgetItem* item24 = new QTreeWidgetItem(topItem2);
        item24->setText(0, "2.4 根据快递状态查询");
        item24->setText(1, "12");

        QTreeWidgetItem* item241 = new QTreeWidgetItem(item24);
        item241->setText(0, "2.4.1 查询所有未揽收快递");
        item241->setCheckState(0, Qt::Unchecked);
        item241->setText(1, "13");

        QTreeWidgetItem* item242 = new QTreeWidgetItem(item24);
        item242->setText(0, "2.4.2 查询所有未签收快递");
        item242->setCheckState(0, Qt::Unchecked);
        item242->setText(1, "14");

        QTreeWidgetItem* item243 = new QTreeWidgetItem(item24);
        item243->setText(0, "2.4.3 查询所有已签收快递");
        item243->setCheckState(0, Qt::Unchecked);
        item243->setText(1, "15");

        QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem3->setText(0, "3. 查询账号信息");
        topItem3->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_3->addTopLevelItem(topItem3);
        topItem3->setText(1, "16");

        QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem4->setText(0, "4. 查询余额");
        topItem4->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_3->addTopLevelItem(topItem4);
        topItem4->setText(1, "17");
        connect(ui->treeWidget_3, &QTreeWidget::itemClicked, this,
            &client::on_courierWindowcheck_clicked);
    }                                                                   //管理员操作界面搜索按钮槽连接

}
/*
* 初始化管理员界面
*/
void client::init_ManagerWindow()
{
    connect(ui->login2, &QPushButton::clicked, this, &client::on_ManagerLoginWindow_login);//管理员登录界面登录按钮槽连接
    connect(ui->search_2, &QPushButton::clicked, this, &client::on_findAllMessage_manager);//管理员操作界面搜索按钮槽连接
    connect(ui->addCourier, SIGNAL(clicked()), this, SLOT(on_addCourier_clicked()), Qt::UniqueConnection);//管理员添加快递员按钮
    connect(ui->deleteCourier, SIGNAL(clicked()), this, SLOT(on_deleteCourier_clicked()), Qt::UniqueConnection);//管理员删除快递员按钮
    connect(ui->distribution, &QPushButton::clicked, this, &client::on_distributionExpress_clicked);//管理员分配快递
    //界面初始化代码块（树表）管理员操作界面
    {
        QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem1->setText(0, "1.查询所有快递信息");
        topItem1->setText(1, "1");
        topItem1->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem1);

        QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem2->setText(0, "2. 查询指定快递信息");
        topItem2->setText(1, "2");
        ui->treeWidget_2->addTopLevelItem(topItem2);

        QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
        item21->setText(0, "2.1 根据快递编号查询");
        item21->setCheckState(0, Qt::Unchecked);
        item21->setText(1, "3");

        QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
        item22->setText(0, "2.2 根据快递时间查询");
        item22->setText(1, "4");

        QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
        item221->setText(0, "2.2.1 根据寄件时间查询");
        item221->setCheckState(0, Qt::Unchecked);
        item221->setText(1, "5");

        QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
        item222->setText(0, "2.2.2 根据揽收时间查询");
        item222->setCheckState(0, Qt::Unchecked);
        item222->setText(1, "6");

        QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
        item223->setText(0, "2.2.3根据收件时间查询");
        item223->setCheckState(0, Qt::Unchecked);
        item223->setText(1, "7");

        QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
        item23->setText(0, "2.3 根据用户查询");
        item23->setText(1, "8");

        QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
        item231->setText(0, "2.3.1根据寄件人查询");
        item231->setCheckState(0, Qt::Unchecked);
        item231->setText(1, "9");

        QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
        item232->setText(0, "2.3.2根据快递员查询");
        item232->setCheckState(0, Qt::Unchecked);
        item232->setText(1, "10");

        QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
        item233->setText(0, "2.3.3根据收件人查询");
        item233->setCheckState(0, Qt::Unchecked);
        item233->setText(1, "11");

        QTreeWidgetItem* item24 = new QTreeWidgetItem(topItem2);
        item24->setText(0, "2.4 根据快递状态查询");
        item24->setText(1, "12");

        QTreeWidgetItem* item241 = new QTreeWidgetItem(item24);
        item241->setText(0, "2.4.1 查询所有未揽收快递");
        item241->setCheckState(0, Qt::Unchecked);
        item241->setText(1, "13");

        QTreeWidgetItem* item242 = new QTreeWidgetItem(item24);
        item242->setText(0, "2.4.2 查询所有未签收快递");
        item242->setCheckState(0, Qt::Unchecked);
        item242->setText(1, "14");

        QTreeWidgetItem* item243 = new QTreeWidgetItem(item24);
        item243->setText(0, "2.4.3 查询所有已签收快递");
        item243->setCheckState(0, Qt::Unchecked);
        item243->setText(1, "15");
        QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget_2);

        topItem3->setText(0, "3. 查询所有用户信息");
        topItem3->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem3);
        topItem3->setText(1, "16");

        QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem4->setText(0, "4. 查询指定用户信息");
        topItem4->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem4);
        topItem4->setText(1, "17");

        QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem5->setText(0, "5. 查询所有快递员信息");
        topItem5->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem5);
        topItem5->setText(1, "18");

        QTreeWidgetItem* topItem6 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem6->setText(0, "6. 查询指定快递员信息");
        topItem6->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem6);
        topItem6->setText(1, "19");

        QTreeWidgetItem* topItem7 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem7->setText(0, "7. 查询所有可添加快递员信息");
        topItem7->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem7);
        topItem7->setText(1, "20");

        QTreeWidgetItem* topItem8 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem8->setText(0, "8. 查询管理员信息");
        topItem8->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem8);
        topItem8->setText(1, "21");

        QTreeWidgetItem* topItem9 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem9->setText(0, "9. 查询余额");
        topItem9->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem9);
        topItem9->setText(1, "22");
        connect(ui->treeWidget_2, &QTreeWidget::itemClicked, this,
            &client::on_managerWindowcheck_clicked);
    }
}
/*
* 初始化快递员注册界面
*/
void client::init_CourierRegister() {
    courier = new Courier();
    {
        connect(ui->username_5, &QLineEdit::editingFinished, this, &client::username_finished);//校验用户名
        connect(ui->password_5, &QLineEdit::editingFinished, this, &client::password_finished);//校验密码
        connect(ui->confirmPassword_5, &QLineEdit::editingFinished, this, &client::confirmPassword);//密码二次核对
        connect(ui->name_5, &QLineEdit::editingFinished, this, &client::name_finished);//校验姓名
        connect(ui->number_5, &QLineEdit::editingFinished, this, &client::number_finished);//校验电话号码
        connect(ui->confirm2, &QPushButton::clicked, this, &client::confirm_clicked);//退出按钮槽连接
        connect(ui->back_5, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//退出按钮槽连接
    }
}
/*
* 初始化用户注册界面
*/
void client::init_UserRegister() {
    user = new User();
    {
        connect(ui->username_4, &QLineEdit::editingFinished, this, &client::username_finished);//校验用户用户名
        connect(ui->password_4, &QLineEdit::editingFinished, this, &client::password_finished);//校验密码
        connect(ui->confirmPassword_4, &QLineEdit::editingFinished, this, &client::confirmPassword);//密码二次核对
        connect(ui->name_4, &QLineEdit::editingFinished, this, &client::name_finished);//校验姓名
        connect(ui->number_4, &QLineEdit::editingFinished, this, &client::number_finished);//校验电话号码
        connect(ui->address_4, &QLineEdit::editingFinished, this, &client::address_finished);//校验地址
        connect(ui->confirm1, &QPushButton::clicked, this, &client::confirm_clicked);//注册按钮槽连接
        connect(ui->back_4, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//退出按钮槽连接
    }
}
/*
* 用户名合理性校验
*/
void client::username_finished()
{
    if (windowChoice == 4)
    {
        if (ui->username_4->text().contains("*"))
            ui->tip1_1->setText("用户名中不可包含 * ！");
        else
        {
            tcp->write("1*");
            tcp->write(ui->username_4->text().toUtf8());
            tcp->flush();
        }
    }
    else {
        if (ui->username_5->text().contains("*"))
            ui->tip1_2->setText("用户名中不可包含 * ！");
        else
        {
            tcp->write("1*");
            tcp->write(ui->username_5->text().toUtf8());
            tcp->flush();
        }
    }
    showChoice = 6;
}
/*
* 密码合理性校验
*/
void client::password_finished() {
    if (windowChoice == 4)
    {
        if (!Account::checkPassword(Account::qTos(ui->password_4->text())))
            ui->tip2_1->setText("密码长度应为8~16位！");
        else if(ui->password_4->text().contains("*"))
            ui->tip2_1->setText("密码不得包含 * ！");
        else
            ui->tip2_1->setText("");
    }
    else 
    {
        if (!Account::checkPassword(Account::qTos(ui->password_5->text())))
            ui->tip2_2->setText("密码长度应为8~16位！");
        else if (ui->password_5->text().contains("*"))
            ui->tip2_2->setText("密码不得包含 * ！");
        else
            ui->tip2_2->setText("");
    }
}
/*
* 密码二次校验
*/
void client::confirmPassword()
{
    if (windowChoice == 4)
    {
        if (ui->password_4->text() != ui->confirmPassword_4->text())
            ui->tip3_1->setText("两次密码不一致！");
        else
            ui->tip3_1->setText("");
    }
    else {
        if (ui->password_5->text() != ui->confirmPassword_5->text())
            ui->tip3_2->setText("两次密码不一致！");
        else
            ui->tip3_2->setText("");
    }
}
/*
* 姓名合理性校验
*/
void client::name_finished()
{
    if (windowChoice == 4)
    {
        if (ui->name_4->text().isEmpty())
            ui->tip4_1->setText("姓名不可为空！");
        else if (ui->name_4->text().contains("*"))
            ui->tip4_1->setText("姓名不得包含 * ！");
        else
            ui->tip4_1->setText("");
    }
    else
    {
        if (ui->name_5->text().isEmpty())
            ui->tip4_2->setText("姓名不可为空！");
        else if (ui->name_5->text().contains("*"))
            ui->tip4_2->setText("姓名不得包含 * ！");
        else
            ui->tip4_2->setText("");
    }
}
/*
* 电话号码合理性校验
*/
void client::number_finished()
{
    if (windowChoice == 4)
    {
        if (!Account::checkNumber(Account::qTos(ui->number_4->text())))
            ui->tip5_1->setText("电话号码长度应为11位纯数字！");
        else
            ui->tip5_1->setText("");
    }
    else
    {
        if (!Account::checkNumber(Account::qTos(ui->number_5->text())))
            ui->tip5_2->setText("电话号码长度应为11位纯数字！");
        else
            ui->tip5_2->setText("");
    }
}
/*
* 地址合理性校验
*/
void client::address_finished()
{
     if (ui->address_4->text().isEmpty())
         ui->tip6_1->setText("地址不可为空！");
     else if (ui->address_4->text().contains("*"))
         ui->tip6_1->setText("地址不得包含 * ！");
     else
         ui->tip6_1->setText("");
}
/*
* 注册确认
*/
void client::confirm_clicked()
{
    QString buffer;
    if (windowChoice == 4)
    {
        if (ui->tip1_1->text().isEmpty() && ui->tip2_1->text().isEmpty() && ui->tip3_1->text().isEmpty() &&
            ui->tip4_1->text().isEmpty() && ui->tip5_1->text().isEmpty() && ui->tip6_1->text().isEmpty()
            &&!ui->username_4->text().isEmpty() && !ui->password_4->text().isEmpty()
            &&!ui->confirmPassword_4->text().isEmpty()&&!ui->name_4->text().isEmpty()
            &&!ui->number_4->text().isEmpty() &&!ui->address_4->text().isEmpty())//提示信息全部为空，信息合理可注册
        {
            buffer.append("2*" + ui->username_4->text() + "*" + ui->password_4->text() + "*"
                + ui->name_4->text() + "*" + ui->number_4->text() + "*" + ui->address_4->text());
            tcp->write(buffer.toUtf8());
            tcp->flush();
            showChoice = 5;
            tag = false;//返回主界面
            windowChoice = 0;
            ui->stackedWidget->setCurrentIndex(0);
            ui->username_4->clear();
            ui->password_4->clear();
            ui->confirmPassword_4->clear();
            ui->name_4->clear();
            ui->number_4->clear();
            ui->address_4->clear();
            QMessageBox message(QMessageBox::NoIcon, "Tip", "注册成功！");
            message.exec();
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "注册信息非法，请修改");
            message.exec();
        }
    }
    else {
        if (ui->tip1_2->text().isEmpty() && ui->tip2_2->text().isEmpty() && ui->tip3_2->text().isEmpty() &&
            ui->tip4_2->text().isEmpty() && ui->tip5_2->text().isEmpty() 
            && !ui->username_5->text().isEmpty() && !ui->password_5->text().isEmpty()
            && !ui->confirmPassword_5->text().isEmpty() && !ui->name_5->text().isEmpty()
            && !ui->number_5->text().isEmpty() )//提示信息全部为空，信息合理可注册
        {
            buffer.append("2*" + ui->username_5->text() + "*" + ui->password_5->text() + "*"
                + ui->name_5->text() + "*" + ui->number_5->text());
            tcp->write(buffer.toUtf8());
            tcp->flush();
            showChoice = 5;
            tag = false;//返回主界面
            windowChoice = 0;
            ui->stackedWidget->setCurrentIndex(0);
            QMessageBox message(QMessageBox::NoIcon, "Tip", "注册成功！");
            message.exec();
            ui->username_5->clear();
            ui->password_5->clear();
            ui->confirmPassword_5->clear();
            ui->name_5->clear();
            ui->number_5->clear();
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "注册信息非法，请修改");
            message.exec();
        }
    }
}
