#pragma once
#include"head.h"
/*
* 快递状态枚举类
*/
enum class State
{
    Sign,
    Unsign
};
/*
* 快递类
*/
class Goods
{
private:
    State state;                             //状态
    string expressNumber;                    //快递单号
    array<int, 6> sendTime;                  //寄件时间
    array<int, 6> receiveTime;               //收件时间
    string sender;                           //寄件人
    string recipient;                        //收件人
    string description;                      //物品描述
    string company;                          //快递承运公司
public:
    Goods();                                            //构造函数
    State getState();                                   //获取当前快递状态
    string getState(int index);                         //获取字符串型的当前快递状态
    string getExpressNumber();                          //获取快递单号
    array<int, 6> getSendTime();                        //获取寄件时间
    string getSendTime(int index);                      //获取字符串型的寄件时间
    array<int, 6> getReceiveTime();                     //获取收件时间
    string getReceiveTime(int index);                   //获取字符串型的收件时间
    string getSender();                                 //获取寄件人
    string getRecipient();                              //获取收件人
    string getDescribtion();                            //获取物品描述
    string getCompany();                                //获取承运公司
    void setState(State state);                         //设置当前快递状态
    void setState(string state);                        //设置当前快递状态
    void setExpressNumber(string expressNumber);        //设置快递单号
    void setExpressNumber(time_t* currentTime);         //根据时间设定快递单号
    void setSendTime(array<int, 6> sendTime);           //设置寄件时间
    void setSendTime(string sendTime);                  //设置寄件时间
    void setSendTime(time_t *sendTime);                 //根据时间设定寄件时间
    void setReceiveTime(array<int, 6> receiveTime);     //设置收件时间
    void setReceiveTime(string receiveTime);               //设置收件时间
    void setReceiveTime(time_t* receiveTime);           //根据时间设置收件时间
    void setSender(string sender);                      //设置寄件人
    void setRecipient(string recipient);                //设置收件人
    void setDecription(string description);             //设置物品描述
    Goods readGoods(ifstream &fin);                     //从文件中读取快递信息
    void saveGoods(ofstream &fout);                     //将商品信息保存到文件中
    void setCompany(string company);                    //设置承运公司
    void signExpress();                                 //签收快递
};
