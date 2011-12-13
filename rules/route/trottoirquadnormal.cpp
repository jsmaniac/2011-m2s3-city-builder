#include "all_includes.hh"

TrottoirQuadNormal::TrottoirQuadNormal(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) {
	this->ne = ne;
	this->nw = nw;
	this->se = se;
	this->sw = sw;
	this->height = height;
	triangulation();
}

bool TrottoirQuadNormal::subdivide() {
	// TODO
	return false;
}

void TrottoirQuadNormal::triangulation() {
	addTriangle(new Triangle(ne + Vertex(0,0,height), nw + Vertex(0,0,height) , sw + Vertex(0,0,height), 0x66, 0x66, 0x66));
	addTriangle(new Triangle(sw + Vertex(0,0,height), se + Vertex(0,0,height), ne + Vertex(0,0,height), 0x66, 0x66, 0x66));
	//addTriangle(new Triangle(ne + Vertex(0,0,height), nw + Vertex(0,0,height), sw + Vertex(0,0,height), 0x66, 0x66, 0x66));
	//addTriangle(new Triangle(sw + Vertex(0,0,height), se + Vertex(0,0,height), ne + Vertex(0,0,height), 0x66, 0x66, 0x66));

	addTriangle(new Triangle(nw + Vertex(0,0,height), nw, sw, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(sw, sw + Vertex(0,0,height), nw + Vertex(0,0,height), 0x66, 0x66, 0x66));
	addTriangle(new Triangle(ne, ne + Vertex(0,0,height), se + Vertex(0,0,height), 0x66, 0x66, 0x66));
	addTriangle(new Triangle(se + Vertex(0,0,height), se, ne, 0x66, 0x66, 0x66));

	addTriangle(new Triangle(ne + Vertex(0,0,height), ne, nw, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(nw, nw + Vertex(0,0,height), ne + Vertex(0,0,height), 0x66, 0x66, 0x66));
	addTriangle(new Triangle(sw, sw + Vertex(0,0,height), se + Vertex(0,0,height), 0x66, 0x66, 0x66));
	addTriangle(new Triangle(se + Vertex(0,0,height), se, sw, 0x66, 0x66, 0x66));
}
