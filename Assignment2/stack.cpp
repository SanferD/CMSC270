#include "stack.h"

stack::~stack()
{
    for(tp;!isEmpty();pop());
    delete tp;
}


void stack::push(int x)
{
    if(tp)
    {
        IntSLLNode *head = tp->next;
        tp->next = new IntSLLNode(x);
        tp = tp->next;
        tp->next = head;
    }
    else
    {
        tp = new IntSLLNode(x);
        tp->next = tp;
    }
}

void stack::pop()
{
    if(!isEmpty())
        if(tp->next==tp)
        {
            delete tp;
            tp = 0;
        }
        else
        {
            IntSLLNode *temp = tp;
            IntSLLNode *head = tp->next;
            for(temp;temp->next!=tp;temp=temp->next);
            delete tp;
            tp = temp;
            tp->next = head;
        }
}
