#include "Account.h"
#include "Database.h"
/*
* 账号类无参构造函数
*/
Account::Account()
{
    //this->userName = "";
   // this->name = "";
   // this->password = "";
   // this->number = "";
    this->balance = 0;//余额初始化
}
/*
* 账号类有参构造函数
* 根据用户名和密码创建账号对象
*/
Account::Account(string username, string password)
{
    this->userName = username;
    this->password = password;
}
/**
 * 获取用户名
 * @return string
 */
string Account::getUserName() {
    return userName;
}
/**
 * 获取姓名
 * @return string
 */
string Account::getName() {
    return name;
}
/**
 * 获取电话号码
 * @return string
 */
string Account::getNumber() {
    return number;
}
/**
 * 获取密码
 * @return string
 */
string Account::getPassword() {
    return password;
}
/**
 * 获取余额
 * @return int
 */
int Account::getBalance() {
    return balance;
}
/*
* 获取余额
* @return string
*/
string Account::getBalance(int index)
{
    string balance;
    stringstream stream;
    stream << getBalance();
    stream >> balance;
    return balance;
}
/**
 * 修改用户名
 * @param string型 username
 */
void Account::setUserName(string username) {
    this->userName = username;
}
/**
 * 修改姓名
 * @param string型 name
 */
void Account::setName(string name) {
    this->name = name;
}
/**
 * 修改电话号码
 * @param string型 number
 */
void Account::setNumber(string number) {
    this->number = number;
}
/**
 * 修改密码
 * @param string型 password
 */
void Account::setPassword(string password) {
    this->password = password;
}
/**
 * 修改余额
 * @param int型 balance 
 */
void Account::setBalance(int balance) {
    this->balance = balance;
}
/*
* 读取所有存在用户名
* @param vector<string>& userList
* 引用传递，参数用于存储用户名列表
*/
void Account::readAllUserName(vector<string>& userList)
{
    string s;
    ifstream fin;
    fin.open("D:/Desktop/program design/Logistics management/Logistics management/User.txt");//打开用户名文件
    while (getline(fin, s))//逐行读取信息
        userList.emplace_back(s);
}
/*
* User类无参构造函数
*/
User::User()
{

}
/**
* 有参构造函数
* 根据用户名和密码创建用户对象
*/
User::User(string username, string password):Account(username,password){
   
}
/**
 * User类对象有参构造函数
 * @param string型 username
 * @param string型 name
 * @param string型 number
 * @param string型 password
 * @param string型 address
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
 * 获取地址
 * @return string
 */
string User::getAddress() {
    return address;
}
/*
* 获取发送的快递列表
* @return vector<Goods>
*/
vector<Goods> User::getSend()
{
    return this->send;
}
/*
* 获取接收的快递列表
* @return vector<Goods>
*/
vector<Goods> User::getReceive()
{
    return this->receive;
}
/**
 *  修改地址
 * @param address
 */
void User::setAddress(string address) {
    this->address = address;
}
/**
 * User类对象注册函数
 * @param string型 username 用户名
 * @param string型 name 姓名
 * @param string型 number 电话号码
 * @param string型 password 账号密码
 * @param string型 address 地址
 * @param int型 balance 余额
 */
void User::registerAccount(string username, string name, string number, string password, string address,int balance)
{
    setUserName(username);
    setName(name);
    setNumber(number);
    setPassword(password);
    setAddress(address);
    setBalance(balance);
}
/**
 * User类对象注册函数
 * @return User 用户
 */
