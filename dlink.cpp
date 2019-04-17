#include <cstdio>
#include "dlink.h"

Dlink::Dlink()
{
    next = prev = NULL;
}


Dlink* Dlink::incr()
{
    return next;
}

Dlink* Dlink::decr()
{
    return prev;
}


Dlink* Dlink::append(Dlink* p)
{
    p->next = this;
    prev = p;
    return p;
}


void Dlink::excluse()
{
    if (next != NULL)
    {
        next->prev = prev;
    }
    if (prev != NULL)
    {
        prev->next = next;
    }
    return;
}


Dlink* Dlink::after(Dlink* p)
{
    p->prev = this;
    if(next != NULL)
    {
        p->next = next;
        next->prev = p;
    }
    else
    {
        p->next = NULL;
    }
    next = p;
    
    return p->next;
}


Dlink* Dlink::before(Dlink* p)
{
    p->next = this;
    p->prev = prev;
    if (prev != NULL)
    {
        prev->next = p;
    }
    prev = p;
    return p->prev;
}


Dlink* Dlink::tohead()
{
    Dlink* p = this;
    Dlink* q = NULL;
    while (p != NULL)
    {
        q = p;
        p = p->prev;
    }
    return q;
}


Dlink* Dlink::tohead(int n)
{
    Dlink* p = this;
    Dlink* q = this;
    int i = 0;
    while (p != NULL)
    {
        q = p;
        if(i == n)
        {
            break;
        }
        p = p->prev;
        i++;
    }
    return q;
}


Dlink* Dlink::totail()
{
    Dlink* p = this;
    Dlink* q = NULL;
    while (p != NULL)
    {
        q = p;
        p = p->next;
    }
    return q;
}


Dlink* Dlink::totail(int n)
{
    Dlink* p = this;
    Dlink* q = this;
    int i = 0;
    while (p != NULL)
    {
        q = p;
        if (i == n)
            break;
        p = p->next;
        i++;
    }
    return q;
}
