#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "doublylinkedlist.h"

/* creates a file of randomly generated positive integers, num in total,
 * starting at min and ending at max.
 */
void fillFile(std::string fName,int num,int min,int max)
{
    std::ofstream out;
    out.open(fName);

    srand((unsigned int)time(NULL));
    for(int i=0;i!=num;i++)
    {
        int val = (min<max) ? std::rand() % (1+max-min) + min
                            : std::rand() % (1+min-max) + max;
        out << val << std::endl;
    }
    out.close();
}

int main()
{
    ifstream src;
    DoublyLinkedList<int> dll;

    std::string path = "C:/Programs/CMSC270/Assignment3/";

    fillFile(path+"unsorted.txt",25,-50,50);
    src.open(path+"unsorted.txt");

    int x;
    src>>x;
    dll.insert(dll.begin(), x);

    while(src >> x)
    {
        DoublyLinkedList<int>::Iterator iter = dll.begin();
        for(iter; iter!=dll.end() && *iter < x; iter++);
        if(iter!=dll.end())
        {
            if(*iter > x) dll.insert(iter,x);
        }
        else dll.insert(iter,x);
    }

    std::cout << dll << std::endl;
    return 0;
}
