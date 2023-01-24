#include "client.h"

client::client(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::clientClass)
{
    ui->setupUi(this);
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(0);
    //1.�����׽���
    tcp = new QTcpSocket(this);
    //2.���ӷ�����
    tcp->connectToHost(QHostAddress("127.0.0.1"), 5200);
    //3.ͨ���źŽ��շ���������
    connect(tcp, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    item_t = new QTreeWidgetItem;
    connect(ui->ul, &QPushButton::clicked, this, &client::on_Userlogin_clicked);//�û���¼��ť������
    connect(ui->ml, &QPushButton::clicked, this, &client::on_Managerlogin_clicked);//����Ա��¼��ť������
    connect(ui->cl, &QPushButton::clicked, this, &client::on_Courierlogin_clicked);//���Ա��¼��ť������
    connect(ui->ur, &QPushButton::clicked, this, &client::on_UserRegister_clicked);//�û�ע�ᰴť������
    connect(ui->cr, &QPushButton::clicked, this, &client::on_CourierRegister_clicked);//���Աע�ᰴť������
    connect(ui->back,&QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//�û���¼�����˳���ť������
    connect(ui->back_2, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//�û���¼�����˳���ť������
    connect(ui->back_3, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//�û���¼�����˳���ť������
    init_UserWindow();
    init_ManagerWindow();
    init_CourierWindow();
    init_UserRegister();
    init_CourierRegister();
    connect(ui->back_6, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//����������
    connect(ui->back_7, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//����������
    connect(ui->back_8, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//����������
    QString qss;
    QFile file(":/qss/lightblue.css");
    if (file.open(QFile::ReadOnly))
    {
        //��readAll��ȡĬ��֧�ֵ���ANSI��ʽ,�����С����creator�򿪱༭���˺ܿ��ܴ򲻿�
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
* ���ܷ��������
*/
void client::slotReadyRead()
{
    QString data = tcp->readAll();;//����У������
    QStringList List1 = data.split("/");
    stringstream stream;
    int num;
    if (windowChoice != 0)//��ʼ�������ж�
    {
        if (!tag)//δ��¼�����е�¼У��
        {
            if (data[0] == "1")//�û���¼У��ɹ�
            {
                tag = true;
                stream << Account::qTos(List1[6]);
                stream >> Balance;
                delete user;
                user = nullptr;
                user = new User(Account::qTos(List1[1]), Account::qTos(List1[3]),
                    Account::qTos(List1[4]), Account::qTos(List1[2]), Account::qTos(List1[5]));
                user->setBalance(Balance);
                ui->stackedWidget->setCurrentIndex(windowChoice);//�����Ӧ��������
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
                ui->stackedWidget->setCurrentIndex(windowChoice);//�����Ӧ��������
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
                ui->stackedWidget->setCurrentIndex(windowChoice);//�����Ӧ��������
                this->setFixedSize(1660, 1030);
                move(125, 0);
            }
            else if (data[0] == "4" || data[0] == "5")
                tag = true;
            else//ʧ����ʾ
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "�˺Ż�������� ");
                message.exec();
            }
        }
        else {
            switch (showChoice)
            {
            case 0://��ݲ�ѯ����
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
            case 1://�û���Ϣ����
            {
                LUsers.clear();
                if (windowChoice == 6&&List1.size()!=0)//���û�����ʱ����
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
            case 2://���Ա��Ϣ����
            {
                LCourier.clear();
                if (windowChoice == 8 && List1.size() != 0)//�����Ա����ʱ����
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
            case 3://����ѯ
            {
                stream << Account::qTos(List1[0]);
                stream >> Balance;
            }break;
            case 4://����Ա��Ϣ��ѯ
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
* ������ҳ��ǰ������˺�����
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
    ui->tableWidget->clear();//��ʱ������ݱ��
    ui->tableWidget_2->clear();
    ui->tableWidget_3->clear();
    ui->lineEdit->clear();//�����������Ϣ
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
* ת���û���¼ҳ��
*/
void client::on_Userlogin_clicked()
{
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(1);
}
/*
* ת������Ա��¼ҳ��
*/
void client::on_Managerlogin_clicked()
{
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(2);
}
/*
* ת�����Ա��¼����
*/
void client::on_Courierlogin_clicked()
{
    this->setFixedSize(600, 500);
    ui->stackedWidget->setCurrentIndex(3);
}
/*
* ת���û�ע�����
*/
void client::on_UserRegister_clicked()
{
    this->setFixedSize(700, 600);
    ui->stackedWidget->setCurrentIndex(4);
    QString buffer = "4";
    windowChoice = 4;
    tcp->write(buffer.toUtf8());//����ת���ź�
    tcp->flush();
}
/*
* ת�����Աע�����
*/
void client::on_CourierRegister_clicked()
{
    this->setFixedSize(700, 600);
    ui->stackedWidget->setCurrentIndex(5);
    QString buffer = "5";
    windowChoice = 5;
    tcp->write(buffer.toUtf8());//����ת���ź�
    tcp->flush();
}
/*
* �û���¼ҳ�棬��¼��ť
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
* �û��������� ������ť
*/
void client::on_findAllMessage_user()
{
    if (item_t->checkState(0) == Qt::Checked)
    {
        if (showChoice == 0)
        {
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(1); //��������
            ui->tableWidget->setColumnCount(12); //��������
            QStringList header;
            header << "��ݵ���" << "�������" << "���״̬" << "������kg/����" << "����ʱ��" << "����ʱ��"
                << "ǩ��ʱ��" << "�ļ���" << "���Ա" << "�ռ���" << "�������" << "���˹�˾";
            ui->tableWidget->setHorizontalHeaderLabels(header);
            ui->tableWidget->setRowCount(LGoods.size());
            if (LGoods.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "�޿����Ϣ�� ");
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
            ui->tableWidget->setRowCount(1); //��������
            ui->tableWidget->setColumnCount(6); //��������
            QStringList header;
            header << "�û���" << "����" << "����" << "�绰����" << "��ַ" << "���";
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
            QMessageBox message(QMessageBox::NoIcon, "Tip", "��ǰ�� " + Account::sToq(to_string(Balance)) + "Ԫ");
            message.exec();
        }
        item_t->setCheckState(0, Qt::Unchecked);
    }
}
/*
* �û�������������ѡ��
*/
void client::on_userWindowcheck_clicked(QTreeWidgetItem* item, int column)
{
    showChoice = 0;
    QString buffer;//������ָ�������ݼ�
    stringstream stream;
    int num;
    stream << Account::qTos(item->text(1));
    stream >> num;
    if (item_t != item)
        item_t->setCheckState(0, Qt::Unchecked);//ȡ���ϸ���ť��ѡ�У������ѡ��
    if (item->checkState(0) == Qt::Checked)
        buffer.append(item->text(1) + "*");
    if (num == 3 || (num >= 9 && num <= 11))//���ͱ�š���������
        buffer.append(ui->lineEdit->text());
    else if (num >= 5 && num <= 7)//����ʱ�����
        buffer.append(ui->year->text() + "*"
            + ui->month->text() + "*"
            + ui->day->text());
    if (num == 13)
        showChoice = 1;
    if (num == 14)
        showChoice = 3;
    tcp->write(buffer.toUtf8());//���Ͳ�ѯָ��
    tcp->flush();
    item_t = item;
}
/*
* �û��������� �޸��˺���Ϣ��ť
*/
void client::on_userWindowChangeMessage_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("������:"));
    // �޸�����
    QString password = QString("�����루8~16λ��: ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Password);
    lineEdit1->setText(Account::sToq(user->getPassword()));
    form.addRow(password, lineEdit1);
    //��ȷ��������
    QLineEdit* lineEdit5 = new QLineEdit(&dialog);
    lineEdit5->setEchoMode(QLineEdit::Password);
    lineEdit5->setText(Account::sToq(user->getPassword()));
    form.addRow(password, lineEdit5);
    // �޸�����
    QString name = QString("������: ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setText(Account::sToq(user->getName()));
    form.addRow(name, lineEdit2);
    //�޸ĵ绰����
    QString number = QString("�µ绰���루11λ��: ");
    QLineEdit* lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setText(Account::sToq(user->getNumber()));
    form.addRow(number, lineEdit3);
    //�޸ĵ�ַ
    QString address = QString("�µ�ַ: ");
    QLineEdit* lineEdit4 = new QLineEdit(&dialog);
    lineEdit4->setText(Account::sToq(user->getAddress()));
    form.addRow(address, lineEdit4);
    // ���OK����Cancel��
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // ��OK��������
    if (dialog.exec() == QDialog::Accepted) {
        if (lineEdit1->text() != lineEdit5->text())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "�������벻һ�£��� ");
            message.exec();
        }
        else if (lineEdit1->text().size() > 16 || lineEdit1->text().size() < 8)
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "���볤�Ȳ����Ϲ淶 ����");
            message.exec();
        }
        else if (11 != lineEdit3->text().size())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "�绰���볤�Ȳ����Ϲ淶 ����");
            message.exec();
        }
        else if (lineEdit1->text().contains("*") || lineEdit2->text().contains("*") ||
            lineEdit3->text().contains("*") || lineEdit4->text().contains("*"))
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "������Ϣ�в��ɰ��� * �ַ����� ");
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
        //    QMessageBox message(QMessageBox::NoIcon, "Tip", "�޸ĳɹ���");
           // message.exec();
        }
    }
}
/*
* ���Ϳ��
*/
void client::on_sendExpress_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("������:"));
    // ���ÿ������
    QString type = QString("������ͣ� ");
    QComboBox* combox1 = new QComboBox(&dialog);
    combox1->addItem("��ͨ���");
    combox1->addItem("�鱾");
    combox1->addItem("����Ʒ");
    form.addRow(type, combox1);
    //��������Ʒ����
    QString description = QString("��Ʒ����: ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    form.addRow(description, lineEdit1);
    //�޸ĵ绰����
    QString name = QString("�ռ����û���: ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    form.addRow(name, lineEdit2);
    // ���ÿ������
    QString company = QString("��ݹ�˾�� ");
    QComboBox* combox2 = new QComboBox(&dialog);
    combox2->addItem("˳��");
    combox2->addItem("����");
    combox2->addItem("����");
    combox2->addItem("�ϴ�");
    combox2->addItem("��ͨ");
    combox2->addItem("Բͨ");
    form.addRow(company, combox2);
    //������Ʒ������/kg)
    QString num = QString("�������/����������1kg��1kg���㣩�� ");
    QLineEdit* lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setValidator(new QIntValidator(1, 100, this));
    form.addRow(num, lineEdit3);
    // ���OK����Cancel��
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // ��OK��������
    if (dialog.exec() == QDialog::Accepted)
    {
        if (lineEdit1->text().isEmpty() || lineEdit1->text().isEmpty() || lineEdit1->text().isEmpty())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "������Ϣ�в���Ϊ�գ��� ");
            message.exec();
        }
        else if (lineEdit1->text().contains("*") || lineEdit2->text().contains("*") || lineEdit3->text().contains("*"))
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "������Ϣ�в��ɰ��� * �ַ����� ");
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
* ǩ�տ��
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
* �˻���ֵ
*/
void client::on_recharge_clicked()
{
    bool judge;
    // ��ȡ����
    double value = QInputDialog::getDouble(this, tr("��ֵ��"), tr("���ֵ��"), 100, 0, 1000, 10, &judge);
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
* ����Ա��¼ҳ�棬��¼��ť
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
* ����Ա�������� ������ť
*/
void client::on_findAllMessage_manager()
{
    if (item_t->checkState(0) == Qt::Checked)
    {
        if (showChoice == 0)
        {
            ui->tableWidget_2->clear();
            ui->tableWidget_2->setRowCount(1); //��������
            ui->tableWidget_2->setColumnCount(12); //��������
            QStringList header;
            header << "��ݵ���" << "�������" << "���״̬" << "������kg/����" << "����ʱ��" << "����ʱ��"
                << "ǩ��ʱ��" << "�ļ���" << "���Ա" << "�ռ���" << "�������" << "���˹�˾";
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setRowCount(LGoods.size());
            if (LGoods.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "�޿����Ϣ�� ");
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
            ui->tableWidget_2->setRowCount(1); //��������
            ui->tableWidget_2->setColumnCount(6); //��������
            QStringList header;
            header << "�û���" << "����" << "����" << "�绰����" << "���" << "��ַ";
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setRowCount(LUsers.size());
            if (LUsers.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "���û���Ϣ�� ");
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
            ui->tableWidget_2->setRowCount(1); //��������
            ui->tableWidget_2->setColumnCount(6); //��������
            QStringList header;
            header << "�û���" << "����" << "����" << "�绰����" << "���" << "��ݹ�˾" ;
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setRowCount(LCourier.size());
            if (LCourier.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "�޿��Ա��Ϣ�� ");
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
            ui->tableWidget_2->setRowCount(1); //��������
            ui->tableWidget_2->setColumnCount(6); //��������
            QStringList header;
            header << "�û���" << "����" << "����" << "�绰����" << "���" << "��ݹ�˾";
            ui->tableWidget_2->setHorizontalHeaderLabels(header);
            ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem(Account::sToq(manager->getUserName())));
            ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(Account::sToq(manager->getPassword())));
            ui->tableWidget_2->setItem(0, 2, new QTableWidgetItem(Account::sToq(manager->getName())));
            ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem(Account::sToq(manager->getNumber())));
            ui->tableWidget_2->setItem(0, 4, new QTableWidgetItem(Account::sToq(manager->getBalance(1))));
            ui->tableWidget_2->setItem(0, 5, new QTableWidgetItem(Account::sToq(manager->getCompany())));                                                                
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "��ǰ�� " + Account::sToq(to_string(Balance)) + "Ԫ");
            message.exec();
        }
        item_t->setCheckState(0, Qt::Unchecked);
    }
}
/*
* ����Ա������������ѡ��
*/
void client::on_managerWindowcheck_clicked(QTreeWidgetItem* item, int column) {
    showChoice = 0;
    QString buffer;//������ָ�������ݼ�
    stringstream stream;
    int num;
    stream << Account::qTos(item->text(1));
    stream >> num;
    if (item_t != item)
        item_t->setCheckState(0, Qt::Unchecked);//ȡ���ϸ���ť��ѡ�У������ѡ��
    if (item->checkState(0) == Qt::Checked)
        buffer.append(item->text(1) + "*");
    if (num == 3 || (num >= 9 && num <= 11)||num==17||num==19)//���ͱ�š���������
        buffer.append(ui->lineEdit_2->text());
    else if (num >= 5 && num <= 7)//����ʱ�����
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
    tcp->write(buffer.toUtf8());//���Ͳ�ѯָ��
    tcp->flush();
    item_t = item;
}
/*
* ���Ա���
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
* ���Աɾ��
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
* ����������
*/
void client::on_distributionExpress_clicked()
{
    QString buffer = "26*";
    Goods good;//��ǩ�տ��
    QDialog dialog(this);
    dialog.setObjectName("��ݷ���");
    QFormLayout form(&dialog);
    form.addRow(new QLabel("������:"));
    // ���ÿ������
    QString expressNumber = QString("��ݱ�ţ� ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    form.addRow(expressNumber, lineEdit1);

    QString name = QString("���Ա�û����� ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    form.addRow(name, lineEdit2);
    // ���OK����Cancel��
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // ��OK��������
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
* ���Ա�������� ������ť
*/
void client::on_findAllMessage_courier()
{
    if (item_t->checkState(0) == Qt::Checked)
    {
        if (showChoice == 0)
        {
            ui->tableWidget_3->clear();
            ui->tableWidget_3->setRowCount(1); //��������
            ui->tableWidget_3->setColumnCount(12); //��������
            QStringList header;
            header << "��ݵ���" << "�������" << "���״̬" << "������kg/����" << "����ʱ��" << "����ʱ��"
                << "ǩ��ʱ��" << "�ļ���" << "���Ա" << "�ռ���" << "�������" << "���˹�˾";
            ui->tableWidget_3->setHorizontalHeaderLabels(header);
            ui->tableWidget_3->setRowCount(LGoods.size());
            if (LGoods.empty())
            {
                QMessageBox message(QMessageBox::NoIcon, "Tip", "�޿����Ϣ�� ");
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
            ui->tableWidget_3->setRowCount(1); //��������
            ui->tableWidget_3->setColumnCount(6); //��������
            QStringList header;
            header << "�û���" << "����" << "����" << "�绰����" << "���" << "��ݹ�˾";
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
            QMessageBox message(QMessageBox::NoIcon, "Tip", "��ǰ�� " + Account::sToq(to_string(Balance)) + "Ԫ");
            message.exec();
        }
        item_t->setCheckState(0, Qt::Unchecked);
    }
}
/*
* ���Ա������������ѡ��
*/
void client::on_courierWindowcheck_clicked(QTreeWidgetItem* item, int column)
{
    showChoice = 0;
    QString buffer;//������ָ�������ݼ�
    stringstream stream;
    int num;
    stream << Account::qTos(item->text(1));
    stream >> num;
    if (item_t != item)
        item_t->setCheckState(0, Qt::Unchecked);//ȡ���ϸ���ť��ѡ�У������ѡ��
    if (item->checkState(0) == Qt::Checked)
        buffer.append(item->text(1) + "*");
    if (num == 3 || (num >= 9 && num <= 11))//���ͱ�š���������
        buffer.append(ui->lineEdit_3->text());
    else if (num >= 5 && num <= 7)//����ʱ�����
        buffer.append(ui->year_3->text() + "*"
            + ui->month_3->text() + "*"
            + ui->day_3->text());
    if (num == 16)
        showChoice = 2;
    else if (num == 17)
        showChoice = 3;
    tcp->write(buffer.toUtf8());//���Ͳ�ѯָ��
    tcp->flush();
    item_t = item;
}
/*
* ���Ա�������� �޸��˺���Ϣ��ť
*/
void client::on_courierWindowChangeMessage_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("������:"));
    // �޸�����
    QString password = QString("�����루8~16λ��: ");
    QLineEdit* lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Password);
    lineEdit1->setText(Account::sToq(courier->getPassword()));
    form.addRow(password, lineEdit1);
    //��ȷ��������
    QLineEdit* lineEdit5 = new QLineEdit(&dialog);
    lineEdit5->setEchoMode(QLineEdit::Password);
    lineEdit5->setText(Account::sToq(courier->getPassword()));
    form.addRow(password, lineEdit5);
    // �޸�����
    QString name = QString("������: ");
    QLineEdit* lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setText(Account::sToq(courier->getName()));
    form.addRow(name, lineEdit2);
    //�޸ĵ绰����
    QString number = QString("�µ绰���루11λ��: ");
    QLineEdit* lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setText(Account::sToq(courier->getNumber()));
    form.addRow(number, lineEdit3);
    //��˾�������޸�
    // ���OK����Cancel��
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // ��OK��������
    if (dialog.exec() == QDialog::Accepted) {
        if (lineEdit1->text() != lineEdit5->text())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "�������벻һ�£��� ");
            message.exec();
        }
        else if (lineEdit1->text().size() > 16 || lineEdit1->text().size() < 8)
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "���볤�Ȳ����Ϲ淶 ����");
            message.exec();
        }
        else if (11 != lineEdit3->text().size())
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "�绰���볤�Ȳ����Ϲ淶 ����");
            message.exec();
        }
        else if (lineEdit1->text().contains("*") || lineEdit2->text().contains("*") ||
            lineEdit3->text().contains("*"))
        {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "������Ϣ�в��ɰ��� * �ַ����� ");
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
            QMessageBox message(QMessageBox::NoIcon, "Tip", "�޸ĳɹ���");
            message.exec();
        }
        showChoice = 5;
}
   
