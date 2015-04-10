#include "stack.h"
#include <iostream>

stack::~stack()
{
    for(tp;!isEmpty();pop());
}

void stack::push(const int x)
{
    IntSLLNode *add = new IntSLLNode(x,tp);
    tp = add;
}

// should it check if stack is empty?
void stack::pop()
{
    if(!isEmpty())
    {
        IntSLLNode *temp = tp;
        tp = tp->next;
        delete temp;
    }
}
