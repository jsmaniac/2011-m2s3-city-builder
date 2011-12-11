#ifndef _TRIANGLE_HH_
#define _TRIANGLE_HH_

#include "all_includes.hh"

class Triangle {
	public:
	Vertex v1;
	Vertex v2;
	Vertex v3;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Vertexf vnormal;

	public:
	friend std::ostream& operator<<(std::ostream& os, const Triangle* t);
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	Triangle(Vertex v1, Vertex v2, Vertex v3, unsigned char r, unsigned char g, unsigned char b);
	float cosAngle(); // cosinus de l'angle en v2.
	float angle(); // angle en v2, en degrés. TODO : le calcul ne donne que des angles entre 0 et 180 !
	void display();
	
	private :
	Vertexf normal(Vertex v1, Vertex v2, Vertex v3);
};

#endif
