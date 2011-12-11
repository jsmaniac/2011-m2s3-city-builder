#ifndef _RULES_TROTTOIRROUTE_HH_
#define _RULES_TRTTOIRROUTE_HH_

#include "all_includes.hh"

class TrottoirRoute : public Chose {
	private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
	int height;

	public :
	TrottoirRoute(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height);
	virtual bool subdivide();
	virtual void triangulation();
};

#endif
