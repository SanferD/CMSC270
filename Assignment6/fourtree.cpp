#include "fourtree.h"
#include <math.h>
#include <iostream>
using namespace std;

FourTree::~FourTree()
{

}

void FourTree::getVicinity(const Node *p, const Node *n,
                const Node *prev, std::vector<const char*> &cities,
                const int r) const
{
    using std::sin;    using std::cos;
    using std::acos;

    if(!p) return;

    double d = R*acos(sin((double)p->lat) *
                      sin((double)n->lat) +
                      cos((double)p->lat) * cos((double)n->lat)
                    * cos((double)n->lng-p->lng));

    cout << p->city << " " << d << " " << r << " " << acos(sin((double)p->lat) *
                                                           sin((double)n->lat) +
                                                           cos((double)p->lat) * cos((double)n->lat)
                                                         * cos((double)n->lng-p->lng)) << endl;

    if(d <= r)
    {
        cities.push_back(p->city);

        if(p->nw!=prev) getVicinity(p->nw,n,p,cities,r);
        if(p->ne!=prev) getVicinity(p->ne,n,p,cities,r);
        if(p->sw!=prev) getVicinity(p->sw,n,p,cities,r);
        if(p->se!=prev) getVicinity(p->se,n,p,cities,r);
    }
    else
    {
        if(p->lat<=n->lat && p->lng<=n->lng)
            getVicinity(p->ne,n,p,cities,r);
        else if(p->lat<=n->lat && p->lng>n->lng)
            getVicinity(p->nw,n,p,cities,r);
        else if(p->lat>n->lat && p->lng<=n->lng)
            getVicinity(p->se,n,p,cities,r);
        else
            getVicinity(p->sw,n,p,cities,r);
    }
}

void FourTree::insert(Node* &p, Node* &n)
{
    if(!p) p = n;
    else if(n->city == p->city) return;
    else if(n->lat<p->lat && n->lng<p->lng)
        insert(p->sw,n);
    else if(n->lat<p->lat && n->lng>=p->lng)
        insert(p->se,n);
    else if(n->lat>=p->lat && n->lng<p->lng)
        insert(p->nw,n);
    else // n->lat>=p->lat && n->lng>=p->lng
        insert(p->ne,n);
}



