#include "EmsgPack.h"


EmsgQueuePack :: EmsgQueuePack()
{
    flagbe = 1;
    pqu = NULL;
    pfo = NULL;
    pcd = NULL;
    pte = NULL;
    pa_message.pDATA = NULL;
    pa_message.strlength = 0;
    pa_message.pos.X = pa_message.pos.Y = 0;
    pa_message.Extra1[0] = '\0';
    pa_message.Extra2[0] = '\0';
    pa_message.o_name = 0;
    pa_message.m_name = pa_message.o_name = 0;
    strcpy(oprname[0],"lookup");
    strcpy(oprname[1],"exchange");
    strcpy(oprname[2],"copy");
    strcpy(oprname[3],"paste");
    strcpy(oprname[4],"revoke");
    strcpy(oprname[5],"open");
    strcpy(oprname[6],"save");
    strcpy(oprname[7],"create");
    strcpy(oprname[8],"close");
    strcpy(oprname[9],"saveas");
}


void EmsgQueuePack :: InputFromKey()
{
    int ldif = 0,ldel = 0,lint = 0;
    if(flagbe)                      //开始创建文件阶段
    {
        OprStrIn();
        pa_message.o_name = StrJudge();
        while(pa_message.o_name != file_open && pa_message.o_name != file_creat)//只有输入创建和打开才执行操作
        {
            EmptyOpr();
            pa_message.o_name = OprStrIn();
        }
        flagbe = pa_message.o_name;
        EmptyOpr();
        StrIn(data_lou);
        pa_message.o_name = file_close;
        pa_message.m_name = FILEOPR;
        PackEmsg();
        pa_message.o_name = flagbe;
        pa_message.m_name = FILEOPR;
        PackEmsg();
        pa_message.o_name = opr_switch;
        pa_message.m_name = DISPLAY;
        PackEmsg();
        flagbe = 0;
    }
    switch(CharIn())                    //对读入的字符进行判断
    {
    case bu_char :
        pa_message.o_name = data_ins;
        pa_message.m_name = TXTEDIT;
        PosIn();
        PackEmsg();
        break;
    case bu_back :
        pa_message.o_name = data_del;
        pa_message.m_name = TXTEDIT;
        PosIn();
        PackEmsg();
        break;
    case bu_ESC :
        pa_message.o_name = opr_switch;
        pa_message.m_name = DISPLAY;
        PackEmsg();
        OprStrIn();
        pa_message.o_name = StrJudge();
        //printf("%d",pa_message.o_name);//测试用
        //printf("%d\n",pa_message.o_name);//测试用
        switch(pa_message.o_name)       //选择功能，对读入的功能进行判断
        {
        case data_lou :
            EmptyOpr();
            pa_message.o_name = data_lou;
            pa_message.m_name = TXTEDIT;
            StrIn(data_lou);
            PackEmsg();
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            FindDest(data_lou,0);
            break;
        case data_exc :
            EmptyOpr();
            ldel = StrIn(data_lou);
            EmptyOpr();
            lint = StrIn(data_exc);
            ldif = ldel - lint;
            pa_message.o_name = data_lou;
            pa_message.m_name = TXTEDIT;
            PackEmsg();
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            strcpy(oprstr,pa_message.Extra1);
            FindDest(data_exc,ldif);
            break;
        case data_cpy :
            CpySet();
            pa_message.o_name = data_cpy;
            pa_message.m_name = TXTEDIT;
            PackEmsg();
            break;
        case data_pst :
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            pa_message.o_name = data_pst;
            pa_message.m_name = TXTEDIT;
            PosIn();
            PackEmsg();
            break;
        case opr_rvk :
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            pa_message.o_name = opr_rvk;
            pa_message.m_name = TXTEDIT;
            PackEmsg();
            break;
        case file_open :
            EmptyOpr();
            pa_message.o_name = file_close;
            pa_message.m_name = FILEOPR;
            PackEmsg();
            pa_message.m_name = FILEOPR;
            pa_message.o_name = file_open;
            StrIn(data_lou);
            PackEmsg();
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            break;
        case file_save :
            pa_message.m_name = FILEOPR;
            PackEmsg();
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            break;
        case file_creat :
            EmptyOpr();
            pa_message.o_name = file_close;
            pa_message.m_name = FILEOPR;
            PackEmsg();
            StrIn(data_lou);
            pa_message.m_name = FILEOPR;
            pa_message.o_name = file_creat;
            PackEmsg();
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            break;
        case file_close :
            pa_message.m_name = FILEOPR;
            pa_message.o_name = file_close;
            PackEmsg();
            EmptyOpr();
            flagbe = 1;
            break;
        case file_saveas:
            EmptyOpr();
            pa_message.o_name = file_saveas;
            pa_message.m_name = FILEOPR;
            StrIn(data_lou);
            PackEmsg();
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            break;
        default:
            pa_message.o_name = opr_switch;
            pa_message.m_name = DISPLAY;
            PackEmsg();
            break;
        }
        break;
    case bu_up :
        PosIn();
        pa_message.o_name =  pos_mov;
        pa_message.m_name = TXTEDIT;
        pa_message.pos.Y = pa_message.pos.Y-1;
        PackEmsg();
        break;
    case bu_down :
        PosIn();
        pa_message.o_name =  pos_mov;
        pa_message.m_name = TXTEDIT;
        pa_message.pos.Y = pa_message.pos.Y+1;
        PackEmsg();
        break;
    case bu_left :
        PosIn();
        pa_message.o_name =  pos_mov;
        pa_message.m_name = TXTEDIT;
        pa_message.pos.X = pa_message.pos.X-1;
        PackEmsg();
        break;
    case bu_right :
        PosIn();
        pa_message.o_name =  pos_mov;
        pa_message.m_name = TXTEDIT;
        pa_message.pos.X = pa_message.pos.X+1;
        PackEmsg();
        break;
    case bu_yes :
        //printf("77777777\n");//测试用
        pa_message.Extra1[0] = '\r';
        pa_message.o_name = data_ins;
        pa_message.m_name = TXTEDIT;
        PosIn();
        PackEmsg();
        pa_message.o_name = pos_mov;
        pa_message.m_name = TXTEDIT;
        PosIn();
        pa_message.pos.X = 1;
        pa_message.pos.Y = pa_message.pos.Y+1;
        PackEmsg();
        break;
    default:
        break;
    }
}


