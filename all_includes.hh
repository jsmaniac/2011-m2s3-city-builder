#ifndef _ALL_INCLUDES_HH_
#define _ALL_INCLUDES_HH_

typedef long long int64;

class Chose;

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "vertex.hh"
#include "segment.hh"
#include "triangle.hh"
#include "directions.hh"
#include "hash.hh"
#include "view.hh"

#include "rules/chose.hh"
#include "rules/quad.hh"
#include "rules/batiment.hh"
#include "rules/carrefour.hh"
#include "rules/route.hh"
#include "rules/rectangleroutes.hh"
#include "rules/quadroutes.hh"

#endif
