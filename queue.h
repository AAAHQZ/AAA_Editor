//@file queue.h
//@brief ʵ��һ���洢ָ��Ķ���
//@author wc
//@version 1.0
//@data 2018/3/12


#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdlib.h>
#include <windows.h>
#include "MSG.h"


struct node                   //������нڵ�ṹ��
{
    COORD pos;
    struct node *next;
};

class Queue
{
public:
    Queue();                  //���캯��
    Queue(Queue &q);          //�������캯��
    ~Queue();                 //��������
    void push(COORD pos);   //�����
    bool pop(COORD &pos);    //������
    int getlength();
    void EmptyQue();
private:
    struct node* top;         //����ͷָ��
    struct node* base;        //����βָ��
    int length;               //���г���
protected:

};


#endif // QUEUE_H_INCLUDED