EmsgQueuePack :: EmsgQueuePack(EmsgQueuePack &EQ)
{

}


int EmsgQueuePack :: CharIn()
{
    HANDLE hIn;
    INPUT_RECORD keyRec;
    DWORD res;
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    while(1)
    {
        ReadConsoleInput(hIn, &keyRec, 1, &res);
        if(keyRec.Event.KeyEvent.bKeyDown)     //按键按下过程中记录所按按键
        {
            pa_message.Extra1[0] = keyRec.Event.KeyEvent.uChar.AsciiChar;
            pa_message.Extra1[1] = '\0';
            if(keyRec.Event.KeyEvent.uChar.AsciiChar == NULL)
            {
                switch(keyRec.Event.KeyEvent.wVirtualKeyCode)//无ASCII码按键
                {
                case 37:
                    return bu_left;
                case 38:
                    return bu_up;
                case 39:
                    return bu_right;
                case 40:
                    return bu_down;
                default:
                    return 0;
                }
            }
            else
            {
                switch(keyRec.Event.KeyEvent.uChar.AsciiChar)//有ASCII码按键
                {
                case bu_ESC :
                    return bu_ESC;
                case '\t' :
                    return 0;
                case '\b' :
                    return bu_back;
                case bu_yes :
                    return bu_yes;
                default :
                    return bu_char;
                }
            }
            break;
        }
    }
}


int EmsgQueuePack :: StrIn(int jud)
{
    int i = 0;
    if(jud == data_lou)                     //非替换式字符串读入，只读一串
    {
        while(i < strlimit - 1)
        {
            pa_message.Extra1[i] = getchar();
            if(pa_message.Extra1[i] == '\n') break;
            i++;
        }
        pa_message.Extra1[i] = '\0';
    }
    else                                    //替换功能字符串读入，读两串
    {
        while(i < strlimit - 1)
        {
            pa_message.Extra2[i] = getchar();
            if(pa_message.Extra2[i] == '\n') break;
            i++;
        }
        pa_message.Extra2[i] = '\0';
    }
    fflush(stdin);
    return i;
}


void EmsgQueuePack :: PaddIn(EditData *pd,FileOper *fo,TextEdit *te,ConDisplay *cd,Queue *pq)//获得其他模块地址
{
    pa_message.pDATA = pd; pfo = fo; pte = te; pcd = cd; pqu = pq;
}


int EmsgQueuePack :: OprStrIn()
{
    int i = 0;

    while(i < strlimit-1)
    {
        oprstr[i] = getchar();
        if(oprstr[i] == '\n') break;
        i++;
    }

    oprstr[i] = '\0';
    fflush(stdin);
    return i;
}


