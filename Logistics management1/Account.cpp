#include "Account.h"
#include "Database.h"
/*
* �˺����޲ι��캯��
*/
Account::Account()
{
    //this->userName = "";
   // this->name = "";
   // this->password = "";
   // this->number = "";
    this->balance = 0;//����ʼ��
}
/*
* �˺����вι��캯��
* �����û��������봴���˺Ŷ���
*/
Account::Account(string username, string password)
{
    this->userName = username;
    this->password = password;
}
/**
 * ��ȡ�û���
 * @return string
 */
string Account::getUserName() {
    return userName;
}
/**
 * ��ȡ����
 * @return string
 */
string Account::getName() {
    return name;
}
/**
 * ��ȡ�绰����
 * @return string
 */
string Account::getNumber() {
    return number;
}
/**
 * ��ȡ����
 * @return string
 */
string Account::getPassword() {
    return password;
}
/**
 * ��ȡ���
 * @return int
 */
double Account::getBalance() {
    return balance;
}
/*
* ��ȡ���
* @return string
*/
string Account::getBalance(double index)
{
    string balance;
    stringstream stream;
    stream << getBalance();
    stream >> balance;
    return balance;
}
/**
 * �޸��û���
 * @param string�� username
 */
void Account::setUserName(string username) {
    this->userName = username;
}
/**
 * �޸�����
 * @param string�� name
 */
void Account::setName(string name) {
    this->name = name;
}
/**
 * �޸ĵ绰����
 * @param string�� number
 */
void Account::setNumber(string number) {
    this->number = number;
}
/**
 * �޸�����
 * @param string�� password
 */
void Account::setPassword(string password) {
    this->password = password;
}
/**
 * �޸����
 * @param int�� balance 
 */
void Account::setBalance(double balance) {
    this->balance = balance;
}
/*
* ��ȡ���д����û���
* @param vector<string>& userList
* ���ô��ݣ��������ڴ洢�û����б�
*/
void Account::readAllUserName(vector<string>& userList)
{
    string s;
    ifstream fin;
    fin.open("User.txt");//���û����ļ�
    while (getline(fin, s))//���ж�ȡ��Ϣ
        userList.emplace_back(s);
}
void Account::readAllCourier(vector<string>& courierList,string company)
{
    string s;
    ifstream fin;
    fin.open("Courier/"+company + "CourierList.txt");
    while (getline(fin, s))
        courierList.emplace_back(s);
}
/*
* User���޲ι��캯��
*/
User::User()
{

}
/**
* �вι��캯��
* �����û��������봴���û�����
*/
User::User(string username, string password):Account(username,password){
   
}
/**
 * User������вι��캯��
 * @param string�� username
 * @param string�� name
 * @param string�� number
 * @param string�� password
 * @param string�� address
 */
User::User(string username, string name, string number, string password, string address) {
    setUserName(username);
    setName(name);
    setNumber(number);
    setPassword(password);
    setAddress(address);
    setBalance(0);
}
/**
 * ��ȡ��ַ
 * @return string
 */
string User::getAddress() {
    return address;
}
/*
* ��ȡ���͵Ŀ���б�
* @return vector<Goods>
*/
vector<Goods> User::getSend()
{
    return this->send;
}
/*
* ��ȡ���յĿ���б�
* @return vector<Goods>
*/
vector<Goods> User::getReceive()
{
    return this->receive;
}
/**
 *  �޸ĵ�ַ
 * @param address
 */
void User::setAddress(string address) {
    this->address = address;
}
/**
 * User�����ע�ắ��
 * @param string�� username �û���
 * @param string�� name ����
 * @param string�� number �绰����
 * @param string�� password �˺�����
 * @param string�� address ��ַ
 * @param int�� balance ���
 */
void User::registerAccount(string username, string name, string number, string password, string address, double balance)
{
    setUserName(username);
    setName(name);
    setNumber(number);
    setPassword(password);
    setAddress(address);
    setBalance(balance);
}
/**
 * User�����ע�ắ��
 * @return User �û�
 */
