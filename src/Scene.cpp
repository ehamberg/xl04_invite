#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Scene.h"

Scene::Scene()
{
	done = false;
	startTime = SDL_GetTicks();
}

Scene::~Scene()
{
}

int Scene::getTime()
{
	return SDL_GetTicks() - startTime;
}

void Scene::init()
{
	startTime = SDL_GetTicks();

	// OpenGL stuff
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(45.0, float(640/480), 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int Scene::run()
{
	// generic mainloop, run until esc is pressed or the window is closed
	while (!done) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = true;
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					return 1;
					break;
				default:
					break;
			}
		}
		render();
	}

	// scene finished, return success
	return 0;
}

void Scene::drawBackground()
{
	setOrtho();

	// draw a nice orange-to-yellow gradient
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glBegin(GL_QUADS);
	{
		glColor3ub(255, 128, 0);   glVertex2i(639, 0);            
		glColor3ub(255, 128, 0);   glVertex2i(0, 0);
		glColor3ub(247, 215, 107); glVertex2i(0, 479);
		glColor3ub(247, 215, 107); glVertex2i(639, 479);
	}
	glEnd();

	unsetOrtho();
}

void Scene::render()
{
	// empty, derived classes will always have their own render method
}

void Scene::setOrtho()
{
	// Set 2D matrices
	glMatrixMode(GL_PROJECTION);  
	glPushMatrix();            
	glLoadIdentity();
	glOrtho(0, 639, 479, 0, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Scene::unsetOrtho()
{
	// Restore 3D matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

