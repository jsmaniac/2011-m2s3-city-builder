#ifndef _RULES_ROUTE_HH_
#define _RULES_ROUTE_HH_

#include "all_includes.hh"

class RouteQuadChaussee : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	RouteQuadChaussee(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
	virtual void triangulation();
};

#endif
