#pragma once
#include"head.h"
/*
* ���״̬ö����
*/
enum class State
{
    Sign,//��ǩ��
    Unsign,//δǩ��
    Uncollect//δ����
};
enum class Type {
    common,
    book,
    fragile
};
/*
* �����
*/
class Goods
{
private:
    Type type;                               //�������
    State state;                             //״̬
    int number;                              //��Ʒ������kg������
    string expressNumber;                    //��ݵ���
    array<int, 6> sendTime;                  //�ļ�ʱ��
    array<int, 6> collectTime;               //����ʱ��
    array<int, 6> receiveTime;               //�ռ�ʱ��
    string sender;                           //�ļ���
    string courier;                          //���Ա
    string recipient;                        //�ռ���
    string description;                      //��Ʒ����
    string company;                          //��ݳ��˹�˾
public:
    Goods();                                            //���캯��
    Type getType();                                     //��ȡ�������
    string getType(int index);                          //��ȡ�ַ����͵Ŀ������
    State getState();                                   //��ȡ��ǰ���״̬
    string getState(int index);                         //��ȡ�ַ����͵ĵ�ǰ���״̬
    int getNumber();                                    //��ȡ��Ʒ����
    string getExpressNumber();                          //��ȡ��ݵ���
    array<int, 6> getSendTime();                        //��ȡ�ļ�ʱ��
    string getSendTime(int index);                      //��ȡ�ַ����͵ļļ�ʱ��
    array<int, 6> getReceiveTime();                     //��ȡ�ռ�ʱ��
    string getReceiveTime(int index);                   //��ȡ�ַ����͵��ռ�ʱ��
    array<int, 6> getCollectTime();                     //��ȡ����ʱ��
    string getCollectTime(int index);                   //��ȡ�ַ����͵�����ʱ��
    string getSender();                                 //��ȡ�ļ���
    string getCourier();                                //��ȡ���Ա
    string getRecipient();                              //��ȡ�ռ���
    string getDescribtion();                            //��ȡ��Ʒ����
    string getCompany();                                //��ȡ���˹�˾
    void setType(Type type);                            //���ÿ������
    void setType(string type);                          //���ÿ������
    void setState(State state);                         //���õ�ǰ���״̬
    void setState(string state);                        //���õ�ǰ���״̬
    void setNumber(int number);                         //������Ʒ����
    void setExpressNumber(string expressNumber);        //���ÿ�ݵ���
    void setExpressNumber(time_t* currentTime);         //����ʱ���趨��ݵ���
    void setSendTime(array<int, 6> sendTime);           //���üļ�ʱ��
    void setSendTime(string sendTime);                  //���üļ�ʱ��
    void setSendTime(time_t* sendTime);                 //����ʱ���趨�ļ�ʱ��
    void setReceiveTime(array<int, 6> receiveTime);     //�����ռ�ʱ��
    void setReceiveTime(string receiveTime);            //�����ռ�ʱ��
    void setReceiveTime(time_t* receiveTime);           //����ʱ�������ռ�ʱ��
    void setCollectTime(array<int, 6> collectTime);     //�����ռ�ʱ��
    void setCollectTime(string collectTime);            //�����ռ�ʱ��
    void setCollectTime(time_t* collectTime);           //����ʱ�������ռ�ʱ��
    void setSender(string sender);                      //���üļ���
    void setCourier(string courier);                    //���ÿ��Ա
    void setRecipient(string recipient);                //�����ռ���
    void setDecription(string description);             //������Ʒ����
//    Goods readGoods(ifstream& fin);                     //���ļ��ж�ȡ�����Ϣ
//    void saveGoods(ofstream& fout);                     //����Ʒ��Ϣ���浽�ļ���
    void setCompany(string company);                    //���ó��˹�˾
//    void signExpress();                                 //ǩ�տ��
//    void distributeCourier(string s);                   //������Ա
    virtual int getPiece();
};
class Fragile :public Goods {
public:
    Fragile(int num);
    int getPiece();

};
class Book :public Goods {
public:
    Book(int num);
    int getPiece();

};
class Common : public Goods {
public:
    Common(int num);
    int getPiece();
};
