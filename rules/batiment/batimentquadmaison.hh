#ifndef _RULES_BATIMENTMAISON_HH_
#define _RULES_BATIMENTMAISON_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuadMaison : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	static const int minHeight = 400;
	static const int maxHeight = 800;
public:
	BatimentQuadMaison(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	int width();
	int height();
	virtual bool subdivide();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
};

#endif