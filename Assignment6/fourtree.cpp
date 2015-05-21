#include "fourtree.h"
#include <math.h>

#define R 3956
#define DEG2RAD(d) ( (double)( (d)*.017453293 ) )
#define RAD2DEG(d) ( (double)( (d)/.017453293 ) )


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
    delete n;
    n=0;
}

void FourTree::getVicinity(const Node *p, const Node *n,
                           std::vector<const char*> &cities,
                           const int r) const
{
    // Checks the location of the node relative to the candidate.
    #define ISNW(nodeLat,nodeLng,canLat,canLng) (nodeLat>=canLat && nodeLng>=canLng)
    #define ISNE(nodeLat,nodeLng,canLat,canLng) (nodeLat>=canLat && nodeLng<canLng )
    #define ISSW(nodeLat,nodeLng,canLat,canLng) (nodeLat<canLat  && nodeLng>=canLng)
    #define ISSE(nodeLat,nodeLng,canLat,canLng) (nodeLat<canLat  && nodeLng<canLng )

    using std::asin;
    using std::sin;
    using std::cos;

    double d;
    if(!p) return;
    if(d=distance(n->lat,n->lng,p->lat,p->lng) <= r)
    {
        cities.push_back(p->city);

        getVicinity(p->nw,n,cities,r);
        getVicinity(p->ne,n,cities,r);
        getVicinity(p->sw,n,cities,r);
        getVicinity(p->se,n,cities,r);
    }
    else
    {
        double lat, lng;
        double nLat,nLong,wLat,wLong,sLat,sLong,eLat,eLong;

        nLat  = RAD2DEG(DEG2RAD(p->lat)+d/R);
        sLat  = RAD2DEG(DEG2RAD(p->lat)-d/R);
        nLong = sLong= p->lng;

        wLat  = eLat = RAD2DEG(asin( sin(DEG2RAD(p->lat))/cos(d/R) ));
        wLong = p->lng + RAD2DEG( cos(d/R)*
                                  cos(asin(sin(DEG2RAD(p->lat))/cos(d/R)))/
                                  cos(DEG2RAD(p->lat)) );
        eLong = p->lng - RAD2DEG( cos(d/R)*
                                  cos(asin(sin(DEG2RAD(p->lat))/cos(d/R)))/
                                  cos(DEG2RAD(p->lat)) );

        lat = n->lat;
        lng = n->lng;
        if( ISNW(lat,lng,nLat,nLong) || ISNW(lat,lng,sLat,sLong) ||
            ISNW(lat,lng,eLat,eLong) || ISNW(lat,lng,wLat,wLong) )
            getVicinity(p->nw,n,cities,r);
        if( ISNE(lat,lng,nLat,nLong) || ISNE(lat,lng,sLat,sLong) ||
            ISNE(lat,lng,eLat,eLong) || ISNE(lat,lng,wLat,wLong) )
            getVicinity(p->ne,n,cities,r);
        if( ISSW(lat,lng,nLat,nLong) || ISSW(lat,lng,sLat,sLong) ||
            ISSW(lat,lng,eLat,eLong) || ISSW(lat,lng,wLat,wLong) )
            getVicinity(p->sw,n,cities,r);
        if( ISSE(lat,lng,nLat,nLong) || ISSE(lat,lng,sLat,sLong) ||
            ISSE(lat,lng,eLat,eLong) || ISSE(lat,lng,wLat,wLong) )
            getVicinity(p->se,n,cities,r);

    }
}

double FourTree::distance(const int lt1, const int lg1,
                const int lt2, const int lg2) const
{
    using std::sin;    using std::cos;
    using std::acos;   using std::floor;
    using std::ceil;

    double val = R*acos(
                  sin(DEG2RAD(lt1)) * sin(DEG2RAD(lt2)) +
                  cos(DEG2RAD(lt1)) * cos(DEG2RAD(lt2)) *
                  cos(DEG2RAD(lg1 - lg2))
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
