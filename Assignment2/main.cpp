#include "stack.h"
#include <iostream>

#define isOp(ch) (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%')
#define isNum(ch) (ch>='0' && ch<='9')
// becuase stack only holds numbers, this checks for an operator in terms of its number.
#define isOpNum(n) (n==('+'-'0') || n==('-'-'0') || n==('*'-'0') || n==('/'-'0') || n==('%'-'0'));

bool CheckSyntax(std::istream& in);

/* Beta version will have check syntax.
 *
 */
int main(int argc, char *argv[])
{
    using namespace std;
    stack s;

    while(true)
    {
        cout << "Enter postfix equation: ";
        CheckSyntax(cin);
        cout << "a" << endl;
        if(cin.peek()=='q') break;
        do {
            char ch = cin.peek();
            if(isNum(ch))
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

                if(isNum(ch) && ch == '-')
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

        // reset cin.
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
    }
    return 0;
}


bool CheckSyntax(std::istream& in)
{
    using namespace std;


    stack s;
    do{
        char ch = in.get();
        if(isOp(ch))
        {
            if(ch=='-')
                if(isNum(in.peek()))
                {
                    int n = in.get()-'0';
                    while(isNum(in.peek()))
                    {
                        ch = cin.get();
                        n = n*10 + (ch-'0');
                    }
                    s.push(-n);
                }
                else
                    s.push(ch-'0');
            else

                s.push(ch-'0');
        }
        else if(isNum(ch)) s.push(ch);
        else if(!isNum(ch) && !isOp(ch) && ch!=' ') return false;
    } while(in.peek() != '\n');
    cout << "print stack" << endl;
    s.print();
    in.seekg(0,std::ios::beg);
    return true;
}
