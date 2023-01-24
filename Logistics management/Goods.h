#pragma once
#include"head.h"
/*
* ���״̬ö����
*/
enum class State
{
    Sign,
    Unsign
};
/*
* �����
*/
class Goods
{
private:
    State state;                             //״̬
    string expressNumber;                    //��ݵ���
    array<int, 6> sendTime;                  //�ļ�ʱ��
    array<int, 6> receiveTime;               //�ռ�ʱ��
    string sender;                           //�ļ���
    string recipient;                        //�ռ���
    string description;                      //��Ʒ����
    string company;                          //��ݳ��˹�˾
public:
    Goods();                                            //���캯��
    State getState();                                   //��ȡ��ǰ���״̬
    string getState(int index);                         //��ȡ�ַ����͵ĵ�ǰ���״̬
    string getExpressNumber();                          //��ȡ��ݵ���
    array<int, 6> getSendTime();                        //��ȡ�ļ�ʱ��
    string getSendTime(int index);                      //��ȡ�ַ����͵ļļ�ʱ��
    array<int, 6> getReceiveTime();                     //��ȡ�ռ�ʱ��
    string getReceiveTime(int index);                   //��ȡ�ַ����͵��ռ�ʱ��
    string getSender();                                 //��ȡ�ļ���
    string getRecipient();                              //��ȡ�ռ���
    string getDescribtion();                            //��ȡ��Ʒ����
    string getCompany();                                //��ȡ���˹�˾
    void setState(State state);                         //���õ�ǰ���״̬
    void setState(string state);                        //���õ�ǰ���״̬
    void setExpressNumber(string expressNumber);        //���ÿ�ݵ���
    void setExpressNumber(time_t* currentTime);         //����ʱ���趨��ݵ���
    void setSendTime(array<int, 6> sendTime);           //���üļ�ʱ��
    void setSendTime(string sendTime);                  //���üļ�ʱ��
    void setSendTime(time_t *sendTime);                 //����ʱ���趨�ļ�ʱ��
    void setReceiveTime(array<int, 6> receiveTime);     //�����ռ�ʱ��
    void setReceiveTime(string receiveTime);               //�����ռ�ʱ��
    void setReceiveTime(time_t* receiveTime);           //����ʱ�������ռ�ʱ��
    void setSender(string sender);                      //���üļ���
    void setRecipient(string recipient);                //�����ռ���
    void setDecription(string description);             //������Ʒ����
    Goods readGoods(ifstream &fin);                     //���ļ��ж�ȡ�����Ϣ
    void saveGoods(ofstream &fout);                     //����Ʒ��Ϣ���浽�ļ���
    void setCompany(string company);                    //���ó��˹�˾
    void signExpress();                                 //ǩ�տ��
};
