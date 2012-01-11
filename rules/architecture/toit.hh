#ifndef _RULES_ARCHITECTURE_TOIT_HH_
#define _RULES_ARCHITECTURE_TOIT_HH_

#include "all_includes.hh"

class ToitQuad : public Chose {
private:
	Quad c;
	float height;
public:
	ToitQuad(Quad _c, float _height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
private:
	void pointCentral();
	void deuxPoints();
	void deuxPointsVerticaux();
	void plat();
	static const char r = 0xF1;
	static const char g = 0xE0;
	static const char b = 0xE0;
};

class ToitTri : public Chose {
private:
	Triangle c;
	float height;
public:
	ToitTri(Triangle _c, float _height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
private:
	void pointCentral();
	void troisPoints();
	void unPointVertical();
	void deuxPointsVerticaux();
	void plat();
	static const char r = 0xF1;
	static const char g = 0xE0;
	static const char b = 0xE0;
};

#endif
