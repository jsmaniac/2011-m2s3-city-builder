#ifndef _VIEW_HH_
#define _VIEW_HH_

#include "all_includes.hh"

// TODO :
// flycam : le centre ne bouge pas, la souris contrôle l'angle de vue x & y
//          les flèches avant/arrière permettent d'avancer/reculer.
// Calcul correct des normales dans triangle.cpp
// Prendre en compte tous les évènements X en attente avant de relancer le rendu.

class View {
private:
	Chose* root;
	
	static const int windowWidth = 1024;
	static const int windowHeight = 768;
	int cameraDist;
	
	int xSight;
	int ySight;
	int zSight;
	
	float xAngle;
	float yAngle;
	int moveDist;
public:
	View(Chose* root);
	void initWindow();
	void mainLoop();
	void renderScene();
	void displayAxes();
};

#endif