void User::registerAccount()
{    
    string username;
    string name;
    string number;
    string password;
    string address;
    int balance = 0;
    cout << "请输入用户名" << endl;
    cin >> username;
    cout << "请输入姓名" << endl;
    cin >> name;
    cout << "请输联系电话" << endl;
    cin >> number;
    cout << "请输入密码" << endl;
    cin >> password;
    cout << "请输入联系地址" << endl;
    cin >> address;
    setUserName(username);
    setName(name);
    setNumber(number);
    setPassword(password);
    setAddress(address);
    setBalance(balance);
}
/*
* 发送快递
* @param vector<string>型 userList 用户名列表 用于检查目标用户是否存在
* @param vector<string>型 companyList 物流公司列表 用于检查物流公司是否存在
*/
void User::sendExpress(vector<string> userList, vector<string> companyList)
{
    Goods good;
    string name;
    time_t currentTime = time(0);//获取当前系统时间
    boolean judge = false;
    good.setSendTime(&currentTime);//根据系统时间确定快递编码
    cout << "请输入物品描述" << endl;
    cin >> name;
    good.setDecription(name);
    while (!judge)
    {
        cout << "请输入收件人姓名" << endl;
        cin >> name;
        for (int i = 0; i < userList.size(); i++)
            if (name == userList[i])
            {
                judge = true;
                break;
            }
        if (!judge)
            cout << "用户不存在！请重新输入" << endl;
    }
    good.setRecipient(name);
    while (judge)
    {
        cout << "请输入快递公司" << endl;
        cin >> name;
        for (int i = 0; i < companyList.size(); i++)
            if (name == companyList[i])
            {
                judge = false;
                break;
            }
        if (judge)
            cout << "快递公司不存在！请重新输入" << endl;
    }
    good.setCompany(name);
    good.setState(State::Unsign);
    good.setSender(this->getUserName());
    good.setReceiveTime("0-0-0 0:0:0");
    good.setExpressNumber(&currentTime);
    if (this->getBalance() < 15)
        cout << "余额不足" << endl;
    else
    {
  //      this->setBalance(this->getBalance() - 15);
        this->addSend(good);
        Database* database = new Database();
        database->connectDatabase();
        database->insertPackage(good);
        database->addBalance(good.getCompany());
        database->FreeConnect();
        delete database;
        database = nullptr;
    }
}
/**
* 添加发送的快递
* @param Goods型 good
*/
void User::addSend(Goods good)
{
    setBalance(getBalance() - 15);//发送快递需要花费15元
    this->send.push_back(good);
}
/**
* 添加接收的快递
* @param Goods型 good
*/
void User::addReceive(Goods good)
{
    this->send.push_back(good);
}
/*
* 设置发送的快递列表
* @param vector<Goods>型 send
*/
void User::setSend(vector<Goods> send)
{
    this->send = send;
}
/*
* 设置接收的快递列表
* @param vector<Goods>型 receive
*/
void User::setReceive(vector<Goods> receive)
{
    this->receive = receive;
}
/*
* 设置指定的接收快递
* @param Goods型 good
* @param int型 index 该快递在接收列表中的位置
*/
void User::setReceive(Goods good, int index)
{
    this->receive[index] = good;
}
/*
* 将用户信息保存到文件中
*/
void User::saveUser()
{
    ofstream fout;
    fout.open(this->getUserName() + ".txt");//将数据写入文件
    fout << getUserName() << endl << getPassword() << endl << 
        getName() << endl << getNumber() << endl << 
        getBalance() << endl << getAddress() << endl;//存储前六个属性
    fout.close();//关闭文件
  /*  fstream fin;
    string username;
    bool judge = true;
    fin.open("D:/Desktop/program design/Logistics management/Logistics management/User.txt",ios::in|ios::out);
    while (getline(fin, username))//判断该用户是否已经存在
    {
        if (username == getUserName())
        {
            judge = false;
            break;
        }
    }
    if (judge)//用户本不存在
    {
        fin.seekg(0, ios::end);
        fin << username;
    }
    fin.close();*/
}
/*
* 从文件中读取用户信息
*/
bool User::readUser() {
    ifstream fin;//文件输入流
    fin.open(getUserName() + ".txt");//打开用户信息文件
    if (!fin)//不存在该用户名对应的文件
    {
        cout << "账号不存在" << endl;
        return false;
    }
    else {
        string s;
        stringstream stream;//流操作，用于进行string和数字的转换
        int n;
        getline(fin, s);//逐行读入数据
        getline(fin, s);
        if (s != getPassword())
        {
            cout << "密码错误" << endl;
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
* 格式化输出用户信息
*/
void User::printUser()
{
    cout << "用户名： " << getUserName()
        << "  密码： " << getPassword()
        << "  姓名： " << getName()
        << "  电话号码： " << getNumber()
        << "  用户余额： " << getBalance()
        << "  地址： " << getAddress()
        <<endl;
}
/**
*USer类析构函数
*/
User::~User()
{
    //vector<Goods>().swap(*send);
    //vector<Goods>().swap(*receive);
}
/**
* 管理员类无参构造函数
*/
Manager::Manager() {

}
/**
* 管理员类有参构造函数
* 根据用户名和密码构造管理员类对象
*/
Manager::Manager(string username, string password):Account( username,  password){

}
/**
* 获取管理员所属公司
* @return string
*/
string Manager::getCompany()
{
    return this->company;
}
/**
* 查询所有快递信息
* @return vector<Goods>
*/
vector<Goods> Manager::getPacket()
{
    return packet;
}
/**
* 设置管理员所在公司
* @param string型 company
*/
void Manager::setCompany(string company)
{
    this->company = company;
}
/**
* 设置快递信息
* @param vector<Goods>型 packet
*/
void Manager::setPacket(vector<Goods> packet)
{
    this->packet = packet;
}
/**
* 输出名下所有快递信息
* @param vector<Goods>型 packet
*/
void Account::printPacket(vector<Goods> packet)
{
    int num = 0;
    for (auto s : packet)//输出列表中的所有快递信息
    {
        cout << ++num<<"."<<endl;
        printPacket(s);
    }
}
/**
* 输出单个快递信息
* @param Goods型 packet
*/
void Account::printPacket(Goods packet)
{
    cout << "快递状态 ： ";
    if (packet.getState() == State::Unsign)
        cout << "未签收" << endl;
    else
        cout << " 已签收" << endl;
    cout << "快递单号 ： " << packet.getExpressNumber() << endl;
    cout << "快递发送时间 : " << packet.getSendTime(1) << endl;
    cout << "快递签收时间 : " << packet.getReceiveTime(1) << endl;
    cout << "寄件人 ： " << packet.getSender() << endl;
    cout << "签收人 ： " << packet.getRecipient() << endl;
    cout << "快递描述 ： " << packet.getDescribtion() << endl<<endl;
}
/**
* 根据快递编号查询快递
* @param Goods&型 good  引用传递，用于存储查询得的快递信息
* @param string型 s     快递编号
* @param vector<Goods>型 source  待查询快递列表
* @return bool 成功为true,失败为false
*/
bool Account::checkPacket(Goods& good, string s,vector<Goods> goods)
{
    for(auto i:goods)
        if (s == i.getExpressNumber())//比对快递编号
        {
            good = i;
            return true;
        }
    return false;
}
/**
* 查询用户未签收的快递
* @param vector<Goods>&型 good  引用传递，用于存储查询得的快递信息
* @param State型 s     快递状态
* @param vector<Goods>型 source  待查询快递列表
* @return bool 成功为true,失败为false
*/
bool Account::checkPacket(vector<Goods>& goods, State state, vector<Goods> source)
{
    bool judge = false;
    for (auto i : source)
        if (state == i.getState())//比对快递状态
        {
            goods.emplace_back(i);
            judge = true;
        }
    return judge;
}
/**
* 根据用户名查询快递信息
* @param vector<Goods>&型 good  引用传递，用于存储查询得的快递信息
* @param string型 s     用户名
* @param bool型 index  true表寄件人，false表收件人
* @param vector<Goods>型 source  待查询快递列表
* @return bool 成功为true,失败为false
*/
bool Account::checkPacket(vector<Goods>& goods, string s, bool index,vector<Goods> source)
{
    bool judge = false;
    if (index)//搜寻目标是寄件人
    {
        for (auto i : source)
            if (i.getSender() == s)//比对寄件人信息
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    else//搜寻目标是收件人
    {
        for (auto i : source)
            if (i.getRecipient() == s)//比对收件人信息
            {
                goods.emplace_back(i);
                judge = true;
            }
    }
    return judge;
}
/**
* 根据时间查询快递信息
* @param vector<Goods>&型 good  引用传递，用于存储查询得的快递信息
* @param array<int, 6>型 s     待查询日期
* @param bool型 index  true表寄件时间，false表收件时间
* @param vector<Goods>型 source  待查询快递列表
* @return bool 成功为true,失败为false
*/
bool Account::checkPacket(vector<Goods>& goods, array<int, 6> s, bool index, vector<Goods> source)
{
    bool judge = false;
    if (index)//比对目标是寄件时间
        for (auto i : source)
            if (i.getSendTime()[0] == s[0]&& i.getSendTime()[1] == s[1] && i.getSendTime()[2] == s[2])//比较寄件时间（年月日）
            {
                goods.emplace_back(i);
                judge = true;
            }
    else     //比对目标是收件时间                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        for (auto i : source)
            if (i.getReceiveTime()[0] == s[0] && i.getReceiveTime()[1] == s[1] && i.getReceiveTime()[2] == s[2])//比较收件时间（年月日）
            {
                   goods.emplace_back(i);
                   judge = true;
             }
    return judge;
}
/*
* 修改账号信息
*/
void User::changeMessage()
{
    int judge = 0;
    string s;
    cout << "是否修改账号密码(1.是，2否）：" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "请输入新密码:" << endl;
        cin >> s;
        setPassword(s);
    }
    cout << "是否修改姓名(1.是，2否）：" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "请输入新姓名:" << endl;
        cin >> s;
        setName(s);
    }
    cout << "是否修改电话号码(1.是，2否）：" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "请输入新电话号码:" << endl;
        cin >> s;
        setNumber(s);
    }
    cout << "是否修改地址(1.是，2否）：" << endl;
    cin >> judge;
    if (judge == 1)
    {
        cout << "请输入新地址:" << endl;
        cin >> s;
        setAddress(s);
    }
    
}
/*
* 根据用户名读取账号信息
* @param string型 用户名
* @return User型
*/
User Manager::readUser(string username)
{
    ifstream fin;//文件输入流
    fin.open(username + ".txt");
    User user ;
    string s;
    stringstream stream;//流操作，用于进行string和数字的转换
    int n;
    getline(fin, s);//逐行读入数据
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