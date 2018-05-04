//@file queue.h
//@brief 实现一个存储指令的队列
//@author wc
//@version 1.0
//@data 2018/3/12


#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdlib.h>
#include <windows.h>
#include "MSG.h"


struct node                   //链表队列节点结构体
{
    COORD pos;
    struct node *next;
};

class Queue
{
public:
    Queue();                  //构造函数
    Queue(Queue &q);          //拷贝构造函数
    ~Queue();                 //析构函数
    void push(COORD pos);   //入队列
    bool pop(COORD &pos);    //出队列
    int getlength();
    void EmptyQue();
private:
    struct node* top;         //队列头指针
    struct node* base;        //队列尾指针
    int length;               //队列长度
protected:

};


#endif // QUEUE_H_INCLUDED
