#include "fourtree.h"

int main()
{
    FourTree tree;
    std::vector<const char*> cities;

    tree.insert("LOUISEVILLE",38,85);
    tree.insert("WASHINGTON",38,77);
    tree.insert("CHICAGO",41,87);
    tree.insert("NEW YORK",40,74);
    tree.insert("PITTSBURG",40,79);
    tree.insert("DAYTON",39,84);
    tree.insert("NASHVILLE",36,87);
    tree.insert("MONTREAL",45,73);
    tree.insert("CLEVELAND",41,81);
    tree.insert("ATLANTA",34,84);

    cities = tree.getVicinity(40,79,200);

    std::cout << std::endl;
    for(int i=0;i!=cities.size();i++)
        std::cout << cities[i] << std::endl;

    return 0;
}
