#ifndef FOURTREE_H
#define FOURTREE_H

#include <vector>
#include <iostream>

class FourTree;

class Node
{
    friend class FourTree;
public:
    Node(const char *name,
         const int lattitude, const int longitude,
         Node *NW=0, Node *NE=0, Node *SW=0,
         Node *SE=0) : city(name) , lat(lattitude) ,
         lng(longitude) , nw(NW), ne(NE), sw(SW), se(SE)
    {}
    friend void removeSubtree(Node *&p);
private:
    const char *city;
    int lat, lng;
    Node *nw, *ne, *sw, *se;
};

class FourTree
{
public:
    FourTree(){root = 0;}
    ~FourTree();

    /* Two wrappers: insert Node* or insert (lat,long)
     */
    void insert(Node *&node)
    {
        insert(root, node);
    }

    void insert(const char* name, const int lat,
                const int lng)
    {
        Node *node = new Node(name,lat,lng);
        insert(root,node);
    }

    /* Two wrappers: getVicinity of Node* within radius r inclusive
     * or getVicinity of (lat,long) within radius r.
     */
    const std::vector<const char*>
    getVicinity(const Node *node,const int dist) const
    {
        std::vector<const char*> cities;

        printDistance(root,node,dist);
        getVicinity(root, node,cities, dist);

        return cities;
    }

    const std::vector<const char*>
    getVicinity(const int lat,const int lng,
                const int dist) const
    {
        std::vector<const char*> cities;
        Node *temp = new Node(0,lat,lng);

        printDistance(root,temp,dist);
        getVicinity(root, temp,cities, dist);

        return cities;
    }

private:
    Node *root;
    void insert(Node *&p, Node *&n);
    void getVicinity(const Node *p, const Node *n,
                     std::vector<const char*> &cities,
                     const int r) const;
    double distance(const int, const int, const int, const int) const;
    void printDistance(const Node *p,const Node *n, const int r) const
    {
        double d = distance(n->lat,n->lng,p->lat,p->lng);
        if(d<=r) std::cout << p->city << " " << d << std::endl;

        if(p->nw) printDistance(p->nw,n,r);
        if(p->ne) printDistance(p->ne,n,r);
        if(p->sw) printDistance(p->sw,n,r);
        if(p->se) printDistance(p->se,n,r);
    }
};

#endif // FOURTREE_H
