#include "graph.h"

graph::~graph()
{
    edges.clear();
    vertices.clear();
    root.clear();
    next.clear();
    length.clear();
}

void graph::addVertex(char a)
{
    if (find(vertices.begin(),
             vertices.end(), a) == vertices.end() )
        vertices.push_back(a);
}

void graph::KruskalsAlgorithm(std::vector<edge> &E)
{
    Initialize();
    for (int i=0; i!=E.size(); Union(E[i++]));
}

std::vector<edge> graph::getAdjEdges(char a)
{
    std::vector<edge> adjE;
    std::vector<edge>::iterator iter = edges.begin();

    while( iter != edges.end() )
    {
        if ( iter->v1==a || iter-> v2==a )
            adjE.push_back(*iter);
        iter++;
    }

    return adjE;
}

void graph::print()
{
    for(int i=0; i!=edges.size(); i++)
    {
        edge e = edges[i];
        e.print();
    }
}


bool graph::isClosedPath(char a, char b, char p)
{
    std::vector<edge> adj = getAdjEdges(a);
    bool isClosed = false;

    for(int i=0; i!=adj.size(); i++)
    {
        edge e = adj[i];
        char v = e.v1==a ? e.v2 : e.v1;
        if (v!=p)
        {
            if (v != b)
                isClosed = isClosed ||
                        isClosedPath(v, b, a);
            else
                return true;
        }
    }

    return isClosed;
}

void graph::Initialize()
{
    typedef std::pair<char, char> pair1;
    typedef std::pair<char, int> pair2;

    for(int i=0; i!=vertices.size(); i++)
    {
        root.insert(pair1(vertices[i], vertices[i]));
        next.insert(pair1(vertices[i], vertices[i]));
        length.insert(pair2(vertices[i], 1));
    }
}

void graph::Union(edge e)
{
    char v = e.v1, u = e.v2;
    if(root[u] == root[v])
        return;
    else if (length[root[v]] < length[root[u]] )
    {
        char rt = root[v];
        length[root[u]] += length[rt];
        root[rt] = root[u];
        for (char j=next[rt]; j!=rt; j=next[j])
            root[j] = root[u];
        // swap
        char temp = next[rt], b = next[root[u]];
        next[rt] = b;
        next[root[u]] = temp;
        // add edge
        edges.push_back(e);
    }
    else
    {
        char rt = root[u];
        length[root[v]] += length[rt];
        root[rt] = root[v];
        for (char j=next[rt]; j!=rt; j = next[j])
            root[j] = root[v];
        // swap
        char temp = next[rt], b = next[root[v]];
        next[rt] = b;
        next[root[v]] = temp;
        // add edge
        edges.push_back(e);
    }


}

