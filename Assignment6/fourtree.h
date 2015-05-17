#ifndef FOURTREE_H
#define FOURTREE_H

#include <vector>

static const double R = 3956;
static const double c = 0.017453293;

class FourTree;

class Node
{
    friend class FourTree;
public:
    Node(const char *name,
         int lattitude, int longitude,
         Node *NW=0, Node *NE=0, Node *SW=0,
         Node *SE=0) : city(name) , lat(lattitude) ,
         lng(longitude) , nw(NW), ne(NE), sw(SW), se(SE)
    {}

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

    void insert(Node* &node)
    {
        insert(root, node);
    }

    const std::vector<const char*>
    getVicinity(const Node *node,const int dist) const
    {
        std::vector<const char*> cities;
        getVicinity(root, node,0,cities, dist);
        return cities;
    }

    const std::vector<const char*>
    getVicinity(const int lat,const int lng,
                const int dist) const
    {
        std::vector<const char*> cities;
        Node *temp = new Node(0,lat,lng);
        getVicinity(root, temp,0,cities, dist);
        return cities;
    }

private:
    Node *root;
    void insert(Node *&p, Node *&n);
    void getVicinity(const Node *p, const Node *n, const Node *prev,
                    std::vector<const char*> &cities, const int r) const;
};

#endif // FOURTREE_H