int EmsgQueuePack :: StrJudge()
{
    int i = 0;

    while(i < opr_mount)
    {
        if(strcmp(oprstr,oprname[i]) == 0) return i+5;
        else i++;
    }

    return 0;
}


void EmsgQueuePack :: PackEmsg()
{
    switch(pa_message.m_name)
    {
    case FILEOPR:
        (*pfo).GetMsg(pa_message);
        break;
    case TXTEDIT:
        (*pte).GetMsg(pa_message);
        break;
    case DISPLAY:
        (*pcd).GetMsg(pa_message);
        break;
    default:
        break;
    }
    //printf("o_name %d\nm_name %d\nextra1 %s\nextra2 %s\nx,y %d,%d\nlength %d\n",pa_message.o_name,pa_message.m_name,pa_message.Extra1,pa_message.Extra2,pa_message.pos.X,pa_message.pos.Y,pa_message.strlength);
}


void EmsgQueuePack :: PosIn()
{
    HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hOut, &bInfo);
    pa_message.pos.X = bInfo.dwCursorPosition.X;
    pa_message.pos.Y = bInfo.dwCursorPosition.Y;
}


void EmsgQueuePack :: CpySet()
{
    COORD head;
    pa_message.o_name = opr_switch;
    pa_message.m_name = DISPLAY;
    PackEmsg();
    PosSet();
    head = pa_message.pos;
    //printf("7777777777777\n");//测试用
    PosSet();
    pa_message.strlength = fabs((pa_message.pos.Y - head.Y)*linenum + pa_message.pos.X - head.X) + 1;//计算复制长度
    if(pa_message.pos.Y > head.Y||(pa_message.pos.Y == head.Y)&&(pa_message.pos.X > head.X)) pa_message.pos = head;//判断起始光标位置
}


COORD EmsgQueuePack :: PosSet()
{
    //printf("%d\n",pa_message.o_name);//测试用
    pa_message.o_name = 0;
    while(pa_message.o_name != bu_yes)
    {
        //printf("%d\n",pa_message.o_name);//测试用
        pa_message.o_name = CharIn();
        /*printf("%d\n",pa_message.o_name);*/
        if(pa_message.o_name >= bu_up&&pa_message.o_name < bu_yes)
        {
            PosIn();
            switch(pa_message.o_name)
            {
            case bu_up :
                pa_message.pos.Y = pa_message.pos.Y-1;
                break;
            case bu_down :
                pa_message.pos.Y = pa_message.pos.Y+1;
                break;
            case bu_left :
                pa_message.pos.X = pa_message.pos.X-1;
                break;
            case bu_right :
                pa_message.pos.X = pa_message.pos.X+1;
                break;
            }
            pa_message.o_name = pos_mov;
            pa_message.m_name = TXTEDIT;
            PackEmsg();
        }
    }
    PosIn();
}


void EmsgQueuePack :: FindDest(int flag,int ldif)       //查找替换的输出显示
{
    int excount = 0;
    while((*pqu).pop(pa_message.pos))
    {
        int jud;
        pa_message.pos.X = pa_message.pos.X - excount * ldif;//替换后光标有所变化
        while(pa_message.pos.X < 1)
        {
            pa_message.pos.Y--;
            pa_message.pos.X = pa_message.pos.X + DEFSIZEX - 1;
        }
        pa_message.o_name = pos_mov;
        pa_message.m_name = TXTEDIT;
        PackEmsg();
        jud = CharIn();
        if(flag == data_lou)
        {
            while(jud != bu_right&&jud!=bu_ESC)
            {
                jud = CharIn();
            }
            if(jud == bu_ESC)
            {
                (*pqu).EmptyQue();
                break;
            }
        }
        else
        {
            while(jud != bu_right&&jud != bu_yes&&jud != bu_ESC)
            {
                jud = CharIn();
            }
            if(jud == bu_yes)
            {
                pa_message.o_name = data_exc;
                strcpy(pa_message.Extra1,oprstr);
                PackEmsg();
                excount++;
            }
            else if(jud == bu_ESC)
            {
                (*pqu).EmptyQue();
                break;
            }
        }
    }
}


void EmsgQueuePack :: EmptyOpr()
{
    pa_message.o_name = opr_switch;
    pa_message.m_name = DISPLAY;
    PackEmsg();
    pa_message.o_name = opr_switch;
    pa_message.m_name = DISPLAY;
    PackEmsg();
}
