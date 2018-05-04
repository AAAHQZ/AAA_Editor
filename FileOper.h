//@file FileOper.h
//@brief
//@author 钟明涵
//@version
//@data 2018/3/19

#ifndef FILEOPER_H_INCLUDED
#define FILEOPER_H_INCLUDED

#include <fstream>
#include "MSG.h"
#include "O_name.h"
#include "Editdata.h"

class FileOper
{
private:

    std::fstream NowFile;//打开文件
    //std::ofstream NewFile;
    eMSG NowMsg;//

public:

    void GetMsg(eMSG);//接口
    FileOper();//初始化
    ~FileOper();//关文件

private:

    char FileName[MAXEXTRA];
    void CreatFile();//创建文件，NowMsg,ptr
    void OpenFile();//打开文件
    void CloseFile();//to do
    void SaveFile();//pdata,ptr
    void Saveas();//save as
};

#endif // FILEOPER_H_INCLUDED
