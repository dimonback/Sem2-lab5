#include <cstdio>
#include <cstdlib>
#include "dlink.h"
#include <locale.h>
#include <iostream>
using namespace std;

class SymLink : public Dlink
{
private:
    
public:
    unsigned char sym; //код символа
    SymLink(unsigned char c) : Dlink(), sym(c) {}
    SymLink* incr() { return((SymLink*)Dlink::incr()); }
    SymLink* decr() { return((SymLink*)Dlink::decr()); }
    SymLink* seek(int);
    void print(char, char);
    static SymLink* find_max(SymLink* head, char max);
};

SymLink* SymLink::seek(int n)
{
    if (n > 0)
        return ((SymLink*)Dlink::totail(n));
    if (n < 0)
        return ((SymLink*)Dlink::tohead(abs(n)));
    return this;
}

void SymLink::print(char max, char min)
{
    SymLink* p = this;
    SymLink *q, *s;
    s = p;
    while (p != NULL)
    {
        putchar(p->sym);
        q = p->incr();
        p = q;
    }
    p = s;
    while (p != NULL)
    {
        if (p->sym == max || p->sym == min)
            putchar('^');
        else if(p->sym != '\n')
            putchar(' ');
        q = p->incr();
        p = q;
    }
    putchar('\n');
}

SymLink* SymLink::find_max(SymLink* node, char max)
{
    SymLink *right = node->incr();
    SymLink *left = node->decr();
    SymLink *node_max(nullptr);
    while (node_max == nullptr) {
        if (right != nullptr) {
            if ((right->sym) == max) {
                node_max = right;
            }
            right = right->incr();
        }
        if (left != nullptr) {
            if (left->sym == max) {
                node_max = left;
            }
            left = left->decr();
        }
    }
    return node_max;
}

int main()
{
    int count = 0;
    int length = 0;
    int ch; //код входного символа
    unsigned pos;
    SymLink* watch[2]; // адреса сторожевых символов в начале и конце списка
    SymLink* head;
    SymLink* tail;
    SymLink *p, *q, *max_, *min_;
    
    Dlink* (Dlink::*insert[])(Dlink*) = {&Dlink::after, &Dlink::before};
    
    setlocale(LC_ALL, "Russian");
    watch[0] = head = new SymLink('\n');
    watch[1] = tail = new SymLink('\n');
    tail->before(head);
    while ((ch = getchar()) != '\n')
    {
        q = new SymLink(ch);
        tail->before(q);
        length++;
    }
  
    
    pos = 1;
    char max = '0';
    char min = head->seek(1)->sym;
    
    while (count < (length))
    {
        if ((head->seek(pos)->sym) < min)
        {
            min = head->seek(pos)->sym;
        }
        
        if ((head->seek(pos)->sym) > max)
        {
            max = head->seek(pos)->sym;
        }
        count++;
        pos++;
    }
    if (max == min)
    {
        cout << "min = max = " << min << endl;
        return 0;
    }
    else
    {
        cout << "min = " << min << endl;
        cout << "max = " << max << endl;
    }
    
    head->print(max, min);
    
    min_ = head;
    max_ = head;
    
    pos = 1;
    count = 0;
    SymLink *current = head;
    SymLink** max_arr = new SymLink*[length];
    SymLink** min_arr = new SymLink*[length];
    
    while (current != nullptr)
    {
        if (current->sym == min)
        {
            min_arr[count] = current;
            max_arr[count] = SymLink::find_max(current, max);
            count++;
        }
        current = current->incr();
    }
    for (int i = 0; i < count; i++)
    {
        if (min_arr[i] == head)
        {
            head = min_arr[i]->decr();
        }
        else if (min_arr[i] == tail)
        {
            tail = min_arr[i]->incr();
        }
        min_arr[i]->excluse();
        max_arr[i]->after(min_arr[i]);
    }
    
    head->print(max, min);
    
    p = tail;
    while (p != NULL)
    {
        q = p->decr();
        p->excluse();
        delete p;
        p = q;
    }
    return (length);
}
