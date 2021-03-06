Triangle::Triangle() {
}
Triangle::Triangle(Vertex left, Vertex top, Vertex right) {
	c[LEFT] = left;
	c[TOP] = top;
	c[RIGHT] = right;
}

float Triangle::cosAngle() const {
	return (c[LEFT]-c[TOP]).cosAngle(c[RIGHT]-c[TOP]);
}

float Triangle::angle() const {
	// TODO : gérer le cas d'un angle à 0 ou 180.
	return std::acos(cosAngle());
}

float Triangle::minAngle() const {
	float at = angle();
	float ar = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float al = Angle::Pi - at - ar;
	return std::min(std::min(al, at), ar);
}

float Triangle::maxAngle() const {
	float at = angle();
	float ar = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float al = Angle::Pi - at - ar;
	return std::max(std::max(al, at), ar);
}

SommetTriangle Triangle::maxAngleCorner() const {
	float at = angle();
	float ar = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float al = Angle::Pi - at - ar;
	if (al > at && al > ar) return LEFT;
	else if (at > ar) return TOP;
	else return RIGHT;
}

SommetTriangle Triangle::minAngleCorner() const {
	float at = angle();
	float ar = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float al = Angle::Pi - at - ar;
	if (al < at && al < ar) return LEFT;
	else if (at < ar) return TOP;
	else return RIGHT;
}

float Triangle::minLength() const {
	return std::min(std::min((c[LEFT] - c[TOP]).norm(), (c[TOP] - c[RIGHT]).norm()), (c[RIGHT] - c[LEFT]).norm());
}

float Triangle::maxLength() const {
	return std::max(std::max((c[LEFT] - c[TOP]).norm(), (c[TOP] - c[RIGHT]).norm()), (c[RIGHT] - c[LEFT]).norm());
}

Triangle Triangle::inset(CoteTriangle side, float offset) const  {
	Triangle t = (*this) << int(side);
	Vertex offsetDirection = Triangle(t[TOP], t[LEFT], t[LEFT] + t.normal()).normal();
	Vertex rightside = t[RIGHT] - t[TOP];
	Vertex base = t[RIGHT] - t[LEFT];
	float distTR = offset / offsetDirection.cosAngle(rightside);
	float distLR = offset / offsetDirection.cosAngle(base);
	t[TOP] = t[TOP] + rightside.setNorm(distTR);
	t[LEFT] = t[LEFT] + base.setNorm(distLR);
	return t >> int(side);
}

Triangle Triangle::insetLTR(float offset) const {
	return (*this).inset(LEFTSIDE, offset).inset(RIGHTSIDE, offset).inset(BASE, offset);
}

Triangle operator+(const Triangle& t, const Vertex& v) {
	return Triangle(t[LEFT] + v, t[TOP] + v, t[RIGHT] + v);
}

Vertex Triangle::randomPoint(int seed, int n) const {
	float rndl = floatInRange(seed, n, 0, 1);
	float rndr = floatInRange(seed, hash2(n, 42), 0, 1 - rndl);
	return c[TOP] + (c[LEFT] - c[TOP]) * (rndl) + (c[RIGHT] - c[TOP]) * (rndr);
}

float Triangle::surface() const {
	float hauteur = Segment(c[TOP], c[LEFT] + (c[TOP] - c[LEFT]).projectOn(c[RIGHT] - c[LEFT])).length();
	float base = Segment(c[LEFT], c[RIGHT]).length();
	return (base * hauteur) / 2.f;
}

Vertex Triangle::normal() const {
	return ((c[LEFT] - c[TOP]) * (c[RIGHT] - c[TOP]));
}

Vertex Triangle::normalizedNormal() const {
	Vertex v = normal();
	return v / v.norm();
}

Triangle Triangle::offsetNormal(float offset) const {
	return ((*this) + this->normal().setNorm(offset));
}

Triangle Triangle::insetProportionnal(float prop) {
    Triangle rTriangle = *this;
    //ibc : isobarycentre.
    Vertex ibc = Segment(c[TOP],Segment(c[LEFT],c[RIGHT]).center()).at(2.f/3.f);
    prop = prop;

    rTriangle[TOP] = Segment(ibc,c[TOP]).at(prop);
    rTriangle[LEFT] = Segment(ibc,c[LEFT]).at(prop);
    rTriangle[RIGHT] = Segment(ibc,c[RIGHT]).at(prop);
    return rTriangle;
}






