#include "stack.h"
#include <iostream>

bool CheckSyntax(std::istream in);

int main(int argc, char *argv[])
{
    using namespace std;
    stack s;

    while(true)
    {
        cout << "Enter postfix equation: ";
        if(cin.peek()=='q') break;
        do {
            char ch = cin.peek();
            if(ch >= '0' && ch <= '9')
            {
                // Read an integer
                int n;
                cin >> n;
                s.push(n);
            }
            else if(ch == ' ')
                ch = cin.get(); // skip the space
            else
            {
                ch = cin.get();
                // ch is an operator or the - at the start of a number

                if(cin.peek() >= '0' && cin.peek() <= '9' && ch == '-')
                {
                    ch = cin.get();
                    int n = ch-'0';

                    while(cin.peek() >= '0' && cin.peek() <= '9')
                    {
                        ch = cin.get();
                        n = n*10 + (ch-'0');
                    }

                    s.push(-n);
                }
                else
                {
                    int a,b;

                    b=s.top(); //top elmt is right operand
                    s.pop();

                    a=s.top(); //top elmt is now left operand
                    s.pop();

                    cout << a << " " << b << " " << ch << endl;
                    switch(ch)
                    {
                    case '+':
                        s.push(a+b);
                        break;
                    case '-':
                        s.push(a-b);
                        break;
                    case '*':
                        s.push(a*b);
                        break;
                    case '/':
                        s.push(a/b);
                        break;
                    case '%':
                        s.push(a%b);
                        break;
                    default:
                        cout << ch << " is invalid" << endl;
                    }
                }
            }
        } while(cin.peek() != '\n');

        int sum = s.top();
        s.pop();

        cout << "Sum= " << sum << endl;
    }
    return 0;
}

bool isOp(char ch){return (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '%');}

bool CheckSyntax(std::istream in)
{
    char ch = in.get();
    for(ch; ch == ' '; ch=in.get());
    if(isOp(ch)) return false;
    while(!in.eof())
    {
        char a,b;
        a = in.get();
        if(!in.eof()) b = in.get();

        for(a,b;
            !in.eof() && isOp(in.peek());
            a=in.get(),
            b=(!in.eof()) ? in.get() : b);

    }
}











