#include "all_includes.hh"

View::View(Chose* root) : root(root), camera(Camera(Vertexf(127,14,128),44,101,40,0.6)) {
	initWindow();
	mainLoop();
}

void View::setColor(unsigned char r, unsigned char g, unsigned char b) {
	float MatDif[4] = {r/255.f, g/255.f, b/255.f, 1.0f};
	float MatAmb[4] = {r/500.f, g/500.f, b/500.f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
}

void View::initWindow() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Sortie terrain OpenGL",NULL);
	SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_OPENGL);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)windowWidth/windowHeight,1,10000);
	glEnable(GL_DEPTH_TEST);
	glewInit();
	
	float MatSpec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float MatDif[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	float MatAmb[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	float shininess = 128.0f;
	 
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
	glMaterialfv(GL_FRONT,GL_SHININESS,&shininess);
	
	glEnable(GL_LIGHTING); 	// Active l'éclairage
  	glEnable(GL_LIGHT0);	// Active la lumière 0;
}

void View::setLight() {
	float Light1Pos[4] = {0.5f, 1.0f, 1.0f, 0.0f};
	float Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float Light1Spec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float Light1Amb[4] = {0.2f, 0.2f, 0.2f, 1.0f};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);
	glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
}

void View::displayAxes() {
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(255,0,0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(2500.0f, 0.0f, 0.0f); // ending point of the line
	glEnd( );
	
	glBegin(GL_LINES);
	glColor3ub(0,255,0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 2500.0f, 0.0f); // ending point of the line
	glEnd( );
	
	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 0.0f, 2500.0f); // ending point of the line
	glEnd( );

	glEnable(GL_LIGHTING);
}

void View::renderScene(int lastTime, int currentTime) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	
	camera.animation(currentTime-lastTime);
	camera.setCamera();
	
	setLight();
	displayAxes();
	root->display();
	
	glFlush();
	SDL_GL_SwapBuffers();
}

void View::mainLoop() {
	short continuer = 1;
	SDL_Event event;
	SDL_EnableKeyRepeat(40,40);
	SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);

	int lastTime = SDL_GetTicks() - 30;
	int currentTime = 0;
	
	while (continuer) {
		lastTime = currentTime;
		currentTime = SDL_GetTicks();
		while ( SDL_PollEvent(&event) ) {
			switch(event.type) {
				case SDL_QUIT:
					continuer = 0;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					camera.keyboard(event.key);
					/*switch(event.key.keysym.sym) {
						case SDLK_DOWN:
							cameraCenter = cameraCenter - Vertex::fromSpherical(moveDist, yAngle, xAngle);
							break;
						case SDLK_UP:
							cameraCenter = cameraCenter + Vertex::fromSpherical(moveDist, yAngle, xAngle);
							break;
						case SDLK_PAGEUP:
							cameraCenter = cameraCenter - Vertex::fromSpherical(moveDist, yAngle + 90, xAngle);
							break;
						case SDLK_PAGEDOWN:
							cameraCenter = cameraCenter + Vertex::fromSpherical(moveDist, yAngle + 90, xAngle);
							break;
						case SDLK_LEFT:
							cameraCenter = cameraCenter - Vertex::fromSpherical(moveDist, 90, xAngle - 90);
							break;
						case SDLK_RIGHT:
							cameraCenter = cameraCenter + Vertex::fromSpherical(moveDist, 90, xAngle - 90);
							break;
						case SDLK_ESCAPE:
							continuer = 0;
							break;
						default:
							if (SDL_GetKeyName(event.key.keysym.sym)[0] == 'q')
								continuer = 0;
							if (SDL_GetKeyName(event.key.keysym.sym)[0] == 'p') { // _Print _Position
								std::cout << "Camera = " << cameraCenter << " xAngle = " << xAngle << " yAngle = " << yAngle << std::endl;
							}
							break;
					}*/
					break;
					
				case SDL_MOUSEMOTION:
					camera.mouseMotion(event.motion);
					break;
					
				default:
					break;
			}
		}

		renderScene(lastTime,currentTime);
	}

	SDL_Quit();
}

Camera::Camera(Vertexf pos, float xA, float yA, int moveSensitivity, float mouseSensitivity) {
	cameraCenter = pos;
	xAngle = xA;
	yAngle = yA;
	cameraSight = cameraCenter + Vertexf::fromSpherical(100,yA,xA);
	moveDist = moveSensitivity;
	this->mouseSensitivity = mouseSensitivity;
}

void Camera::setCamera() {
	cameraSight = cameraCenter + Vertexf::fromSpherical(100, yAngle, xAngle);
	gluLookAt(cameraCenter.x,cameraCenter.y,cameraCenter.z, cameraSight.x, cameraSight.y, cameraSight.z,0,0,1);
}

void Camera::mouseMotion(const SDL_MouseMotionEvent &event) {
	xAngle -= event.xrel*mouseSensitivity;
	yAngle += event.yrel*mouseSensitivity;
	if(yAngle > 179)
		yAngle = 179;
	else if(yAngle < 1)
		yAngle = 1;
}

void Camera::keyboard(const SDL_KeyboardEvent &eventKey) {
	switch(eventKey.keysym.sym) {
		case SDLK_UP:
			up = (eventKey.type == SDL_KEYDOWN);
			break;
		case SDLK_DOWN:
			down = (eventKey.type == SDL_KEYDOWN);
			break;
		case SDLK_LEFT:
			left = (eventKey.type == SDL_KEYDOWN);
			break;
		case SDLK_RIGHT:
			right = (eventKey.type == SDL_KEYDOWN);
			break;
		case SDLK_PAGEUP:
			pageUp = (eventKey.type == SDL_KEYDOWN);
			break;
		case SDLK_PAGEDOWN:
			pageDown = (eventKey.type == SDL_KEYDOWN);
			break;
		case SDLK_ESCAPE:
			exit(0);
			break;
		default :
			break;
	}
}

void Camera::animation(int elapsedTime) {
	float diff = ((float)(elapsedTime+1)/1000.)*(float)moveDist;
	
	if(up)
		cameraCenter = cameraCenter + Vertexf::fromSpherical(diff, yAngle, xAngle);
	if(down)
		cameraCenter = cameraCenter - Vertexf::fromSpherical(diff, yAngle, xAngle);
	if(left)
		cameraCenter = cameraCenter - Vertexf::fromSpherical(diff, 90, xAngle - 90);
	if(right)
		cameraCenter = cameraCenter + Vertexf::fromSpherical(diff, 90, xAngle - 90);
	if(pageUp)
		cameraCenter = cameraCenter - Vertexf::fromSpherical(diff, yAngle + 90, xAngle);
	if(pageDown)
		cameraCenter = cameraCenter + Vertexf::fromSpherical(diff, yAngle + 90, xAngle);
}
