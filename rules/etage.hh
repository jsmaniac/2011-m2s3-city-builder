#ifndef _RULES_ETAGE_HH_
#define _RULES_ETAGE_HH_

#include "all_includes.hh"

class EtageQuad : public Chose {
    private :
	Quad c;
	Quad ch;
	QuadBool w;
	int etage;
	int nbEtages;

    public :
	EtageQuad(Quad c, Quad ch, QuadBool _w, int _etage, int _nbEtages);
	virtual void split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

class EtageTri : public Chose {
    private :
	Triangle c;
	Triangle ch;
	TriBool w;
	int etage;
	int nbEtages;

    public :
	EtageTri(Triangle c, Triangle ch, TriBool _w, int _etage, int _nbEtages);
	virtual void split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
