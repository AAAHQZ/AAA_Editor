#include "Editdata.h"

EditData::EditData()
{
    //ctor
    i = 0;
    len = 0;
    page = 0;
    pos = {1,1};
    maxSize = DEFAULTSIZE;
    dislen = DEFSIZEX - 2;
    dishigh = DEFSIZEY - 3 - 2;
    data = new char [maxSize];
    for(int i = 0; i < maxSize; i++)
    {
        *(data+i) = '\0';
    }
}

EditData::~EditData()
{
    //dtor
    delete [] data;
}

//-----------------------------------------------------------------------
//文件操作
//-----------------------------------------------------------------------
int EditData::GetLength() const
{
    return maxSize;
}

void EditData::GetElem(int index, char & wc)
{
    wc = *(data+index);
}

bool EditData::InsElem(int index, const char  wc)
{
    AutoChangeSize();
    if(index >= 0 && index < maxSize)
    {
        *(data+index) = wc;
        return true;
    }
    else
    {
        return false;
    }
}

bool EditData::DelElem(int index)
{
    if(index >= 0 && index < maxSize)
    {
        *(data+index) = '\0';
        return true;
    }
    else
    {
        return false;
    }
}



//-----------------------------------------------------------------------
//文本编辑
//-----------------------------------------------------------------------
COORD EditData::InsertE(COORD nowpos, const char wc)
{
    this->ChangePos(nowpos);
    this->UpdataI();
    this->AutoChangeSize();
    this->MoveBack(i,1);
    this->InsElem(i, wc);
    this->MovePos(true);
    return pos;
}

COORD EditData::DeleteE(COORD nowpos)//todo
{
    this->ChangePos(nowpos);
    this->UpdataI();
    this->AutoChangeSize();
    this->DelElem(i);
    this->MoveTo(i,1);
   // this->MovePos(false);
    return pos;
}

void EditData::GetE(COORD nowpos, char &wc)
{
    this->ChangePos(nowpos);
    this->UpdataI();
    this->GetElem(i,wc);
}

int EditData::GetL()
{
    Refresh();
    return len;
}


void EditData::UpdataPos(COORD newpos)
{
    this->ChangePos(newpos);
}

void EditData::UpdataPage(int newpage)
{
    page = newpage;
}
//----------------------------------------
//界面显示
//----------------------------------------
COORD EditData::GetPos()
{
    return pos;
}

int EditData::GetP()
{
    return page;
}

//----------------------------------------
//封装函数
//----------------------------------------
void EditData::Refresh()
{
    int n,m,k;
    for(n = 0;n < maxSize;n++)
    {
        if(*(data+n) == '\0')
            break;
    }
    len = n+1;
    for(n = 0;n < maxSize;n++)
    {
        if(*(data+n) == '\n')
        {
            k = n%(dislen);
            this->MoveBack(n+1,dislen-k-1);

            for(m = k+1;m < (dislen-2);m++)
            {
                this->InsElem(n+m-k,' ');
            }
        }
    }
}

bool EditData::AutoChangeSize()//
{
    if((page+1)*DEFAULTSIZE > (maxSize/2))
        return this->ChangeSize(maxSize*2);
    return true;

}

void EditData::MoveTo(int index, int num)//需要测试
{
    int order = 0;
    char wc,sym = '\0';
    //if((index+order+num) > len-1) return;
    while ((index+order+num) < maxSize)
    {
        this->GetElem(index+order+num,wc);
        this->InsElem((index+order), wc);
        order++;
    }
    while((index+order) < maxSize)
    {
        this->InsElem((index+order),sym);
        order++;
    }
    len = len - num;
    this->Refresh();
    return;

}

void EditData::MoveBack(int index, int num)//需要测试//BUG
{
    //todo
    int order = 0;
    char wc,sym = ' ';
    while ((index+order) <= maxSize-num )
    {
        this->GetElem(maxSize-num-order,wc);
        this->InsElem(maxSize-order,wc);
        order++;
    }
     while((index+order) < len)
    {
        this->InsElem((index+order),sym);
        order++;
        order++;
        order++;
    }
    len = len + num;
    return;
}

void EditData::ChangePos(COORD newpos)//@brief 提供修改xy的功能//条件
{
    pos = newpos;
    if(pos.X == 0)
    {
        if(pos.Y == 1)
        {
            if(page == 0)
            {
                pos.X = 1;
            }
            else
            {
                pos.X = dislen;
                pos.Y = dishigh;
                page--;
            }
        }
        else
        {
            pos.X = dislen;
            pos.Y--;
        }
    }


    if(pos.Y == 0)
    {
        if(page == 0)
        {
            pos.Y = 1;
        }
        else
        {
            pos.Y = dishigh;
            page--;
        }
    }

    if(pos.X == dislen + 1)
    {
        pos.X = 1;
        pos.Y++;
        if(pos.Y == dishigh + 1)
        {
            pos.Y = 1;
            page++;
            this->AutoChangeSize();
        }
    }
    if(pos.Y == dishigh + 1)
    {
        pos.Y = 1;
        page++;
        this->AutoChangeSize();
    }

}

void EditData::UpdataI()
{
    //todo
    i = (pos.X-1)+(pos.Y-1)*(dislen)+page*DEFAULTSIZE;
}

void EditData::MovePos(bool flag)
{
    if(flag)
    {
        pos.X++;
        if(pos.X == dislen + 1)
        {
            pos.X = 1;
            pos.Y++;
            if(pos.Y == dishigh + 2)
            {
                pos.Y = 1;
                page++;
                this->AutoChangeSize();
            }
        }
    }
    else
    {
        pos.X--;
        if(pos.X == 0)
        {
            if(page == 0)
            {
                pos.X = 1;
            }
            else
            {
                pos.X == dislen + 1;
                pos.Y--;
                if(pos.Y == 0)
                {
                    pos.Y = dislen + 1;
                    page--;
                }
            }

        }
    }
}



//----------------------------------------
//资源分配
//----------------------------------------
bool EditData::ChangeSize(int newSize)
{
    char *temp;
    temp = new char [newSize];
    if(temp == NULL)
    {
        return false;
    }
    memcpy(temp, data, maxSize);
    delete [] data;
    data = temp;
    maxSize = newSize;
    return true;
}

