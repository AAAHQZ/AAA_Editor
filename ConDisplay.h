#ifndef CONDISPLAY_H
#define CONDISPLAY_H

#include <windows.h>
#include "MSG.h"
#include "Editdata.h"

#include "config.h"



class ConDisplay
{
public:
    ConDisplay();
    ~ConDisplay();
    void GetpED(EditData * p);
    void GetMsg(eMSG msg);
    void Display();
    void Display1();

    void Test();
private:
    void DisplayInterface();
    void DisplayData();
    void DisplayPage();
    void DisplayCursor();
    void DisplayResetCursor();
private:
    void DrawBox(COORD prc, COORD drc, WORD color);
    void DrawFrame(COORD prc, COORD drc);
    void DrawData(COORD now, WORD color,char dt);
private:
    bool sw;//命令模式与编辑模式开关
    EditData * pED;
    HANDLE hOut;
    COORD pos;
    COORD size;
    SMALL_RECT rc;
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    DWORD written;
};

#endif // CONDISPLAY_H
