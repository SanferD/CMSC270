#include "graph.h"
#include <fstream>

#define FP "C:/Programs/CMSC270/Assignment7/graph.txt"

int main()
{
    std::vector<edge> E;
    graph G;
    std::ifstream src(FP);
    char a,b;
    int wt;

    while(src >> a >> b >> wt)
    {
        edge e((int)a,(int)b,wt);
        E.push_back(e);
        G.addVertex(a,b);
    }

    std::sort(E.begin(), E.end());

    G.KruskalsAlgorithm(E);

    G.print();
    std::cout<< "done." << std::endl;

    return 0;
}


