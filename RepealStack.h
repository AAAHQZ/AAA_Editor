#ifndef REPEALSTACK_H_INCLUDED
#define REPEALSTACK_H_INCLUDED
//本类为数据结构栈，用于保存操作历史
//容量默认为10个元素T，溢出时自动覆盖
#include "MSG.h"

class RepealStack
{
public:
       RepealStack();
       ~RepealStack();
public:
        void push(eMSG);
        bool pop(eMSG &);  //出栈，通过引用返回元素，返回值为false代表，打印栈空，返回失败
                        //返回true时代表成功返回
private:
        int NowSize;
        int MaxSize;
        int top;        //栈顶下一个元素位置
        eMSG* base;        //栈空间的首地址
};


#endif // REPEALSTACK_H_INCLUDED
