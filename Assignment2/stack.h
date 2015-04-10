#ifndef STACK_H
#define STACK_H

#include "intsllst.h"
#include <limits.h>

// top points to first element.
class stack
{
public:
  stack(){tp=0;}
  ~stack();

  bool isEmpty() const {return tp==0;}
  int top() const {return tp ? tp->info : INT_MAX;} // Return the int at the top of the stack

  void push(const int x); // Push a new int on the stack
  void pop(); // Remove the item at the top of the stack
private:
    IntSLLNode *tp;
};

#endif // STACK_H
