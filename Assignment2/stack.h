#ifndef STACK_H
#define STACK_H

#include "intsllst.h"

// top points to first element.
class stack
{
private:
    IntSLLNode *tp;
public:
  stack(){tp=0;}
  ~stack();

  bool isEmpty() const {return tp==0;}
  int top() const {return tp->info;} // Return the int at the top of the stack

  void push(int x); // Push a new int on the stack
  void pop(); // Remove the item at the top of the stack
};

#endif // STACK_H