void User::registerAccount()
{    
    string username;
    string name;
    string number;
    string password;
    string address;
    double balance = 0;
    cout << "�������û���" << endl;
    cin >> username;
    cout << "����������" << endl;
    cin >> name;
    cout << "������ϵ�绰" << endl;
    cin >> number;
    cout << "����������" << endl;
    cin >> password;
    cout << "��������ϵ��ַ" << endl;
    cin >> address;
    registerAccount(username, name, number, password, address, balance);
}
/*
* ���Ϳ��
* @param vector<string>�� userList �û����б� ���ڼ��Ŀ���û��Ƿ����
* @param vector<string>�� companyList ������˾�б� ���ڼ��������˾�Ƿ����
*/
void User::sendExpress(vector<string> userList, vector<string> companyList)
{
    Goods* good;
    string name;
    time_t currentTime = time(0);//��ȡ��ǰϵͳʱ��
    bool judge = false;
    int num = 0;
    cout << "��������Ʒ���ͣ�" << endl << "0.��ͨ���" << endl << "1.�鱾" << endl << "2.����Ʒ" << endl;
    cin >> name;
    if (name == "1")
        good = new Book(0);
    else if (name == "2")
        good = new Fragile(0);
    else
        good = new Common(0);
    good->setSendTime(&currentTime);//����ϵͳʱ��ȷ����ݱ���
    cout << "��������Ʒ����" << endl;
    cin >> name;
    good->setDecription(name);
    while (!judge)
    {
        cout << "�������ռ�������" << endl;
        cin >> name;
        for (int i = 0; i < userList.size(); i++)
            if (name == userList[i])
            {
                judge = true;
                break;
            }
        if (!judge)
            cout << "�û������ڣ�����������" << endl;
    }
    good->setRecipient(name);
    while (judge)
    {
        cout << "�������ݹ�˾" << endl;
        cin >> name;
        for (int i = 0; i < companyList.size(); i++)
            if (name == companyList[i])
            {
                judge = false;
                break;
            }
        if (judge)
            cout << "��ݹ�˾�����ڣ�����������" << endl;
    }
    good->setCompany(name);
    cout << "��������Ʒ������";
    cin >> num;
    good->setNumber(num);
    good->setState(State::Uncollect);
    good->setSender(this->getUserName());
    good->setReceiveTime("0-0-0 0:0:0");
    good->setCollectTime("0-0-0 0:0:0");
    good->setCourier(" ");
    good->setExpressNumber(&currentTime);
    if (this->getBalance() < good->getPiece())
        cout << "����" << endl;
    else
    {
        this->addSend(good);
        Database* database = new Database();
        database->connectDatabase();
        database->insertPackage(*good);
        database->addBalance(good->getCompany(), good->getPiece());//����ָ��ָ�������������ú���
        database->FreeConnect();
        delete database;
        database = nullptr;
    }
}
/**
* ��ӷ��͵Ŀ��
* @param Goods�� good
*/
void User::addSend(Goods *good)
{
    setBalance(getBalance() -good->getPiece());//���Ϳ����Ҫ����15Ԫ
    this->send.push_back(*good);
}
/**
* ��ӽ��յĿ��
* @param Goods�� good
*/
void User::addReceive(Goods good)
{
    this->send.push_back(good);
}
/*
* ���÷��͵Ŀ���б�
* @param vector<Goods>�� send
*/
void User::setSend(vector<Goods> send)
{
    this->send = send;
}
/*
* ���ý��յĿ���б�
* @param vector<Goods>�� receive
*/
void User::setReceive(vector<Goods> receive)
{
    this->receive = receive;
}
/*
* ����ָ���Ľ��տ��
* @param Goods�� good
* @param int�� index �ÿ���ڽ����б��е�λ��
*/
void User::setReceive(Goods good, int index)
{
    this->receive[index] = good;
}
/*
* ���û���Ϣ���浽�ļ���
*/
void User::saveUser()
{
    ofstream fout;
    fout.open("User/" + getUserName() + ".txt");//������д���ļ�
    fout << getUserName() << endl << getPassword() << endl << 
        getName() << endl << getNumber() << endl << 
        getBalance() << endl << getAddress() << endl;//�洢ǰ��������
    fout.close();//�ر��ļ�
}
/*
* ���ļ��ж�ȡ�û���Ϣ
*/
bool User::readUser() {
    ifstream fin;//�ļ�������
    fin.open("User/"+getUserName() + ".txt");//���û���Ϣ�ļ�
    if (!fin)//�����ڸ��û�����Ӧ���ļ�
    {
        cout << "�˺Ų�����" << endl;
        return false;
    }
    else {
        string s;
        stringstream stream;//�����������ڽ���string�����ֵ�ת��
        double n;
        getline(fin, s);//���ж�������
        getline(fin, s);
        if (s != getPassword())
        {
            cout << "�������" << endl;
            fin.close();
            return false;
        }
        else {
            getline(fin, s);
            setName(s);
            getline(fin, s);
            setNumber(s);
            getline(fin, s);
            stream << s;
            stream >> n;
            setBalance(n);
            getline(fin, s);
            setAddress(s);
        }
    }
    fin.close();
    return true;
}
/*
* ��ʽ������û���Ϣ
*/
void User::printUser()
{
    cout << "�û����� " << getUserName()
        << "  ���룺 " << getPassword()
        << "  ������ " << getName()
        << "  �绰���룺 " << getNumber()
        << "  �û��� " << getBalance()
        << "  ��ַ�� " << getAddress()
        <<endl;
}
/**
*USer����������
*/
User::~User()
{
    //vector<Goods>().swap(*send);
    //vector<Goods>().swap(*receive);
}
/**
* ����Ա���޲ι��캯��
*/
Manager::Manager() {

}
/**
* ����Ա���вι��캯��
* �����û��������빹�����Ա�����
*/
Manager::Manager(string username, string password):Account( username,  password){

}
/**
* ��ȡ����Ա������˾
* @return string
*/
string Manager::getCompany()
{
    return this->company;
}
/**
* ��ѯ���п����Ϣ
* @return vector<Goods>
*/
vector<Goods> Manager::getPacket()
{
    return packet;
}
vector<Courier> Manager::getCourier()
{
    return this->courier;
}
/**
* ���ù���Ա���ڹ�˾
* @param string�� company
*/
void Manager::setCompany(string company)
{
    this->company = company;
}
/**
* ���ÿ����Ϣ
* @param vector<Goods>�� packet
*/
void Manager::setPacket(vector<Goods> packet)
{
    this->packet = packet;
}
void Manager::setPacket(Goods good, int index)
{
    this->packet[index] = good;
}
/**
* ����������п����Ϣ
* @param vector<Goods>�� packet
*/
void Account::printPacket(vector<Goods> packet)
{
    int num = 0;
    for (auto s : packet)//����б��е����п����Ϣ
    {
        cout << ++num<<"."<<endl;
        printPacket(s);
    }
}
/**
* ������������Ϣ
* @param Goods�� packet
*/
void Account::printPacket(Goods packet)
{
    cout << "�������:" ;
    if (packet.getType() == Type::book)
        cout << " �鱾" ;
    else if (packet.getType() == Type::fragile)
        cout << " ����Ʒ" ;
    else
        cout << " ��ͨ" ;
    cout << "  ���״̬ �� ";
    if (packet.getState() == State::Unsign)
        cout << " δǩ��" ;
    else if (packet.getState() == State::Uncollect)
        cout << " δ����" ;
    else 
        cout << " ��ǩ��" ;
    cout << "   ��ݵ��� �� " << packet.getExpressNumber() ;
    cout << "   ��Ʒ������" << packet.getNumber() ;
    cout << "   ��ݷ���ʱ�� : " << packet.getSendTime(1) ;
    cout << "   �������ʱ��" << packet.getCollectTime(1);
    cout << "   ���ǩ��ʱ�� : " << packet.getReceiveTime(1);
    cout << "   �ļ��� �� " << packet.getSender() ;
    cout << "   ���Ա��" << packet.getCourier() ;
    cout << "   ǩ���� �� " << packet.getRecipient() ;
    cout << "   ���˹�˾�� " << packet.getCompany();
    cout << "   ������� �� " << packet.getDescribtion() << endl;
}
/**
* ���ݿ�ݱ�Ų�ѯ���
* @param Goods&�� good  ���ô��ݣ����ڴ洢��ѯ�õĿ����Ϣ
* @param string�� s     ��ݱ��
* @param vector<Goods>�� source  ����ѯ����б�
* @return bool �ɹ�Ϊtrue,ʧ��Ϊfalse
*/
bool Account::checkPacket(Goods& good, string s,vector<Goods> goods)
{
    for(auto i:goods)
        if (s == i.getExpressNumber())//�ȶԿ�ݱ��
        {
            good = i;
            return true;
        }
    return false;
}
/**
* ��ѯ�û�δǩ�յĿ��
* @param vector<Goods>&�� good  ���ô��ݣ����ڴ洢��ѯ�õĿ����Ϣ
* @param State�� s     ���״̬
* @param vector<Goods>�� source  ����ѯ����б�
* @return bool �ɹ�Ϊtrue,ʧ��Ϊfalse
*/
bool Account::checkPacket(vector<Goods>& goods, State state, vector<Goods> source)
{
    bool judge = false;
    for (auto i : source)
        if (state == i.getState())//�ȶԿ��״̬
        {
            goods.emplace_back(i);
            judge = true;
        }
    return judge;
}
/**
* �����û�����ѯ�����Ϣ
* @param vector<Goods>&�� good  ���ô��ݣ����ڴ洢��ѯ�õĿ����Ϣ
* @param string�� s     �û���
* @param bool�� index  true��ļ��ˣ�false���ռ���
* @param vector<Goods>�� source  ����ѯ����б�
* @return bool �ɹ�Ϊtrue,ʧ��Ϊfalse
*/
bool Account::checkPacket(vector<Goods>& goods, string s, int index,vector<Goods> source)
{
    bool judge = false;
    if (index==1)//��ѰĿ���Ǽļ���
    {
        for (auto i : source)
            if (i.getSender() == s)//�ȶԼļ�����Ϣ
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    else if(index==2)//��ѰĿ�����ռ���
    {
        for (auto i : source)
            if (i.getRecipient() == s)//�ȶ��ռ�����Ϣ
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    else 
    {
        for (auto i : source)
            if (i.getCourier() == s)//�ȶ��ռ�����Ϣ
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    return judge;
}
/**
* ����ʱ���ѯ�����Ϣ
* @param vector<Goods>&�� good  ���ô��ݣ����ڴ洢��ѯ�õĿ����Ϣ
* @param array<int, 6>�� s     ����ѯ����
* @param bool�� index  true��ļ�ʱ�䣬false���ռ�ʱ��
* @param vector<Goods>�� source  ����ѯ����б�
* @return bool �ɹ�Ϊtrue,ʧ��Ϊfalse
*/
bool Account::checkPacket(vector<Goods>& goods, array<int, 6> s, int index, vector<Goods> source)
{
    bool judge = false;
    if (index == 1)//�ȶ�Ŀ���Ǽļ�ʱ��
    {
        for (auto i : source)
            if (i.getSendTime()[0] == s[0] && i.getSendTime()[1] == s[1] && i.getSendTime()[2] == s[2])//�Ƚϼļ�ʱ�䣨�����գ�
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    else  if (index == 2)   //�ȶ�Ŀ�����ռ�ʱ��          
    {
        for (auto i : source)
            if (i.getReceiveTime()[0] == s[0] && i.getReceiveTime()[1] == s[1] && i.getReceiveTime()[2] == s[2])//�Ƚ��ռ�ʱ�䣨�����գ�
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    else {
        for (auto i : source)
            if (i.getCollectTime()[0] == s[0] && i.getCollectTime()[1] == s[1] && i.getCollectTime()[2] == s[2])//�Ƚ��ռ�ʱ�䣨�����գ�
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    return judge;
}
/**
 * Account�����ע�ắ��
 * @param string�� username �û���
 * @param string�� name ����
 * @param string�� number �绰����
 * @param string�� password �˺�����
 * @param int�� balance ���
 */
void Account::registerAccount(string username, string name, string number, string password, double balance)
{
    setUserName(username);
    setName(name);
    setNumber(number);
    setPassword(password);
    setBalance(balance);
}
bool Account::findPacket(vector<Goods> goods, string s,Goods& good)
{
    bool judge = false;
    for(int i =0;i<goods.size();i++)
        if (goods[i].getExpressNumber() == s)
        {
            good = goods[i];
            judge = true;
            break;
        }
    return judge;
}
/*
* �޸��˺���Ϣ
*/
void User::changeMessage()
{
    int judge = 0;
    string s;
    cout << "�Ƿ��޸��˺�����(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "������������:" << endl;
        cin >> s;
        setPassword(s);
    }
    cout << "�Ƿ��޸�����(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "������������:" << endl;
        cin >> s;
        setName(s);
    }
    cout << "�Ƿ��޸ĵ绰����(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "�������µ绰����:" << endl;
        cin >> s;
        setNumber(s);
    }
    cout << "�Ƿ��޸ĵ�ַ(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "�������µ�ַ:" << endl;
        cin >> s;
        setAddress(s);
    }
    
}
/*
* �����û�����ȡ�˺���Ϣ
* @param string�� �û���
* @return User��
*/
User Manager::readUser(string username)
{
    ifstream fin;//�ļ�������
    fin.open("User/"+username + ".txt");
    User user ;
    string s;
    stringstream stream;//�����������ڽ���string�����ֵ�ת��
    double n;
    getline(fin, s);//���ж�������
    user.setUserName(s);
    getline(fin, s);
    user.setPassword(s);
    getline(fin, s);
    user.setName(s);
    getline(fin, s);
    user.setNumber(s);
    getline(fin, s);
    stream << s;
    stream >> n;
    user.setBalance(n);
    getline(fin, s);
    user.setAddress(s);
    fin.close();
    return user;
}
/*
* �����û�����ȡ���Ա�˺���Ϣ
* @param string�� �û���
* @return Courier��
*/
Courier Manager::readCourier(string username)
{
    ifstream fin;//�ļ�������
    fin.open("Courier/"+username + ".txt");
    Courier courier;
    string s;
    stringstream stream;//�����������ڽ���string�����ֵ�ת��
    double n;
    getline(fin, s);//���ж�������
    courier.setUserName(s);
    getline(fin, s);
    courier.setPassword(s);
    getline(fin, s);
    courier.setName(s);
    getline(fin, s);
    courier.setNumber(s);
    getline(fin, s);
    stream << s;
    stream >> n;
    courier.setBalance(n);
    getline(fin, s);
    courier.setCompany(s);
    fin.close();
    return courier;
}

void Manager::setCourier(vector<Courier> courier)
{
    this->courier = courier;
}

/*
* ���������˾���¹���Ա
*/
void Manager::addCourier(Courier &temp)
{
    temp.setCompany(this->getCompany());
    courier.emplace_back(temp);
}
/*
* ɾ��������˾���¹���Ա
*/
Courier Manager::decCourier(int index)
{
    Courier temp = courier[index];
    temp.setCompany("0");
    courier.erase(courier.begin()+index);
    return temp;
}
bool Manager::findCourier(string username)
{
    bool judge = false;
    for (auto s : this->getCourier())
    {
        if (s.getUserName() == username)
        {
            judge = true;
            break;
        }
    }
    return judge;
}
void Manager::saveAllCourier(string company, vector<Courier> courier)
{
    ofstream fout;
    fout.open("Courier/"+company + "CourierList.txt");//������д���ļ�
    for (int i = 0; i < courier.size(); i++)
    {
        fout << courier[i].getUserName()<<endl;//д���û�������
        courier[i].saveCourier();//����������
    }
    fout.close();//�ر��ļ�
}
Courier::Courier()
{
}
Courier::Courier(string username, string password):Account(username,password)
{
}
/*
* ��ȡ���Ա���ڹ�˾
* @return string��
*/
string Courier::getCompany()
{
    return this->company;
}
/*
* ��ȡ���Ա������Ŀ���б�
* @return vector<Goods>��
*/
vector<Goods> Courier::getAssigned()
{
    return this->assigned;
}
/*
* ���ÿ��Ա���ڹ�˾
* @param string��
*/
void Courier::setCompany(string company)
{
    this->company = company;
}
/*
* ���ÿ��Ա������Ŀ���б�
* @param vector<Goods>�� goods
*/
void Courier::setAssigned(vector<Goods> goods)
{
    this->assigned = goods;
}
/*
* ���տ��
* @param Goods�� ���տ��
*/
void Courier::collectExpress(Goods &good, double &money)
{
    Goods* p;
    time_t time1 = time(0);
    good.setState(State::Unsign);
    good.setCollectTime(&time1);
    if (good.getType() == Type::book)
        p = new Book(good.getNumber());
    else if (good.getType() == Type::fragile)
        p = new Fragile(good.getNumber());
    else
        p = new Common(good.getNumber());
    money = p->getPiece() * 0.5;
    this->setBalance(this->getBalance() + money);
    cout << "������ճɹ���" << endl;
    delete p;
    p = nullptr;
}
/*
* �����Ա��Ϣ�洢���ļ���
*/
void Courier::saveCourier()
{
    ofstream fout;
    fout.open("Courier/"+this->getUserName() + ".txt");//������д���ļ�
    fout << getUserName() << endl << getPassword() << endl <<
        getName() << endl << getNumber() << endl <<
        getBalance() << endl << getCompany() << endl;//�洢ǰ��������
    fout.close();//�ر��ļ�
}
void Courier::saveCourierToList()
{
    ofstream fout;
    fout.open( "Courier/0CourierList.txt",ios::app);//������д���ļ�
    fout << this->getUserName() << endl;
    fout.close();
}
/*
* ���ļ��ڶ�ȡ���Ա��Ϣ
*/
bool Courier::readCourier()
{
    ifstream fin;//�ļ�������
    fin.open("Courier/"+getUserName() + ".txt");//���û���Ϣ�ļ�
    if (!fin)//�����ڸ��û�����Ӧ���ļ�
        cout << "�˺Ų�����" << endl;
    else {
        string s;
        stringstream stream;//�����������ڽ���string�����ֵ�ת��
        double n;
        getline(fin, s);//���ж�������
        getline(fin, s);
        if (s != getPassword())
        {
            cout << "�������" << endl;
            fin.close();
            return false;
        }
        else {
            getline(fin, s);
            setName(s);
            getline(fin, s);
            setNumber(s);
            getline(fin, s);
            stream << s;
            stream >> n;
            setBalance(n);
            getline(fin, s);
            setCompany(s);
        }
    }
    fin.close();
    return true;
}
/*
* ������Ա��Ϣ
*/
void Courier::printCourier()
{
    cout << "�û����� " << getUserName()
        << "  ���룺 " << getPassword()
        << "  ������ " << getName()
        << "  �绰���룺 " << getNumber()
        << "  �û��� " << getBalance()
        << "  ������˾�� " << getCompany()
        << endl;
}

void Courier::changeMessage()
{
    int judge = 0;
    string s;
    cout << "�Ƿ��޸��˺�����(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "������������:" << endl;
        cin >> s;
        setPassword(s);
    }
    cout << "�Ƿ��޸�����(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "������������:" << endl;
        cin >> s;
        setName(s);
    }
    cout << "�Ƿ��޸ĵ绰����(1.�ǣ�2�񣩣�" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "�������µ绰����:" << endl;
        cin >> s;
        setNumber(s);
    }
}

void Courier::setPacket(Goods good, int index)
{
    this->assigned[index] = good;
}
