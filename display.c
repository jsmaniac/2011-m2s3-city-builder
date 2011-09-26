#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

int main(int argc, char *argv[]) {
	short continuer;
	SDL_Event event;

	argc = argc; /* Unused */
	argv = argv; /* Unused */
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Mon premier programme OpenGL !",NULL);
	SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

	continuer = 1;
	while (continuer) {
		SDL_WaitEvent(&event);
		
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
			glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
			glColor3ub(0,255,0);    glVertex2d(0,0.75);
			glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
		glEnd();

		glFlush();
		SDL_GL_SwapBuffers();
	}

	SDL_Quit();

	return 0;
}
