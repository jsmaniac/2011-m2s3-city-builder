#ifndef _RULES_BATIMENTPONT_HH_
#define _RULES_BATIMENTPONT_HH_

#include "all_includes.hh"


class BatimentQuadPont: public Chose {
    private :
	Vertex c[4];
	int height;

    public :

	BatimentQuadPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height);
	virtual ~BatimentQuadPont();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif