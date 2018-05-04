//@file queue.h
//@brief ʵ��һ���洢ָ��Ķ���
//@author wc
//@version 1.0
//@data 2018/3/12


#include "queue.h"


Queue :: Queue(){top = (struct node*)malloc(sizeof(struct node));base = top;top -> next = NULL;length = 0;}//top��baseָ���ͷ


Queue :: Queue(Queue &q)
{
    struct node* newnode;//ԭ��ı��ָ��
    struct node* newnext;//�±�����ָ��
    struct node* newtop;//�±�ı��ָ��
    newtop = top;
    newnode = q.top;
    length = q.length;
    while(newnode -> next != NULL)
    {
        newnext = (struct node*)malloc(sizeof(struct node));
        newtop->next = newnext;
        newnext->pos = newnode->pos;
        newnode = newnode->next;
        newtop = newnext;
    }
    newtop->next = NULL;
    base = newtop;
}


Queue :: ~Queue()
{
    struct node *mid;
    while(top != NULL)
    {
        mid = top->next;
        delete top;
        top = mid;
    }
}


void Queue :: push(COORD newpos)
{
    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    base -> next = newnode;
    base = newnode;
    base -> pos = newpos;
    base -> next = NULL;
    length++;
}


bool Queue :: pop(COORD& oldpos)
{
    if(top == base) return 0;
    struct node* newnode;
    newnode = top;
    top = top -> next;
    delete newnode;
    oldpos = top -> pos;
    length--;
    return 1;
}

int Queue :: getlength()
{
    return length;
}

void Queue :: EmptyQue()
{
    struct node *mid;
    while(top != base)
    {
        mid = top->next;
        delete top;
        top = mid;
    }
}
