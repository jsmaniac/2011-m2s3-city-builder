#ifndef _RULES_QUARTIER_QUARTIERQUADCARRE_HH_
#define _RULES_QUARTIER_QUARTIERQUADCARRE_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuartierQuadCarre : public QuartierQuad {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierQuadCarre(Quad c);
	virtual bool split();
};

#endif
