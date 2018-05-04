//@file FileOper.h
//@brief
//@author ������
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

    std::fstream NowFile;//���ļ�
    //std::ofstream NewFile;
    eMSG NowMsg;//

public:

    void GetMsg(eMSG);//�ӿ�
    FileOper();//��ʼ��
    ~FileOper();//���ļ�

private:

    char FileName[MAXEXTRA];
    void CreatFile();//�����ļ���NowMsg,ptr
    void OpenFile();//���ļ�
    void CloseFile();//to do
    void SaveFile();//pdata,ptr
    void Saveas();//save as
};

#endif // FILEOPER_H_INCLUDED
