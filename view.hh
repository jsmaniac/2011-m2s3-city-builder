#ifndef _VIEW_HH_
#define _VIEW_HH_

#include "all_includes.hh"

class Camera {
public :
	Vertex cameraCenter;
	Vertex cameraSight;

private :
	float xAngle;
	float yAngle;
	int moveSensitivity;
	float mouseSensitivity;
	bool up;
	bool down;
	bool left;
	bool right;
	bool pageUp;
	bool pageDown;
	bool autoPilot;

public :
	Camera(Vertex pos, float xA, float yA, int moveSensitivity, float mouseSensitivity);
	void setCamera();
	void mouseMotion(const SDL_MouseMotionEvent &event);
	void keyboard(const SDL_KeyboardEvent &event);
	void animation(int elapsedTime);
	std::ostream& print(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Camera& c) { return c.print(os); }

    private :
    int takeScreenshot(const char * filename);
};


class View {
private :
	Chose* root;

public :
	Camera camera;
private:
	Lod lod;
    GLfloat fogColor[4];

public :
	View(Chose* root);
	void initWindow();
	void mainLoop();
	void renderScene(int lastTime, int currentTime);
	void displayAxes();

	static void setColor(unsigned char r, unsigned char g, unsigned char b);

private :
	void setLight();
	void setSkybox();
};

#endif
