#include"Goods.h"
/*
* ����๹�캯��
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
    string answer = "1";
    if (this->state == State::Sign)
        answer = "0";
    return answer;

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
/*
* ��ȡ�ļ�������
* @return string��
*/
string Goods::getSender() {
    return sender;
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
void Goods::setState(string state)
{
    if (state[0] == '0')
        this->state = State::Sign;
    else
        this->state = State::Unsign;
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
* �޸Ŀ�ݷ�����
* @param string�ͣ��¿�ݷ�����
*/
void Goods::setSender(string sender) {
    this->sender = sender;
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

