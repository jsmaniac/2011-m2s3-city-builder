#include "all_includes.hh"

Route::Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	triangulation();
}

bool Route::subdivide() {
	// TODO
	return false;
}

std::ostream& operator<<(std::ostream& os, const Route* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
	return os << "Route " << r.ne << "-" << r.se << "-" << r.sw << "-" << r.nw;
}

void Route::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(sw, se, ne, 0x36, 0x36, 0x36));
}
