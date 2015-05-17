#include "fourtree.h"
#include <math.h>
#include <iostream>

double distance(const int, const int, const int, const int);

FourTree::~FourTree()
{
    if(root) removeSubtree(root);
}

void removeSubtree(Node *&n)
{
    if(n->nw) removeSubtree(n->nw);
    if(n->ne) removeSubtree(n->ne);
    if(n->sw) removeSubtree(n->sw);
    if(n->se) removeSubtree(n->se);
    n=0;
}

void FourTree::getVicinity(const Node *p, const Node *n,
                           std::vector<const char*> &cities,
                           const int r) const
{

    if(!p) return;
    if(distance(n->lat,n->lng,p->lat,p->lng) <= r)
    {
        cities.push_back(p->city);

        getVicinity(p->nw,n,cities,r);
        getVicinity(p->ne,n,cities,r);
        getVicinity(p->sw,n,cities,r);
        getVicinity(p->se,n,cities,r);
    }
    else
    {
        if( (p->lat <= n->lat) && (p->lng <= n->lng) )
            getVicinity(p->nw,n,cities,r);
        else if( (p->lat <= n->lat) && (p->lng > n->lng) )
            getVicinity(p->ne,n,cities,r);
        else if( (p->lat > n->lat) && (p->lng <= n->lng) )
            getVicinity(p->sw,n,cities,r);
        else
            getVicinity(p->se,n,cities,r);
    }
}

double distance(const int lt1, const int lg1,
                const int lt2, const int lg2)
{
    #define R 3956
    #define deg2rad(d) ( (double)( (d)*.017453293 ) )

    using std::sin;    using std::cos;
    using std::acos;   using std::floor;
    using std::ceil;

    double val = R*acos(
                  sin(deg2rad(lt1)) * sin(deg2rad(lt2)) +
                  cos(deg2rad(lt1)) * cos(deg2rad(lt2)) *
                  cos(deg2rad(lg1 - lg2))
                 );

    return (val < 0) ? ceil(val - .5) : floor(val + .5);
}

void FourTree::insert(Node *&p, Node *&n)
{
    if(!p) p = n;
    else if(n->city == p->city) return;
    else if( (n->lat < p->lat) && (n->lng < p->lng) )
        insert(p->se,n);
    else if( (n->lat < p->lat) && (n->lng >= p->lng) )
        insert(p->sw,n);
    else if( (n->lat >= p->lat) &&  (n->lng < p->lng) )
        insert(p->ne,n);
    else // (n->lat >= p->lat) && (n->lng >= p->lng)
        insert(p->nw,n);
}
