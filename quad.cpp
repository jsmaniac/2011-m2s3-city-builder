#include "all_includes.hh"

Quad::Quad() {}

Quad::Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

void Quad::offset(/*Cardinal*/int side, int offset) {
	Vertex voffset = (corner[NE + side]-corner[NW + side]).perpendicular().setNorm(offset);
	corner[NE + side] = corner[NE + side] + voffset.projectOn(corner[NE + side]-corner[SE + side]);
	corner[NW + side] = corner[NW + side] + voffset.projectOn(corner[NW + side]-corner[SW + side]);
}

int Quad::minLength() {
	return std::min(
		std::min(
			Segment(corner[NE],corner[SE]).length(),
			Segment(corner[SE],corner[SW]).length()
		), std::min(
			Segment(corner[SW],corner[NW]).length(),
			Segment(corner[NW],corner[NE]).length()
		)
	);
}

int Quad::maxLength() {
	return std::max(
		std::max(
			Segment(corner[NE],corner[SE]).length(),
			Segment(corner[SE],corner[SW]).length()
		), std::max(
			Segment(corner[SW],corner[NW]).length(),
			Segment(corner[NW],corner[NE]).length()
		)
	);
}
