
#include "TextEdit.h"

TextEdit :: TextEdit(RepealStack* ptr,Queue* pttr)
{
    nowpos = {0,0};
    fpos = {0,0};

    strlength = 0;
    o_name = 0;
    pos = 0;

    from[0] = '/0';
    to[0] = '/0';

    nowdata = NULL;
    nowstack = ptr;
    nowqueue = pttr;
}

TextEdit :: TextEdit(TextEdit &TE)
{
    //kaobeigouzao
}

TextEdit :: ~TextEdit()
{
    //kaobeigouzao
}

void TextEdit :: GetMsg(eMSG message)
{
    int page = 0;
    int c;
    AssignMsg(message);
    if(o_name != opr_rvk)
    {
        if( nowpos.Y > 20 )
        {
            c = nowpos.Y / 20;
            nowpos.Y = nowpos.Y % 20;
            message.pos.Y = nowpos.Y;
            (*nowdata).UpdataPage(c);
        }
        (*nowdata).UpdataPos(nowpos);
    }

    switch(o_name)
    {
        case data_ins:
            DataInsert();//插入函数
            break;

        case data_del:
            DataDelete();//删除
            message.Extra1[0] = ch;
            break;

        case data_lou:
            (*nowdata).UpdataPage(0);
            LookupStr();//查找
            return;
            break;

        case data_exc:
            ExchangeStr();//字符串替换
            break;

        case data_cpy://复制
            fpos = nowpos;
            strlength = message.strlength;
            return ;
            break;

        case data_pst:
            DataPaste();//粘贴
            break;

        case opr_rvk:
            OperRevoke();//撤销
            return ;
            break;

        case pos_mov:
            return ;
            break;

        default:
            return;
            break;

    }
    page = (*nowdata).GetP();
    message.page = page;
    (*nowstack).push(message);
}

void TextEdit :: AssignMsg(eMSG message)
{
    nowpos = message.pos;
    nowdata = message.pDATA;
    o_name = message.o_name;//保存信息
    strcpy(from + 1,message.Extra1);
    from[0] = strlen(message.Extra1);//保存长度
    strcpy(to,message.Extra2);
    ch = message.Extra1[0];//赋值，插入操作使用;
}

void TextEdit :: DataInsert()
{
    (*nowdata).InsertE(nowpos,ch);

}

void TextEdit :: DataDelete()
{
    PosChange(nowpos, -1);
    (*nowdata).GetE(nowpos,ch);
    (*nowdata).DeleteE(nowpos);
}

//void TextEdit :: DataCopy()


void TextEdit :: DataPaste()
{
        int i = 0;
        while(i < strlength)
        {
                if((nowpos.Y*linenum + nowpos.X) > (fpos.Y*linenum + fpos.X))
                {
                    (*nowdata).GetE(fpos,ch);
                    PosChange(fpos,+1);
                }
                else
                {
                    (*nowdata).GetE(fpos,ch);
                    PosChange(fpos,+2);
                }

                (*nowdata).InsertE(nowpos,ch);
                PosChange(nowpos,+1);
                i++;
        }
}

void TextEdit :: LookupStr()
{
    int i = 1,j = 0;
    int len;
    int length = from[0];
    int next[length];

    next[0] = 0;
    next[1] = 0;
    while( i < length )
    {
        if(j == 0 || from[i] == from[j])
        {
            ++ i;
            ++ j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }//构建next数组
    i = 0;

    len = (*nowdata).GetLength();
    while(i < len)
    {
        j = 1;
        while(i < len && j <= length)
        {
            (*nowdata).GetElem(i,ch);//use index to get element
            if( 0 == j || ch == from[j])
            {
                ++ i;
                ++ j;
            }
            else
            {
                j = next[j];
            }
        }

        COORD POS;
        if( j > length)
        {
            POS.X = i % linenum ;
            POS.Y = i/linenum + 1 ;//coordinate exchange
            PosChange(POS,-length + 1);
            (*nowqueue).push(POS);// post to queue
        }
    }//string matching

    pos = i;

}

bool TextEdit :: ExchangeStr()
{
        int i = 0;
        PosChange(nowpos,from[0] - 1);//delete from the rear
        while( i < from[0])
        {
                (*nowdata).DeleteE(nowpos);
                PosChange(nowpos,-1);
                i++;
        }
        PosChange(nowpos,+1);
        i = strlen(to);//insert from the rear
        while( i > 0)
        {
                (*nowdata).InsertE(nowpos,to[i - 1]);
                i--;
        }
        return true;
}

bool TextEdit :: OperRevoke()
{
    eMSG temmsg;
    int i = 0;

    if((*nowstack).pop(temmsg) == false)
    {
        return false;
    }
    (*nowdata).UpdataPage(temmsg.page);
    AssignMsg(temmsg);
    (*nowdata).UpdataPos(nowpos);

    switch(o_name)
    {
        case data_ins:
            PosChange(nowpos,1);
            DataDelete();
            break;

        case data_del:
            PosChange(nowpos,-1);
            DataInsert();
            break;

        case data_exc:
            strcpy(from + 1,temmsg.Extra2);
            strcpy(to,temmsg.Extra1);
            from[0] = strlen(temmsg.Extra2);
            ExchangeStr();//字符串替换
            break;

        case data_pst:
            while(i < strlength)
            {
                (*nowdata).DeleteE(nowpos);//粘贴
                i ++;
            }
            break;
        case pos_mov:

            break;
        default :
            break;
    }
    return true;
}

void TextEdit :: PosChange(COORD& POS, int dir)
{
    int sum = POS.X + dir;
    if(dir >= 0)
    {
            if(sum <= linenum)
            {
                    POS.X = sum;
            }
            else
            {
                    POS.Y++;
                    POS.X = sum - linenum;
            }
    }
    else
    {
            if(sum >= 1)
            {
                    POS.X = sum;
            }
            else
            {
                    POS.Y--;
                    POS.X =linenum + sum;
            }
    }
}
