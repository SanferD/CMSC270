#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class edge
{
public:
    friend class graph;
    edge(char a, char b, int weight) :
        v1(a), v2(b), wt(weight) {}
    void print()
    {
        std::cout << v1 << " " << v2
                  << " " << wt << std::endl;
    }

    inline bool operator==(const edge& e) const
    {
        return this->v1==e.v1 && this->v2==e.v2
                && this->wt==e.wt;
    }
    inline bool operator<(const edge& e) const
    {
        return this->wt < e.wt;
    }
private:
    char v1, v2;
    int wt;
};

class graph
{
public:
    graph() {}
    ~graph();

    bool isCycle(edge E)
    {
        return isClosedPath(E.v1, E.v2, E.v2);
    }

    inline void addEdge(edge E)
    {
        edges.push_back(E);
    }
    void addVertex(char a);
    void addVertex(char a, char b)
    {
        addVertex(a);
        addVertex(b);
    }
    void KruskalsAlgorithm(std::vector<edge> &E);


    void print();

private:
    std::vector<edge> edges;
    std::vector<const int> vertices;

    std::map<char, char> root;
    std::map<char, char> next;
    std::map<char, int> length;

    std::vector<edge> getAdjEdges(char a);
    bool isClosedPath(char a, char b, char p);

    void Initialize();
    void Union(edge e);
};

#endif // GRAPH_H
