#include <iostream>
#include "fourtree.h"
#include <vector>

using namespace std;

int main()
{
    FourTree tree;
    vector<const char*> cities;
    Node *one = new Node("LOUISEVILLE",38,85);
    Node *two = new Node("WASHINGTON",38,77);
   // Node *three = new Node("Dummy",100,100);

    tree.insert(one);
    tree.insert(two);
   // tree.insert(three);

    cities = tree.getVicinity(38,77,10000);

    for(int i=0;i!=cities.size();i++)
        cout << cities[i] << endl;

    return 0;
}
