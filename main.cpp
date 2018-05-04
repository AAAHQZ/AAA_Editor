#include <iostream>
#include<pthread.h>
#include<windows.h>
#include "Editdata.h"
#include "FileOper.h"
#include "TextEdit.h"
#include "MSG.h"
#include "ConDisplay.h"
#include "EmsgPack.h"


using namespace std;
ConDisplay CD;
void *Display(void * arg)
{
    while(1)
    {
        CD.Display1();
        Sleep(80);
    }
}

int main(int argc,char* argv[])
{

    EditData data;
    FileOper fo;
    Queue a;
    RepealStack b;
    TextEdit te(&b,&a);
    EmsgQueuePack eqp;
    eMSG msg1,msg2,msg3;
    msg1.pDATA = &data;
    eqp.PaddIn(&data,&fo,&te,&CD,&a);
    CD.GetpED(&data); //CD.Display();

    pthread_t dis;
    pthread_create(&dis,NULL,Display,&CD);

    CD.Display();
    msg1.o_name = file_open;
    msg1.m_name = TXTEDIT;
    strcpy(msg1.Extra1,"help.txt");
    fo.GetMsg(msg1);
    CD.GetMsg(msg1);
    while(1)
    {
        eqp.InputFromKey();
        Sleep(150);
    }

    return 1;

}

