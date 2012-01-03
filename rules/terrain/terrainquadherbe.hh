#ifndef _RULES_QUAD_HERBE_HH_
#define _RULES_QUAD_HERBE_HH_

#include "all_includes.hh"


class TerrainQuadHerbe : public Chose {
    private :
	Vertex c[4];

    public :
	TerrainQuadHerbe(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};


#endif
