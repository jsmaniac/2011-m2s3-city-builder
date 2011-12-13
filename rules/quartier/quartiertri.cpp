#include "all_includes.hh"

QuartierTri::QuartierTri(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	corner[0] = left;
	corner[1] = top;
	corner[2] = right;
	triangulation();
}

Chose* QuartierTri::factory(int seed, int n, Vertex left, Vertex top, Vertex right) {
	(void)seed;
	(void)n;
	// TODO
	return new QuartierTri(left, top, right);
}

bool QuartierTri::subdivide() {
	return false;
}

void QuartierTri::triangulation() {
	triangles.reserve(1);
	addTriangle(new Triangle(corner[0], corner[1], corner[2], 0xf0, 0xc0, 0xc0));
}