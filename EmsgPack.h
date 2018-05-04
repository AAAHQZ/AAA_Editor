#ifndef EMSGPACK_H_INCLUDED
#define EMSGPACK_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <string>
#include "queue.h"
#include "O_name.h"
#include "ConDisplay.h"
#include "Editdata.h"
#include "FileOper.h"
#include "TextEdit.h"
#include "MSG.h"
#define bu_char 1
#define bu_ESC 27
#define bu_back 3
#define bu_up 4
#define bu_down 5
#define bu_left 6
#define bu_right 7
#define bu_yes 13
#define opr_mount 10
#define FILEOPR 1
#define TXTEDIT 2
#define DISPLAY 3
using namespace std;
class EmsgQueuePack
{
public:
    void PaddIn(EditData *pd,FileOper *fo,TextEdit *te,ConDisplay *cd,Queue *pq); //获得模块地址
    void InputFromKey();        //从键盘读取（该模块主函数）
    EmsgQueuePack();            //构造
    //~EmsgQueuePack();           //析构
    eMSG pa_message;        //打包中的信息存储
private:
    EmsgQueuePack(EmsgQueuePack &EQ);//拷贝构造
    Queue *pqu;             //队列地址
    EditData *pdate;        //线性表地址
    FileOper *pfo;          //文件模块地址
    TextEdit *pte;           //文本模块地址
    ConDisplay *pcd;        //显示模块地址
    int flagbe;             //当前状态
    char oprstr[strlimit];  //输入的指令字符串
    char oprname[opr_mount][opr_mount+2];//存储的指令字符串
    int CharIn();           //读取字符，返回字符类型
    int OprStrIn();         //读取字符串
    int StrIn(int jud);     //读入待操作的字符串
    int StrJudge();         //判断操作要求
    void PackEmsg();        //打包传递消息
    void PosIn();           //获取光标位置
    COORD PosSet();         //调整光标位置并获取
    void FindDest(int flag,int ldif);//查找替换找到目标
    void CpySet();           //复制功能中获取光标位置
    void EmptyOpr();        //清除指令行
protected:

};

#endif // EMSGPACK_H_INCLUDED
