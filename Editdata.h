#ifndef EDITDATA_H
#define EDITDATA_H


#include <string.h>
#include <windows.h>
#include "config.h"


class EditData
{
public:
    EditData();
    ~EditData();
public://文件操作
    int GetLength() const;
    void GetElem(int index, char & wc);
    bool InsElem(int index, const char wc);
    bool DelElem(int index);
public://文本编辑
    COORD InsertE(COORD nowpos, const char wc);//@brief 插入字符，xy增加?
    COORD DeleteE(COORD nowpos);//@brief 删除字符，xy减少?
    void GetE(COORD nowpos, char & wc);//@brief 获得xy处字符
    void UpdataPos(COORD newpos);
    void UpdataPage(int newpage);
    int GetL();
public://界面显示
    int GetP();
    COORD GetPos();
private://封装函数
    void Refresh();//@brief 记录len
    bool AutoChangeSize();//@brief 自动改变线性表大小
    void MoveTo(int index, int num);//@brief 移动数据
    void MoveBack(int index, int num);//@brief 移动数据
    void ChangePos(COORD newpos);//@brief 提供修改xy的功能
    void UpdataI();
    void MovePos(bool flag);
private:
    bool ChangeSize(int newSize);

private:
    COORD pos;
    char *data;
    int maxSize;
    int len;
    int i;
    int dislen,dishigh;
    int page;
};

#endif // EDITDATA_H