/*
* ��ݲ������� ���տ��
*/
void client::on_collectExpress_clicked()
{
    QString buffer = "19*";
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("������:"));
    // ���ÿ������
    QString expressNumber = QString("��ݵ��ţ� ");
    QLineEdit* lineEdit = new QLineEdit(&dialog);
    form.addRow(expressNumber, lineEdit);
    // ���OK����Cancel��
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // ��OK��������
    if (dialog.exec() == QDialog::Accepted)
    {
        buffer.append(lineEdit->text());
        tcp->write(buffer.toUtf8());
        tcp->flush();
        showChoice = 5;
    }
}

/**
* ����������
*/
void client::on_returnChooseWindow_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//������ҳ��
    messageClear();//���ԭ����
    tcp->write(QString::number(windowChoice+20).toUtf8());
    tcp->flush();
    windowChoice = 0;
}
/*
* ��ʼ���û�����
*/
void client::init_UserWindow()
{
    connect(ui->login1, &QPushButton::clicked, this, &client::on_UserLoginWindow_login);//�û���¼�����¼��ť������
    connect(ui->search, &QPushButton::clicked, this, &client::on_findAllMessage_user);//�û���������������ť������
    connect(ui->changeMessage1, &QPushButton::clicked, this, &client::on_userWindowChangeMessage_clicked);//�û����������޸���Ϣ��ť
    connect(ui->sendExpress, SIGNAL(clicked()), this, SLOT(on_sendExpress_clicked()), Qt::UniqueConnection);//���Ϳ�ݰ�ť������
    connect(ui->recharge, SIGNAL(clicked()), this, SLOT(on_recharge_clicked()), Qt::UniqueConnection);//��ֵ��ť������
    connect(ui->sign, &QPushButton::clicked, this, &client::on_signExpress_clicked);//ǩ�հ�ť������
    //�����ʼ������飨�����û���������
    {
        QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget);
        topItem1->setText(0, "1.��ѯ���п����Ϣ");
        topItem1->setText(1, "1");
        topItem1->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem1);

        QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget);
        topItem2->setText(0, "2. ��ѯָ�������Ϣ");
        topItem2->setText(1, "2");
        ui->treeWidget->addTopLevelItem(topItem2);

        QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
        item21->setText(0, "2.1 ���ݿ�ݱ�Ų�ѯ");
        item21->setCheckState(0, Qt::Unchecked);
        item21->setText(1, "3");

        QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
        item22->setText(0, "2.2 ���ݿ��ʱ���ѯ");
        item22->setText(1, "4");

        QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
        item221->setText(0, "2.2.1 ���ݼļ�ʱ���ѯ");
        item221->setCheckState(0, Qt::Unchecked);
        item221->setText(1, "5");

        QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
        item222->setText(0, "2.2.2 ��������ʱ���ѯ");
        item222->setCheckState(0, Qt::Unchecked);
        item222->setText(1, "6");

        QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
        item223->setText(0, "2.2.3�����ռ�ʱ���ѯ");
        item223->setCheckState(0, Qt::Unchecked);
        item223->setText(1, "7");

        QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
        item23->setText(0, "2.3 �����û���ѯ");
        item23->setText(1, "8");

        QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
        item231->setText(0, "2.3.1���ݼļ��˲�ѯ");
        item231->setCheckState(0, Qt::Unchecked);
        item231->setText(1, "9");

        QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
        item232->setText(0, "2.3.2���ݿ��Ա��ѯ");
        item232->setCheckState(0, Qt::Unchecked);
        item232->setText(1, "10");

        QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
        item233->setText(0, "2.3.3�����ռ��˲�ѯ");
        item233->setCheckState(0, Qt::Unchecked);
        item233->setText(1, "11");

        QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget);
        topItem3->setText(0, "3. ��ѯ����δǩ�տ����Ϣ");
        topItem3->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem3);
        topItem3->setText(1, "12");

        QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget);
        topItem4->setText(0, "4. ��ѯ�û���Ϣ");
        topItem4->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem4);
        topItem4->setText(1, "13");

        QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget);
        topItem5->setText(0, "5. ��ѯ���");
        topItem5->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(topItem5);
        topItem5->setText(1, "14");
        connect(ui->treeWidget, &QTreeWidget::itemClicked, this,
            &client::on_userWindowcheck_clicked);
    }
}
/*
* ��ʼ�����Ա����
*/
void client::init_CourierWindow()
{
    connect(ui->login_3, &QPushButton::clicked, this, &client::on_CourierLoginWindow_login);//���Ա��¼�����¼��ť������
    connect(ui->search_3, &QPushButton::clicked, this, &client::on_findAllMessage_courier);//���Ա��������������ť������
    connect(ui->collect, SIGNAL(clicked()), this, SLOT(on_collectExpress_clicked()), Qt::UniqueConnection);//���Ա�������棬���տ��;;
    connect(ui->changeMessage3, &QPushButton::clicked, this, &client::on_courierWindowChangeMessage_clicked);//�û����������޸���Ϣ��ť
    //�����ʼ������飨�������Ա��������
    {
        QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem1->setText(0, "1.��ѯ���п����Ϣ");
        topItem1->setText(1, "1");
        topItem1->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_3->addTopLevelItem(topItem1);

        QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem2->setText(0, "2. ��ѯָ�������Ϣ");
        topItem2->setText(1, "2");
        ui->treeWidget_3->addTopLevelItem(topItem2);

        QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
        item21->setText(0, "2.1 ���ݿ�ݱ�Ų�ѯ");
        item21->setCheckState(0, Qt::Unchecked);
        item21->setText(1, "3");

        QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
        item22->setText(0, "2.2 ���ݿ��ʱ���ѯ");
        item22->setText(1, "4");

        QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
        item221->setText(0, "2.2.1 ���ݼļ�ʱ���ѯ");
        item221->setCheckState(0, Qt::Unchecked);
        item221->setText(1, "5");

        QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
        item222->setText(0, "2.2.2 ��������ʱ���ѯ");
        item222->setCheckState(0, Qt::Unchecked);
        item222->setText(1, "6");

        QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
        item223->setText(0, "2.2.3�����ռ�ʱ���ѯ");
        item223->setCheckState(0, Qt::Unchecked);
        item223->setText(1, "7");

        QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
        item23->setText(0, "2.3 �����û���ѯ");
        item23->setText(1, "8");

        QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
        item231->setText(0, "2.3.1���ݼļ��˲�ѯ");
        item231->setCheckState(0, Qt::Unchecked);
        item231->setText(1, "9");

        QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
        item232->setText(0, "2.3.2���ݿ��Ա��ѯ");
        item232->setCheckState(0, Qt::Unchecked);
        item232->setText(1, "10");

        QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
        item233->setText(0, "2.3.3�����ռ��˲�ѯ");
        item233->setCheckState(0, Qt::Unchecked);
        item233->setText(1, "11");

        QTreeWidgetItem* item24 = new QTreeWidgetItem(topItem2);
        item24->setText(0, "2.4 ���ݿ��״̬��ѯ");
        item24->setText(1, "12");

        QTreeWidgetItem* item241 = new QTreeWidgetItem(item24);
        item241->setText(0, "2.4.1 ��ѯ����δ���տ��");
        item241->setCheckState(0, Qt::Unchecked);
        item241->setText(1, "13");

        QTreeWidgetItem* item242 = new QTreeWidgetItem(item24);
        item242->setText(0, "2.4.2 ��ѯ����δǩ�տ��");
        item242->setCheckState(0, Qt::Unchecked);
        item242->setText(1, "14");

        QTreeWidgetItem* item243 = new QTreeWidgetItem(item24);
        item243->setText(0, "2.4.3 ��ѯ������ǩ�տ��");
        item243->setCheckState(0, Qt::Unchecked);
        item243->setText(1, "15");

        QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem3->setText(0, "3. ��ѯ�˺���Ϣ");
        topItem3->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_3->addTopLevelItem(topItem3);
        topItem3->setText(1, "16");

        QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget_3);
        topItem4->setText(0, "4. ��ѯ���");
        topItem4->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_3->addTopLevelItem(topItem4);
        topItem4->setText(1, "17");
        connect(ui->treeWidget_3, &QTreeWidget::itemClicked, this,
            &client::on_courierWindowcheck_clicked);
    }                                                                   //����Ա��������������ť������

}
/*
* ��ʼ������Ա����
*/
void client::init_ManagerWindow()
{
    connect(ui->login2, &QPushButton::clicked, this, &client::on_ManagerLoginWindow_login);//����Ա��¼�����¼��ť������
    connect(ui->search_2, &QPushButton::clicked, this, &client::on_findAllMessage_manager);//����Ա��������������ť������
    connect(ui->addCourier, SIGNAL(clicked()), this, SLOT(on_addCourier_clicked()), Qt::UniqueConnection);//����Ա��ӿ��Ա��ť
    connect(ui->deleteCourier, SIGNAL(clicked()), this, SLOT(on_deleteCourier_clicked()), Qt::UniqueConnection);//����Աɾ�����Ա��ť
    connect(ui->distribution, &QPushButton::clicked, this, &client::on_distributionExpress_clicked);//����Ա������
    //�����ʼ������飨��������Ա��������
    {
        QTreeWidgetItem* topItem1 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem1->setText(0, "1.��ѯ���п����Ϣ");
        topItem1->setText(1, "1");
        topItem1->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem1);

        QTreeWidgetItem* topItem2 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem2->setText(0, "2. ��ѯָ�������Ϣ");
        topItem2->setText(1, "2");
        ui->treeWidget_2->addTopLevelItem(topItem2);

        QTreeWidgetItem* item21 = new QTreeWidgetItem(topItem2);
        item21->setText(0, "2.1 ���ݿ�ݱ�Ų�ѯ");
        item21->setCheckState(0, Qt::Unchecked);
        item21->setText(1, "3");

        QTreeWidgetItem* item22 = new QTreeWidgetItem(topItem2);
        item22->setText(0, "2.2 ���ݿ��ʱ���ѯ");
        item22->setText(1, "4");

        QTreeWidgetItem* item221 = new QTreeWidgetItem(item22);
        item221->setText(0, "2.2.1 ���ݼļ�ʱ���ѯ");
        item221->setCheckState(0, Qt::Unchecked);
        item221->setText(1, "5");

        QTreeWidgetItem* item222 = new QTreeWidgetItem(item22);
        item222->setText(0, "2.2.2 ��������ʱ���ѯ");
        item222->setCheckState(0, Qt::Unchecked);
        item222->setText(1, "6");

        QTreeWidgetItem* item223 = new QTreeWidgetItem(item22);
        item223->setText(0, "2.2.3�����ռ�ʱ���ѯ");
        item223->setCheckState(0, Qt::Unchecked);
        item223->setText(1, "7");

        QTreeWidgetItem* item23 = new QTreeWidgetItem(topItem2);
        item23->setText(0, "2.3 �����û���ѯ");
        item23->setText(1, "8");

        QTreeWidgetItem* item231 = new QTreeWidgetItem(item23);
        item231->setText(0, "2.3.1���ݼļ��˲�ѯ");
        item231->setCheckState(0, Qt::Unchecked);
        item231->setText(1, "9");

        QTreeWidgetItem* item232 = new QTreeWidgetItem(item23);
        item232->setText(0, "2.3.2���ݿ��Ա��ѯ");
        item232->setCheckState(0, Qt::Unchecked);
        item232->setText(1, "10");

        QTreeWidgetItem* item233 = new QTreeWidgetItem(item23);
        item233->setText(0, "2.3.3�����ռ��˲�ѯ");
        item233->setCheckState(0, Qt::Unchecked);
        item233->setText(1, "11");

        QTreeWidgetItem* item24 = new QTreeWidgetItem(topItem2);
        item24->setText(0, "2.4 ���ݿ��״̬��ѯ");
        item24->setText(1, "12");

        QTreeWidgetItem* item241 = new QTreeWidgetItem(item24);
        item241->setText(0, "2.4.1 ��ѯ����δ���տ��");
        item241->setCheckState(0, Qt::Unchecked);
        item241->setText(1, "13");

        QTreeWidgetItem* item242 = new QTreeWidgetItem(item24);
        item242->setText(0, "2.4.2 ��ѯ����δǩ�տ��");
        item242->setCheckState(0, Qt::Unchecked);
        item242->setText(1, "14");

        QTreeWidgetItem* item243 = new QTreeWidgetItem(item24);
        item243->setText(0, "2.4.3 ��ѯ������ǩ�տ��");
        item243->setCheckState(0, Qt::Unchecked);
        item243->setText(1, "15");
        QTreeWidgetItem* topItem3 = new QTreeWidgetItem(ui->treeWidget_2);

        topItem3->setText(0, "3. ��ѯ�����û���Ϣ");
        topItem3->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem3);
        topItem3->setText(1, "16");

        QTreeWidgetItem* topItem4 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem4->setText(0, "4. ��ѯָ���û���Ϣ");
        topItem4->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem4);
        topItem4->setText(1, "17");

        QTreeWidgetItem* topItem5 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem5->setText(0, "5. ��ѯ���п��Ա��Ϣ");
        topItem5->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem5);
        topItem5->setText(1, "18");

        QTreeWidgetItem* topItem6 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem6->setText(0, "6. ��ѯָ�����Ա��Ϣ");
        topItem6->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem6);
        topItem6->setText(1, "19");

        QTreeWidgetItem* topItem7 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem7->setText(0, "7. ��ѯ���п���ӿ��Ա��Ϣ");
        topItem7->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem7);
        topItem7->setText(1, "20");

        QTreeWidgetItem* topItem8 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem8->setText(0, "8. ��ѯ����Ա��Ϣ");
        topItem8->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem8);
        topItem8->setText(1, "21");

        QTreeWidgetItem* topItem9 = new QTreeWidgetItem(ui->treeWidget_2);
        topItem9->setText(0, "9. ��ѯ���");
        topItem9->setCheckState(0, Qt::Unchecked);
        ui->treeWidget_2->addTopLevelItem(topItem9);
        topItem9->setText(1, "22");
        connect(ui->treeWidget_2, &QTreeWidget::itemClicked, this,
            &client::on_managerWindowcheck_clicked);
    }
}
/*
* ��ʼ�����Աע�����
*/
void client::init_CourierRegister() {
    courier = new Courier();
    {
        connect(ui->username_5, &QLineEdit::editingFinished, this, &client::username_finished);//У���û���
        connect(ui->password_5, &QLineEdit::editingFinished, this, &client::password_finished);//У������
        connect(ui->confirmPassword_5, &QLineEdit::editingFinished, this, &client::confirmPassword);//������κ˶�
        connect(ui->name_5, &QLineEdit::editingFinished, this, &client::name_finished);//У������
        connect(ui->number_5, &QLineEdit::editingFinished, this, &client::number_finished);//У��绰����
        connect(ui->confirm2, &QPushButton::clicked, this, &client::confirm_clicked);//�˳���ť������
        connect(ui->back_5, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//�˳���ť������
    }
}
/*
* ��ʼ���û�ע�����
*/
void client::init_UserRegister() {
    user = new User();
    {
        connect(ui->username_4, &QLineEdit::editingFinished, this, &client::username_finished);//У���û��û���
        connect(ui->password_4, &QLineEdit::editingFinished, this, &client::password_finished);//У������
        connect(ui->confirmPassword_4, &QLineEdit::editingFinished, this, &client::confirmPassword);//������κ˶�
        connect(ui->name_4, &QLineEdit::editingFinished, this, &client::name_finished);//У������
        connect(ui->number_4, &QLineEdit::editingFinished, this, &client::number_finished);//У��绰����
        connect(ui->address_4, &QLineEdit::editingFinished, this, &client::address_finished);//У���ַ
        connect(ui->confirm1, &QPushButton::clicked, this, &client::confirm_clicked);//ע�ᰴť������
        connect(ui->back_4, &QPushButton::clicked, this, &client::on_returnChooseWindow_clicked);//�˳���ť������
    }
}
/*
* �û���������У��
*/
void client::username_finished()
{
    if (windowChoice == 4)
    {
        if (ui->username_4->text().contains("*"))
            ui->tip1_1->setText("�û����в��ɰ��� * ��");
        else
        {
            tcp->write("1*");
            tcp->write(ui->username_4->text().toUtf8());
            tcp->flush();
        }
    }
    else {
        if (ui->username_5->text().contains("*"))
            ui->tip1_2->setText("�û����в��ɰ��� * ��");
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
* ���������У��
*/
void client::password_finished() {
    if (windowChoice == 4)
    {
        if (!Account::checkPassword(Account::qTos(ui->password_4->text())))
            ui->tip2_1->setText("���볤��ӦΪ8~16λ��");
        else if(ui->password_4->text().contains("*"))
            ui->tip2_1->setText("���벻�ð��� * ��");
        else
            ui->tip2_1->setText("");
    }
    else 
    {
        if (!Account::checkPassword(Account::qTos(ui->password_5->text())))
            ui->tip2_2->setText("���볤��ӦΪ8~16λ��");
        else if (ui->password_5->text().contains("*"))
            ui->tip2_2->setText("���벻�ð��� * ��");
        else
            ui->tip2_2->setText("");
    }
}
/*
* �������У��
*/
void client::confirmPassword()
{
    if (windowChoice == 4)
    {
        if (ui->password_4->text() != ui->confirmPassword_4->text())
            ui->tip3_1->setText("�������벻һ�£�");
        else
            ui->tip3_1->setText("");
    }
    else {
        if (ui->password_5->text() != ui->confirmPassword_5->text())
            ui->tip3_2->setText("�������벻һ�£�");
        else
            ui->tip3_2->setText("");
    }
}
/*
* ����������У��
*/
void client::name_finished()
{
    if (windowChoice == 4)
    {
        if (ui->name_4->text().isEmpty())
            ui->tip4_1->setText("��������Ϊ�գ�");
        else if (ui->name_4->text().contains("*"))
            ui->tip4_1->setText("�������ð��� * ��");
        else
            ui->tip4_1->setText("");
    }
    else
    {
        if (ui->name_5->text().isEmpty())
            ui->tip4_2->setText("��������Ϊ�գ�");
        else if (ui->name_5->text().contains("*"))
            ui->tip4_2->setText("�������ð��� * ��");
        else
            ui->tip4_2->setText("");
    }
}
/*
* �绰���������У��
*/
void client::number_finished()
{
    if (windowChoice == 4)
    {
        if (!Account::checkNumber(Account::qTos(ui->number_4->text())))
            ui->tip5_1->setText("�绰���볤��ӦΪ11λ�����֣�");
        else
            ui->tip5_1->setText("");
    }
    else
    {
        if (!Account::checkNumber(Account::qTos(ui->number_5->text())))
            ui->tip5_2->setText("�绰���볤��ӦΪ11λ�����֣�");
        else
            ui->tip5_2->setText("");
    }
}
/*
* ��ַ������У��
*/
void client::address_finished()
{
     if (ui->address_4->text().isEmpty())
         ui->tip6_1->setText("��ַ����Ϊ�գ�");
     else if (ui->address_4->text().contains("*"))
         ui->tip6_1->setText("��ַ���ð��� * ��");
     else
         ui->tip6_1->setText("");
}
/*
* ע��ȷ��
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
            &&!ui->number_4->text().isEmpty() &&!ui->address_4->text().isEmpty())//��ʾ��Ϣȫ��Ϊ�գ���Ϣ�����ע��
        {
            buffer.append("2*" + ui->username_4->text() + "*" + ui->password_4->text() + "*"
                + ui->name_4->text() + "*" + ui->number_4->text() + "*" + ui->address_4->text());
            tcp->write(buffer.toUtf8());
            tcp->flush();
            showChoice = 5;
            tag = false;//����������
            windowChoice = 0;
            ui->stackedWidget->setCurrentIndex(0);
            ui->username_4->clear();
            ui->password_4->clear();
            ui->confirmPassword_4->clear();
            ui->name_4->clear();
            ui->number_4->clear();
            ui->address_4->clear();
            QMessageBox message(QMessageBox::NoIcon, "Tip", "ע��ɹ���");
            message.exec();
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "ע����Ϣ�Ƿ������޸�");
            message.exec();
        }
    }
    else {
        if (ui->tip1_2->text().isEmpty() && ui->tip2_2->text().isEmpty() && ui->tip3_2->text().isEmpty() &&
            ui->tip4_2->text().isEmpty() && ui->tip5_2->text().isEmpty() 
            && !ui->username_5->text().isEmpty() && !ui->password_5->text().isEmpty()
            && !ui->confirmPassword_5->text().isEmpty() && !ui->name_5->text().isEmpty()
            && !ui->number_5->text().isEmpty() )//��ʾ��Ϣȫ��Ϊ�գ���Ϣ�����ע��
        {
            buffer.append("2*" + ui->username_5->text() + "*" + ui->password_5->text() + "*"
                + ui->name_5->text() + "*" + ui->number_5->text());
            tcp->write(buffer.toUtf8());
            tcp->flush();
            showChoice = 5;
            tag = false;//����������
            windowChoice = 0;
            ui->stackedWidget->setCurrentIndex(0);
            QMessageBox message(QMessageBox::NoIcon, "Tip", "ע��ɹ���");
            message.exec();
            ui->username_5->clear();
            ui->password_5->clear();
            ui->confirmPassword_5->clear();
            ui->name_5->clear();
            ui->number_5->clear();
        }
        else {
            QMessageBox message(QMessageBox::NoIcon, "Tip", "ע����Ϣ�Ƿ������޸�");
            message.exec();
        }
    }
}
