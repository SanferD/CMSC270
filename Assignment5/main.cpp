#include "avl.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

int main()
{
    std::string path = "C:/Programs/CMSC270/Assignment5/";

    AVLTree<int> x;
    std::ofstream out;
    bool invalid, unbalanced;
    int max=1000000,min=-1000000,num=500000;

    /* Generate the tree from random integers.
     */
    std::cout << "Start." << std::endl;

    srand((unsigned int)time(NULL));
    for(int i=0;i!=num;i++)
    {
        int val = std::rand() % (1+max-min) + min;
        x.insert(val);
    }

    /* Save the tree to disk.
     */
    out.open(path+"tree.txt");
    x.snapShot(out);
    out.close();

    /* Validate the tree.
     */
    std::cout << "Begin verification." << std::endl;

    if(invalid = !x.isValid()) std::cout << "Tree constraint not satisfied." << std::endl;
    if(unbalanced = !x.isBalanced()) std::cout << "Tree is unbalanced." << std::endl;

    std::cout << "Done." << std::endl;
    if(!invalid && !unbalanced) std::cout << "Successfully created balanced tree of " << num
                                    << " nodes on [" << min << "," << max << "]." << std::endl;

    return 0;
}
