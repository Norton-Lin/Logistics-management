#include"Goods.h"
/*
* 快递类构造函数
*/
Goods::Goods() {
    state = State::Unsign;
    expressNumber = "";
    sendTime = { 0 };
    receiveTime = { 0 };
    sender = "";
    recipient = "";
    description = "";
};
/**
* 获取快递状态
* @return 返回Stata类型数据
*/
State Goods::getState() {
    return state;
}
/**
* 获取快递状态
* @return 返回string类型数据
*/
string Goods::getState(int index)
{
    string answer = "1";
    if (this->state == State::Sign)
        answer = "0";
    return answer;

}
/*
* 获取快递编号
* @return string型
*/
string Goods::getExpressNumber() {
    return expressNumber;
}
/*
* 获取快递发送时间
* @return array<int,6>型(年、月、日、时、分、秒）
*/
array<int, 6> Goods::getSendTime() {
    return sendTime;
}
/*
* 获取快递发送时间
* @param int型 无义 用于重载
* @return string型(年-月-日 时:分:秒）
*/
string Goods::getSendTime(int index)
{
    string answer = "";
    answer.append(to_string(this->sendTime[0]) + "-" + to_string(this->sendTime[1]) + "-" + to_string(this->sendTime[2]) + " "
        + to_string(this->sendTime[3]) + ":" + to_string(this->sendTime[4]) + ":" + to_string(this->sendTime[5]));
    return answer;
}
/**
* 获取快递的签收时间
* @return array<int,6>型(年、月、日、时、分、秒）
*/
array<int, 6> Goods::getReceiveTime() {
    return receiveTime;
}
/*
* 获取快递签收时间
* @param int型 无义 用于重载
* @return string型(年-月-日 时:分:秒）
*/
string Goods::getReceiveTime(int index)
{
    string answer = "";
    answer.append(to_string(this->receiveTime[0]) + "-" + to_string(this->receiveTime[1]) + "-" + to_string(this->receiveTime[2]) + " "
        + to_string(this->receiveTime[3]) + ":" + to_string(this->receiveTime[4]) + ":" + to_string(this->receiveTime[5]));
    return answer;
}
/*
* 获取寄件人姓名
* @return string型
*/
string Goods::getSender() {
    return sender;
}
/*
* 获取收件人姓名
* @return string型
*/
string Goods::getRecipient() {
    return recipient;
}
/*
* 获取快递描述
* @return string型
*/
string Goods::getDescribtion() {
    return description;
}
/*
* 获取承运公司
* @return string型
*/
string Goods::getCompany()
{
    return this->company;
}
/*
* 修改快递状态
* @param State型 新状态
*/
void Goods::setState(State state) {
    this->state = state;
}
/*
* 设置快递状态
* @param string型，新状态
*/
void Goods::setState(string state)
{
    if (state[0] == '0')
        this->state = State::Sign;
    else
        this->state = State::Unsign;
}
/*
* 设置快递编号
* @param String型，新编号
*/
void Goods::setExpressNumber(string expressNumber) {
    this->expressNumber = expressNumber;
}
/*
* 设置快递编号
* @param time_t型
* 根据时间生成编号
*/
void Goods::setExpressNumber(time_t* currentTime)
{
    string s = getCompany();
    string s1;
    stringstream stream;
    if (s == "顺丰")
        expressNumber = "1";
    else if (s == "邮政")
        expressNumber = "2";
    else if (s == "京东")
        expressNumber = "3";
    else if (s == "韵达")
        expressNumber = "4";
    else if (s == "申通")
        expressNumber = "5";
    else if (s == "圆通")
        expressNumber = "6";
    expressNumber.append(to_string(*currentTime));
    srand(time(0));//根据时间生成随机树种
    stream << (rand() % 1000 + 100);
    stream >> s1;
    expressNumber.append(s1);
}
/*
* 修改快递发送时间
* @param array<int, 6>型，新发送时间
*/
void Goods::setSendTime(array<int, 6> sendTime) {
    this->sendTime = sendTime;
}
/*
* 修改快递发送时间
* @param string型，新发送时间
*/
void Goods::setSendTime(string sendTime)
{
    int head = 0;
    int tail = 0;
    string num;
    for (int i = 0; i < 6; i++)
    {
        if (i < 2)
            tail = sendTime.find('-', head);
        else if (i == 2)
            tail = sendTime.find(' ', head);
        else if (i < 5)
            tail = sendTime.find(':', head);
        else
            tail = num.size();
        num = sendTime.substr(head, tail - head);
        this->sendTime[i] = atoi(num.data());
        head = tail + 1;
    }
}
/*
* 修改快递发送时间
* @param time_t型，新发送时间
*/
void Goods::setSendTime(time_t* sendTime)
{
    struct tm temp;
    gmtime_s(&temp, sendTime);
    this->sendTime[0] = temp.tm_year + 1900;
    this->sendTime[1] = temp.tm_mon + 1;
    this->sendTime[2] = temp.tm_mday;
    this->sendTime[3] = (temp.tm_hour + 8) % 24;
    this->sendTime[4] = temp.tm_min;
    this->sendTime[5] = temp.tm_sec;
}
/*
* 修改快递签收时间
* @param array<int, 6>型，新签收时间
*/
void Goods::setReceiveTime(array<int, 6> receiveTime) {
    this->receiveTime = receiveTime;
}
/*
* 修改快递签收时间
* @param string型，新签收时间
*/
void Goods::setReceiveTime(string receiveTime)
{
    int head = 0;
    int tail = 0;
    string num;
    for (int i = 0; i < 6; i++)
    {
        if (i < 2)
            tail = receiveTime.find('-', head);
        else if (i == 2)
            tail = receiveTime.find(' ', head);
        else if (i < 5)
            tail = receiveTime.find(':', head);
        else
            tail = num.size();
        num = receiveTime.substr(head, tail - head);
        this->receiveTime[i] = atoi(num.data());
        head = tail + 1;
    }
}
/*
* 修改快递签收时间
* @param time_t型，新签收时间
*/
void Goods::setReceiveTime(time_t* receiveTime)
{
    struct tm temp;
    gmtime_s(&temp, receiveTime);
    this->receiveTime[0] = temp.tm_year + 1900;
    this->receiveTime[1] = temp.tm_mon + 1;
    this->receiveTime[2] = temp.tm_mday;
    this->receiveTime[3] = (temp.tm_hour + 8) % 24;
    this->receiveTime[4] = temp.tm_min;
    this->receiveTime[5] = temp.tm_sec;
}
/*
* 修改快递发送者
* @param string型，新快递发送者
*/
void Goods::setSender(string sender) {
    this->sender = sender;
}
/*
* 修改快递签收者
* @param string型，新快递签收者
*/
void Goods::setRecipient(string recipient) {
    this->recipient = recipient;
}
/*
* 修改快递描述
* @param string型，新快递描述
*/
void Goods::setDecription(string description) {
    this->description = description;
}
/*
* 文件流操作，从文件中读取快递信息
* @param ifstream& 型，读文件流
* @return Goods型 返回快递货物对象
*/
Goods Goods::readGoods(ifstream& fin)
{
    int n;
    string s;
    stringstream stream;//流操作，用于进行类型转换
    array<int, 6> a;
    std::getline(fin, s);
    stream << s;
    stream >> n;//string类型转int
    if (n == 0)
        setState(State::Sign);
    else
        setState(State::Unsign);
    std::getline(fin, s);
    setExpressNumber(s);
    for (int i = 0; i < 6; i++) {
        std::getline(fin, s, '.');
        stream << s;
        stream >> a[i];
    }
    setSendTime(a);
    for (int i = 0; i < 6; i++) {
        std::getline(fin, s, '.');
        stream << s;
        stream >> a[i];
    }
    setReceiveTime(a);
    std::getline(fin, s);
    setSender(s);
    std::getline(fin, s);
    setRecipient(s);
    return *this;
}
/*
* 文件流操作，向文件中存储快递信息
* @param ofstream& 型，写文件流
*/
void Goods::saveGoods(ofstream& fout)
{
    int n = 1;
    if (getState() == State::Sign)
        n = 0;
    fout << n << endl << getExpressNumber() << endl;
    for (int i = 0; i < 5; i++)
        fout << getSendTime().at(i) << '.';
    fout << endl;
    for (int i = 0; i < 5; i++)
        fout << getReceiveTime().at(i) << '.';
    fout << endl;
    fout << getSender() << endl << getRecipient() << endl
        << getDescribtion() << endl;
}
/*
* 修改承运公司
* @param string型 新快递公司
*/
void Goods::setCompany(string company)
{
    this->company = company;
}
/*
* 快递签收
* 用于设置签收状态和签收时间
*/
void Goods::signExpress()
{
    time_t time1 = time(0);
    setState(State::Sign);
    setReceiveTime(&time1);
    cout << "签收成功！" << endl;
}

