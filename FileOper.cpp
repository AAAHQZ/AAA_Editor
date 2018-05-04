#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include <math.h>
#include "FileOper.h"


FileOper::FileOper()
{
}

FileOper::~FileOper()
{
    NowFile.close();
    //NewFile.close();
}

void FileOper::GetMsg(eMSG mes)
{
    NowMsg = mes;
    switch(mes.o_name)
    {
        case file_creat://11
            CreatFile();
            break;
        case file_open://9
            OpenFile();
            break;
        case file_close://file_close:
            CloseFile();
            break;
        case file_save://10
            SaveFile();
            break;
        case file_saveas://file_saveas:
            Saveas();
            break;
        default :
            break;
    }
}

void FileOper::CreatFile()
{
    strcpy(FileName,NowMsg.Extra1);
    NowFile.open(FileName,std::ios::out);
}

void FileOper::OpenFile()
{
    int i = 0;
    char ch;
    strcpy(FileName,NowMsg.Extra1);
    NowFile.open(FileName,std::ios::in);//
    while(NowFile.peek() != EOF)
    {
        NowFile.get(ch);
        if(ch == '\n')
        {
                ch = '\r';
                (*(NowMsg.pDATA)).InsElem(i,ch);
                i = (i/linenum + 1) * linenum - 1;
        }
        else
        {
                (*(NowMsg.pDATA)).InsElem(i,ch);
        }
        i ++;
    }

    //error deal
}

void FileOper::CloseFile()
{
        int i;
        NowFile.close();
        for(i = 0; i < (*(NowMsg.pDATA)).GetLength(); i ++)//
        {
                (*(NowMsg.pDATA)).DeleteE({1,1});
        }
    // to do
}

void FileOper::SaveFile()
{
    int i;
    char ch; //hong
    NowFile.close();
    NowFile.open(FileName,std::ios::out);
    NowFile.seekp(0L,std::ios::beg);
    int nn =(*(NowMsg.pDATA)).GetLength();
    for(i = 0; i < nn; i++)
    {
        (*(NowMsg.pDATA)).GetElem(i,ch);
        if(ch == '\r')
        {
            ch = '\n';
            i = (i/linenum + 1)*linenum - 2;
        }
        NowFile.put(ch);
    }

}

void FileOper::Saveas()
{
    int i;
    char ch;
    std::fstream NewFile;

    strcpy(FileName,NowMsg.Extra1);
    NewFile.open(FileName,std::ios::out);
    for(i = 0; i < (*(NowMsg.pDATA)).GetLength() ; i ++)
    {
        (*(NowMsg.pDATA)).GetElem(i,ch);
        if(ch == '\r')
        {
            ch = '\n';
            i = (i/linenum + 1)*linenum - 2;
        }
        NewFile.put(ch);
    }
}
