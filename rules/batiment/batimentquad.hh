#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuad : public Chose {
    private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
	Cardinal entry;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, Cardinal door);
	virtual ~BatimentQuad();
	int width();
	int height();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual std::vector<Vertex*> getBoundingBoxPoints() const;
};

#endif
