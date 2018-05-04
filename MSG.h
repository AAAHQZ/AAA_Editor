//@file MSG.h
//@brief 包含用于模块间通信的MSG结构体及相关的宏定义
//@author AAA
//@version 1.0
//@date 2018/3/10

#ifndef MSG_H_INCLUDED
#define MSG_H_INCLUDED

#include "Editdata.h"

#define MAXEXTRA 40

#define _File_Operation 0
#define _Text_Editor 1
#define _Interface_Display 2


typedef struct eMSG
{
    EditData* pDATA;//@todo 可能需要修改
    int m_name;
    int o_name;
    char Extra1[MAXEXTRA];
    char Extra2[MAXEXTRA];
    int page;
    COORD pos;//光标所在坐标
    int strlength;
}EMSG,*pEMSG;

#endif // MSG_H_INCLUDED
