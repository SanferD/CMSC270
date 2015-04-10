#include "stack.h"
#include <iostream>

#define ISOP(ch) (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%')
#define ISNUM(ch) (ch>='0' && ch<='9')

int main()
{
    using namespace std;

    while(true)
    {
        stack s;
        bool isValid = true;
        cout << "Enter postfix equation (q=Quit): ";

        if(cin.peek()=='q') break;
        do {
            char ch = cin.peek();

            if(ISNUM(ch))
            {
                ch = cin.get();
                int n = ch-'0';
                while(ISNUM(cin.peek()))
                {
                    ch = cin.get();
                    n = n*10 + (ch-'0');
                }
                s.push(n);
            }

            else if(ch == ' ') ch = cin.get(); // skip the space

            /* Validate Operator or Create Negative Number */
            else if(ISOP(ch))
            {
                ch = cin.get();

                if(ISNUM(cin.peek()) && ch == '-')
                {   // create negative integer
                    ch = cin.get();
                    int n = ch-'0';

                    while(ISNUM(cin.peek()))
                    {
                        ch = cin.get();
                        n = n*10 + (ch-'0');
                    }

                    s.push(-n);
                }
                else
                {
                    int a,b;

                    if(s.isEmpty())
                    {
                        isValid = false;
                        break;
                    }
                    b=s.top(); // top elmt is right operand
                    s.pop();

                    if(s.isEmpty())
                    {
                        isValid = false;
                        break;
                    }
                    a=s.top(); // top elmt is now left operand
                    s.pop();

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
            else
            {
                isValid = false;
                break;
            }
        } while(cin.peek() != '\n');

        /* Check if syntax is valid and print sum if it is. */
        if(isValid && !s.isEmpty())
        {
            int sum = s.top();
            s.pop();

            if(s.isEmpty()) // otherwise too few operations were performed.
                cout << "Sum= " << sum << endl;
            else
                cout << "Invalid Syntax" << endl;
        }
        else
            cout << "Invalid Syntax" << endl;

        // reset cin.
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
    }
    return 0;
}
