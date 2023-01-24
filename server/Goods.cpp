#include"Goods.h"
#include "Account.h"
/*
* ����๹�캯��
*/
Goods::Goods() {
    type = Type::common;
    state = State::Uncollect;
    expressNumber = "";
    sendTime = { 0 };
    collectTime = { 0 };
    receiveTime = { 0 };
    sender = "";
    courier = "";
    recipient = "";
    description = "";
}
/*
* ��ȡ�������
* @return Type
*/
Type Goods::getType()
{
    return type;
}
/*
* ��ȡ�������
* @param intռλ��
* @return string
*/
string Goods::getType(int index)
{
    QString answer = "";
    if (type == Type::book)
        answer = "�鱾";
    else if (type == Type::fragile)
        answer = "����Ʒ";
    else
        answer = "��ͨ���";
    return Account::qTos(answer);
}
/**
* ��ȡ���״̬
* @return ����Stata��������
*/
State Goods::getState() {
    return state;
}
/**
* ��ȡ���״̬
* @return ����string��������
*/
string Goods::getState(int index)
{
    QString answer = "δǩ��";
    if (this->state == State::Sign)
        answer = "��ǩ��";
    else if (this->state == State::Uncollect)
        answer = "δ����";
    return Account::qTos(answer);
    /**  string answer = "δǩ��";
      if (this->state == State::Sign)
          answer = "��ǩ��";
      else if (this->state == State::Uncollect)
          answer = "δ����";
      return answer;*/

}
/*
* ��ȡ�������/����
* @return int
*/
int Goods::getNumber()
{
    return number;
}
/*
* ��ȡ��ݱ��
* @return string��
*/
string Goods::getExpressNumber() {
    return expressNumber;
}
/*
* ��ȡ��ݷ���ʱ��
* @return array<int,6>��(�ꡢ�¡��ա�ʱ���֡��룩
*/
array<int, 6> Goods::getSendTime() {
    return sendTime;
}
/*
* ��ȡ��ݷ���ʱ��
* @param int�� ���� ��������
* @return string��(��-��-�� ʱ:��:�룩
*/
string Goods::getSendTime(int index)
{
    string answer = "";
    answer.append(to_string(this->sendTime[0]) + "-" + to_string(this->sendTime[1]) + "-" + to_string(this->sendTime[2]) + " "
        + to_string(this->sendTime[3]) + ":" + to_string(this->sendTime[4]) + ":" + to_string(this->sendTime[5]));
    return answer;
}
/**
* ��ȡ��ݵ�ǩ��ʱ��
* @return array<int,6>��(�ꡢ�¡��ա�ʱ���֡��룩
*/
array<int, 6> Goods::getReceiveTime() {
    return receiveTime;
}
/*
* ��ȡ���ǩ��ʱ��
* @param int�� ���� ��������
* @return string��(��-��-�� ʱ:��:�룩
*/
string Goods::getReceiveTime(int index)
{
    string answer = "";
    answer.append(to_string(this->receiveTime[0]) + "-" + to_string(this->receiveTime[1]) + "-" + to_string(this->receiveTime[2]) + " "
        + to_string(this->receiveTime[3]) + ":" + to_string(this->receiveTime[4]) + ":" + to_string(this->receiveTime[5]));
    return answer;
}
/**
* ��ȡ��ݵ�����ʱ��
* @return array<int,6>��(�ꡢ�¡��ա�ʱ���֡��룩
*/
array<int, 6> Goods::getCollectTime()
{
    return collectTime;
}
/*
* ��ȡ�������ʱ��
* @param int�� ���� ��������
* @return string��(��-��-�� ʱ:��:�룩
*/
string Goods::getCollectTime(int index)
{
    string answer = "";
    answer.append(to_string(this->collectTime[0]) + "-" + to_string(this->collectTime[1]) + "-" + to_string(this->collectTime[2]) + " "
        + to_string(this->collectTime[3]) + ":" + to_string(this->collectTime[4]) + ":" + to_string(this->collectTime[5]));
    return answer;
}
/*
* ��ȡ�ļ�������
* @return string��
*/
string Goods::getSender() {
    return sender;
}
/*
* ��ȡ���Ա����
* @return string��
*/
string Goods::getCourier()
{
    if (courier == "")
        return " ";
    return courier;
}
/*
* ��ȡ�ռ�������
* @return string��
*/
string Goods::getRecipient() {
    return recipient;
}
/*
* ��ȡ�������
* @return string��
*/
string Goods::getDescribtion() {
    return description;
}
/*
* ��ȡ���˹�˾
* @return string��
*/
string Goods::getCompany()
{
    return this->company;
}
/*
* ���ÿ������
* @param Type
*/
void Goods::setType(Type type)
{
    this->type = type;
}
/*
* ���ÿ������
* @param string
*/
void Goods::setType(string temp)
{
    QString type = Account::sToq(temp);
    if (type == "��ͨ���")
        this->type = Type::common;
    else if (type == "�鱾")
        this->type = Type::book;
    else
        this->type = Type::fragile;
}
/*
* �޸Ŀ��״̬
* @param State�� ��״̬
*/
void Goods::setState(State state) {
    this->state = state;
}
/*
* ���ÿ��״̬
* @param string�ͣ���״̬
*/
void Goods::setState(string temp)
{
    QString state = Account::sToq(temp);
    if (state == "��ǩ��")
        this->state = State::Sign;
    else if (state == "δǩ��")
        this->state = State::Unsign;
    else
        this->state = State::Uncollect;
}
void Goods::setNumber(int number)
{
    this->number = number;
}
/*
* ���ÿ�ݱ��
* @param String�ͣ��±��
*/
void Goods::setExpressNumber(string expressNumber) {
    this->expressNumber = expressNumber;
}
/*
* ���ÿ�ݱ��
* @param time_t��
* ����ʱ�����ɱ��
*/
void Goods::setExpressNumber(time_t* currentTime)
{
    string s = getCompany();
    string s1;
    stringstream stream;
    if (s == "˳��")
        expressNumber = "1";
    else if (s == "����")
        expressNumber = "2";
    else if (s == "����")
        expressNumber = "3";
    else if (s == "�ϴ�")
        expressNumber = "4";
    else if (s == "��ͨ")
        expressNumber = "5";
    else if (s == "Բͨ")
        expressNumber = "6";
    expressNumber.append(to_string(*currentTime));
    srand(time(0));//����ʱ�������������
    stream << (rand() % 1000 + 100);
    stream >> s1;
    expressNumber.append(s1);
}
/*
* �޸Ŀ�ݷ���ʱ��
* @param array<int, 6>�ͣ��·���ʱ��
*/
void Goods::setSendTime(array<int, 6> sendTime) {
    this->sendTime = sendTime;
}
/*
* �޸Ŀ�ݷ���ʱ��
* @param string�ͣ��·���ʱ��
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
* �޸Ŀ�ݷ���ʱ��
* @param time_t�ͣ��·���ʱ��
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
* �޸Ŀ��ǩ��ʱ��
* @param array<int, 6>�ͣ���ǩ��ʱ��
*/
void Goods::setReceiveTime(array<int, 6> receiveTime) {
    this->receiveTime = receiveTime;
}
/*
* �޸Ŀ��ǩ��ʱ��
* @param string�ͣ���ǩ��ʱ��
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
* �޸Ŀ��ǩ��ʱ��
* @param time_t�ͣ���ǩ��ʱ��
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
* �޸Ŀ������ʱ��
* @param array<int, 6>�ͣ�������ʱ��
*/
void Goods::setCollectTime(array<int, 6> collecttime)
{
    this->collectTime = collectTime;
}
/*
* �޸Ŀ������ʱ��
* @param string�ͣ�������ʱ��
*/
void Goods::setCollectTime(string collectTime)
{
    int head = 0;
    int tail = 0;
    string num;
    for (int i = 0; i < 6; i++)
    {
        if (i < 2)
            tail = collectTime.find('-', head);
        else if (i == 2)
            tail = collectTime.find(' ', head);
        else if (i < 5)
            tail = collectTime.find(':', head);
        else
            tail = num.size();
        num = collectTime.substr(head, tail - head);
        this->collectTime[i] = atoi(num.data());
        head = tail + 1;
    }
}
/*
* �޸Ŀ������ʱ��
* @param time_t�ͣ�������ʱ��
*/
void Goods::setCollectTime(time_t* collectTime)
{
    struct tm temp;
    gmtime_s(&temp, collectTime);
    this->collectTime[0] = temp.tm_year + 1900;
    this->collectTime[1] = temp.tm_mon + 1;
    this->collectTime[2] = temp.tm_mday;
    this->collectTime[3] = (temp.tm_hour + 8) % 24;
    this->collectTime[4] = temp.tm_min;
    this->collectTime[5] = temp.tm_sec;
}
/*
* �޸Ŀ�ݷ�����
* @param string�ͣ��¿�ݷ�����
*/
void Goods::setSender(string sender) {
    this->sender = sender;
}
/*
* ���ÿ�����տ��Ա
* @param string�ͣ��¿�ݷ�����
*/
void Goods::setCourier(string courier)
{
    this->courier = courier;
}
/*
* �޸Ŀ��ǩ����
* @param string�ͣ��¿��ǩ����
*/
void Goods::setRecipient(string recipient) {
    this->recipient = recipient;
}
/*
* �޸Ŀ������
* @param string�ͣ��¿������
*/
void Goods::setDecription(string description) {
    this->description = description;
}
/*
* �ļ������������ļ��ж�ȡ�����Ϣ
* @param ifstream& �ͣ����ļ���
* @return Goods�� ���ؿ�ݻ������
*/
Goods Goods::readGoods(ifstream& fin)
{
    int n;
    string s;
    stringstream stream;//�����������ڽ�������ת��
    array<int, 6> a;
    std::getline(fin, s);
    stream << s;
    stream >> n;//string����תint
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
* �ļ������������ļ��д洢�����Ϣ
* @param ofstream& �ͣ�д�ļ���
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
* �޸ĳ��˹�˾
* @param string�� �¿�ݹ�˾
*/
void Goods::setCompany(string company)
{
    this->company = company;
}
/*
* ���ǩ��
* ��������ǩ��״̬��ǩ��ʱ��
*/
void Goods::signExpress()
{
    time_t time1 = time(0);
    setState(State::Sign);
    setReceiveTime(&time1);
    cout << "ǩ�ճɹ���" << endl;
}
/*
* ������
*/
void Goods::distributeCourier(string s)
{
    setCourier(s);
    cout << "��ݷ���ɹ���" << endl;
}
/*
* �����ݼ۸�
* @return double
*/
double Goods::getPiece()
{
    return number * 5;
}
/*
* Fragile�๹�캯��
*/
Fragile::Fragile(int num)
{
    setNumber(num);
    setType(Type::fragile);
}
/*
* �����ݼ۸�
* @return double
*/
double Fragile::getPiece()
{
    return getNumber() * 8;
}
/*
* Book�๹�캯��
*/
Book::Book(int num) :Goods()
{
    setNumber(num);
    setType(Type::book);
}
/*
* �����ݼ۸�
* @return double
*/
double Book::getPiece()
{
    return getNumber() * 2;
}
/*
* Common�๹�캯��
*/
Common::Common(int num)
{
    setNumber(num);
}
/*
* �����ݼ۸�
* @return double
*/
double Common::getPiece()
{
    return getNumber() * 5;
}
