#ifndef TEXTEDIT_H_INCLUDED
#define TEXTEDIT_H_INCLUDED

#include<iostream>
#include<cstring>

#include "windows.h"
#include "MSG.h"
#include "O_name.h"
#include "Editdata.h"
#include "RepealStack.h"
#include "Queue.h"

class TextEdit
{
    public:

        TextEdit(RepealStack*,Queue*);
        ~TextEdit();

        void GetMsg(eMSG message);      //类接口，得到信息

    private:

        COORD nowpos,fpos;//坐标位置,复制原位置

        int strlength; //复制字符串长度
        int o_name; //操作对应名
        int pos;//查找起始位置

        char from[strlimit];//字符串匹配中的源字符串，或者其他需要存储字符串时使用
        char to[strlimit];//字符串匹配中的目的字符串
        char ch;//插入操作使用

        EditData* nowdata;//数据类指针
        RepealStack* nowstack;//栈指针（撤销）
        Queue* nowqueue;//替换队列指针


    private:

        TextEdit(TextEdit &TE);

        void DataInsert();//插入函数
        void DataDelete();//删除
        void LookupStr();//查找
        bool ExchangeStr();//字符串替换
        //bool DataCopy();//复制
        void DataPaste();//粘贴
        bool OperRevoke();//撤销操作

        void AssignMsg(eMSG message);//save information
        void PosChange(COORD&, int);//deal with change of position

        //bool AsyCmp(char, int);

};


#endif // TEXTEDIT_H_INCLUDED
