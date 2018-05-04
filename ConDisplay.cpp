#include "ConDisplay.h"


ConDisplay::ConDisplay()
{
    //ctor
    sw = false;
    hOut =  GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hOut, &bInfo);
    SetConsoleTitle("EDITORv1.0");
    size.X = DEFSIZEX;
    size.Y = DEFSIZEY;
    SetConsoleScreenBufferSize(hOut, size);
    rc = {0, 0, size.X-1,size.Y-1};
    SetConsoleWindowInfo(hOut, true, &rc);
}

ConDisplay::~ConDisplay()
{
    //dtor
    CloseHandle(hOut);
}

void ConDisplay::Display()
{
    this->DisplayInterface();
    this->DisplayPage();
    this->DisplayData();
    if(sw == false)
        this->DisplayCursor();
}

void ConDisplay::Display1()
{
    this->DisplayPage();
    this->DisplayData();
    if(sw == false)
        this->DisplayCursor();
}
//-------------------------------------------------------------------
//界面显示
//-------------------------------------------------------------------
void ConDisplay::GetpED(EditData *p)
{
    pED = p;
}

void ConDisplay::GetMsg(eMSG msg)
{
    COORD p;
    WORD color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY ;
    if(sw == false)
    {
        p.X = 1;
        p.Y = DEFSIZEY - 2;
        sw = true;
        SetConsoleCursorPosition(hOut,p);
    }
    else
    {
        p.X = 1;
        p.Y = DEFSIZEY - 2;
        for(;p.X < DEFSIZEX-2;p.X++)
        {
            DrawData(p,color,'\0');
        }
        p = pED->GetPos();
        sw = false;
        SetConsoleCursorPosition(hOut,p);
    }
}

void ConDisplay::DisplayInterface()
{
    COORD p,d;
    char ch;
    WORD color;
    color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE;// 文本属性
    p.X = 0;
    p.Y = 0;
    d.X = DEFSIZEX;
    d.Y = DEFSIZEY-3;
    DrawBox(p,d,color);
    DrawFrame(p,d);
    color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;// 文本属性
    p.Y = p.Y + d.Y;
    d.Y = 3;
    DrawBox(p,d,color);
    DrawFrame(p,d);
    color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY ;
    d.X = d.X - 2;
    d.Y = 1;
    p.X++;
    p.Y++;
    DrawBox(p,d,color);
}

void ConDisplay::DisplayPage()
{
    COORD p;
    int num,n;
    char ch[3];
    WORD color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
    p.X = DEFSIZEX - 10;
    p.Y = DEFSIZEY-  4;
    DrawData(p,color,'P');
    p.X++;
    DrawData(p,color,':');

    num = pED->GetP();
    if(num/100 != 0)
    {
        ch[0] = '0'+num%1000;
    }
    else
    {
        ch[0] = '0';
    }
    if(num/10 != 0)
    {
        ch[1] = '0'+num%100;
    }
    else
    {
        ch[1] = '0';
    }
    if(num/1 != 0)
    {
        ch[2] = '0'+num%10;
    }
    else
    {
        ch[2] = '0';
    }
    for(n=0;n<3;n++)
    {
        p.X++;
        DrawData(p,color,ch[n]);
    }

}

void ConDisplay::DisplayData()
{
    char ch;
    COORD p;
    p.X = 1;
    p.Y = 1;
    WORD color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
    for(int i=0;i<DEFAULTSIZE;i++)
    {
        pED->GetElem(i+pED->GetP()*DEFAULTSIZE,ch);
        DrawData(p,color,ch);
        p.X++;
        if(p.X == DEFSIZEX-1)
        {
            p.X = 1;
            p.Y++;
        }
    }
}

void ConDisplay::Test()
{
    COORD p,d;
    char ch;
    WORD color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE;// 文本属性
    p.X = 0;
    p.Y = 0;
    d.X = DEFSIZEX;
    d.Y = DEFSIZEY-3;
    DrawBox(p,d,color);
    DrawFrame(p,d);
    p.Y = p.Y + d.Y;
    d.Y = 3;
    color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY ;// 文本属性
    DrawBox(p,d,color);
    DrawFrame(p,d);
    p.X = DEFSIZEX - 10;
    p.Y = DEFSIZEY-  4;
    DrawData(p,color,'P');
    p.X++;
    DrawData(p,color,':');
    p.X++;
    DrawData(p,color,'0'+pED->GetP());
    p.X = 1;
    p.Y = 1;
    color = FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
    for(int i=0;i<pED->GetLength();i++)
    {
        pED->GetElem(i,ch);
        DrawData(p,color,ch);
        p.X++;
        if(p.X == DEFSIZEX-1)
        {
            p.X = 1;
            p.Y++;
        }
    }

}


//-------------------------------------------------------------------
//封装函数
//-------------------------------------------------------------------
void ConDisplay::DrawBox(COORD prc, COORD drc, WORD color)
{
    for (int i=0;i<drc.Y;i++)
	{
		FillConsoleOutputAttribute(hOut, color, drc.X, prc, &written);
		prc.Y++;
	}
}

void ConDisplay::DrawFrame(COORD prc, COORD drc)
{
    char corner = '+';
    char xedge = '-';
    char yedge = '|';
    COORD now = prc;
    for(int i=1;i < drc.X;i++)
    {
        now = prc;
        now.X = prc.X+i;
        WriteConsoleOutputCharacter(hOut, &xedge, 1, now, &written);
        now.Y = prc.Y+drc.Y-1;
        WriteConsoleOutputCharacter(hOut, &xedge, 1, now, &written);
    }
    for(int i=1;i < drc.Y;i++)
    {
        now = prc;
        now.Y = prc.Y+i;
        WriteConsoleOutputCharacter(hOut, &yedge, 1, now, &written);
        now.X = prc.X+drc.X-1;
        WriteConsoleOutputCharacter(hOut, &yedge, 1, now, &written);
    }
    now = prc;
    WriteConsoleOutputCharacter(hOut, &corner, 1, now, &written);
    now.X = prc.X + drc.X-1;
    WriteConsoleOutputCharacter(hOut, &corner, 1, now, &written);
    now.Y = prc.Y + drc.Y-1;
    WriteConsoleOutputCharacter(hOut, &corner, 1, now, &written);
    now.X = prc.X;
    WriteConsoleOutputCharacter(hOut, &corner, 1, now, &written);
}

void ConDisplay::DrawData(COORD now, WORD color,char dt)
{
    WriteConsoleOutputCharacter(hOut, &dt, 1, now, &written);
}

void ConDisplay::DisplayResetCursor()
{
    SetConsoleCursorPosition(hOut,{1,1});
}

void ConDisplay::DisplayCursor()
{
    SetConsoleCursorPosition(hOut,pED->GetPos());
}
