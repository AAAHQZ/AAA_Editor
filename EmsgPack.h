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
    void PaddIn(EditData *pd,FileOper *fo,TextEdit *te,ConDisplay *cd,Queue *pq); //���ģ���ַ
    void InputFromKey();        //�Ӽ��̶�ȡ����ģ����������
    EmsgQueuePack();            //����
    //~EmsgQueuePack();           //����
    eMSG pa_message;        //����е���Ϣ�洢
private:
    EmsgQueuePack(EmsgQueuePack &EQ);//��������
    Queue *pqu;             //���е�ַ
    EditData *pdate;        //���Ա��ַ
    FileOper *pfo;          //�ļ�ģ���ַ
    TextEdit *pte;           //�ı�ģ���ַ
    ConDisplay *pcd;        //��ʾģ���ַ
    int flagbe;             //��ǰ״̬
    char oprstr[strlimit];  //�����ָ���ַ���
    char oprname[opr_mount][opr_mount+2];//�洢��ָ���ַ���
    int CharIn();           //��ȡ�ַ��������ַ�����
    int OprStrIn();         //��ȡ�ַ���
    int StrIn(int jud);     //������������ַ���
    int StrJudge();         //�жϲ���Ҫ��
    void PackEmsg();        //���������Ϣ
    void PosIn();           //��ȡ���λ��
    COORD PosSet();         //�������λ�ò���ȡ
    void FindDest(int flag,int ldif);//�����滻�ҵ�Ŀ��
    void CpySet();           //���ƹ����л�ȡ���λ��
    void EmptyOpr();        //���ָ����
protected:

};

#endif // EMSGPACK_H_INCLUDED
