#include "avl.h"
#include <fstream>
#include <string>

int main()
{
    std::string path = "C:/Programs/CMSC270/Assignment5/";
    AVLTree<int> x;

    x.insert(0);
    x.insert(3);
    x.insert(2);
    x.insert(4);
    x.insert(5);
    x.insert(1);
    x.insert(-1);
    x.insert(11);
    x.insert(24);
    x.insert(12);
    x.insert(-2);
    x.insert(-5);

    std::ofstream out(path+"tree.txt");
    x.snapShot(out);

    out.close();

    return 0;
}
