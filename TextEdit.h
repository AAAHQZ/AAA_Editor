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

        void GetMsg(eMSG message);      //��ӿڣ��õ���Ϣ

    private:

        COORD nowpos,fpos;//����λ��,����ԭλ��

        int strlength; //�����ַ�������
        int o_name; //������Ӧ��
        int pos;//������ʼλ��

        char from[strlimit];//�ַ���ƥ���е�Դ�ַ���������������Ҫ�洢�ַ���ʱʹ��
        char to[strlimit];//�ַ���ƥ���е�Ŀ���ַ���
        char ch;//�������ʹ��

        EditData* nowdata;//������ָ��
        RepealStack* nowstack;//ջָ�루������
        Queue* nowqueue;//�滻����ָ��


    private:

        TextEdit(TextEdit &TE);

        void DataInsert();//���뺯��
        void DataDelete();//ɾ��
        void LookupStr();//����
        bool ExchangeStr();//�ַ����滻
        //bool DataCopy();//����
        void DataPaste();//ճ��
        bool OperRevoke();//��������

        void AssignMsg(eMSG message);//save information
        void PosChange(COORD&, int);//deal with change of position

        //bool AsyCmp(char, int);

};


#endif // TEXTEDIT_H_INCLUDED
