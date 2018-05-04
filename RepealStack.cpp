#include <iostream>
#include <stdlib.h>
#include "repealstack.h"

#define def 10

RepealStack::RepealStack()
{
        base = new eMSG[def];
        NowSize = 0;
        MaxSize = def;
        top = 0;
}

RepealStack::~RepealStack()
{
        delete []base;
}

void RepealStack::push(eMSG un)
{
        base[top] = un;
        top = (top + 1) % def;
        if(NowSize < def)
        {
                NowSize ++;
        }
}

bool RepealStack::pop(eMSG &un)
{
        if(NowSize == 0)
        {
                return false;
        }
        NowSize--;
        top = (def + top - 1)% def;
        un = base[top];
        return true;
}



