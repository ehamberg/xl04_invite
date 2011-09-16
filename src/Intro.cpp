#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "Texture.h"
#include "Intro.h"
#include "Particle.h"
#include "Scroller.h"

#include "xenox_logo.h"

// "models"
#include "xenox.h"
#include "pc.h"
#include "steinkjerhallen.h"
#include "xl04.h"
#include "jgh24022802.h"
#include "hall.h"

Intro::Intro(SDL_Surface *sdlsurf)
{
	done = 0;
	surface = sdlsurf;
	
	xenoxLogo = new Texture("data/xenox_logo.png");

	string lol = "                    "
		"DU ER HERVED INVITERT TIL XENOX XL04   -   SAA TA MED PC-EN DIN "
		"OG BLI MED PAA GAME- OG SCENE-COMPOS   -   TID: VINTERFERIEN, UKE 9, "
		"STED: STEINKJERHALLEN   -   ";
	scroller = new Scroller(lol, surface);
	p1 = new Particle(256);
	p2 = new Particle(128);

	// feed coordinates to p1
	for (int i = 0; i < p1->getNumber(); i++)
		p1->addStartCoordinates((rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < p1->getNumber(); i++)
		p1->addState(0, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < xenox_numberVertices; i++)
		p1->addState(1, xenox_vertices[i][0], xenox_vertices[i][1],
				xenox_vertices[i][2]);
	for (int i = 0; i < xenox_numberVertices; i++)
		p1->addState(2, xenox_vertices[i][0], xenox_vertices[i][1],
				xenox_vertices[i][2]);
	for (int i = 0; i < p1->getNumber(); i++)
		p1->addState(3, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < pc_numberVertices; i++)
		p1->addState(4, pc_vertices[i][0], pc_vertices[i][1],
				pc_vertices[i][2]);
	for (int i = 0; i < pc_numberVertices; i++)
		p1->addState(5, pc_vertices[i][0], pc_vertices[i][1],
				pc_vertices[i][2]);
	for (int i = 0; i < p1->getNumber(); i++)
		p1->addState(6, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < pc_numberVertices; i++)
		p1->addState(7, steinkjerhallen_vertices[i][0], steinkjerhallen_vertices[i][1],
				steinkjerhallen_vertices[i][2]);
	for (int i = 0; i < steinkjerhallen_numberVertices; i++)
		p1->addState(8, steinkjerhallen_vertices[i][0], steinkjerhallen_vertices[i][1],
				steinkjerhallen_vertices[i][2]);
	for (int i = 0; i < p1->getNumber(); i++)
		p1->addState(9, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);

	// feed coordinates to p2
	for (int i = 0; i < p2->getNumber(); i++)
		p2->addStartCoordinates((rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < p2->getNumber(); i++)
		p2->addState(0, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < xl04_numberVertices; i++)
		p2->addState(1, xl04_vertices[i][0], xl04_vertices[i][1],
				xl04_vertices[i][2]);
	for (int i = 0; i < xl04_numberVertices; i++)
		p2->addState(2, xl04_vertices[i][0], xl04_vertices[i][1],
				xl04_vertices[i][2]);
	for (int i = 0; i < p2->getNumber(); i++)
		p2->addState(3, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < jgh24022802_numberVertices; i++)
		p2->addState(4, jgh24022802_vertices[i][0], jgh24022802_vertices[i][1],
				jgh24022802_vertices[i][2]);
	for (int i = 0; i < jgh24022802_numberVertices; i++)
		p2->addState(5, jgh24022802_vertices[i][0], jgh24022802_vertices[i][1],
				jgh24022802_vertices[i][2]);
	for (int i = 0; i < p2->getNumber(); i++)
		p2->addState(6, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);
	for (int i = 0; i < jgh24022802_numberVertices; i++)
		p2->addState(7, hall_vertices[i][0], hall_vertices[i][1],
				hall_vertices[i][2]);
	for (int i = 0; i < hall_numberVertices; i++)
		p2->addState(8, hall_vertices[i][0], hall_vertices[i][1],
				hall_vertices[i][2]);
	for (int i = 0; i < p2->getNumber(); i++)
		p2->addState(9, (rand()%21)-10, (rand()%21)-10, (rand()%21)-10);

	glPointSize(3.0);
	rotation = 0.0;
	init();
}

Intro::~Intro()
{
	glPointSize(1.0);
	delete scroller;
	delete p1;
	delete p2;
}

void Intro::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawBackground();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(65.0, float(640/480), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);

	if (getTime() <= 2500) {
		// draw rotating 'X'
		glPushMatrix();
		//glTranslatef(0.0, 0.9,-12.0);
		glTranslatef(0.0, 0.9,-112+(float)(getTime()/25.0));
		glRotatef(((float)getTime()/(2500.0/720.0)), 0.0, 0.0, 1.0);
		glColor4ub(0, 0, 0, 155);
		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < xenox_logo_numberFaces; i++) {
				glVertex3fv(xenox_logo_vertices[xenox_logo_faces[i][0]]);
				glVertex3fv(xenox_logo_vertices[xenox_logo_faces[i][1]]);
				glVertex3fv(xenox_logo_vertices[xenox_logo_faces[i][2]]);
			}
		}
		glEnd();
		glPopMatrix();
	} else {
		setOrtho();
		// draw logo-thingie
		xenoxLogo->bind();

		if (getTime() < 5000)
			// fade out logo
			glColor4ub(255, 255, 255,
					(unsigned char)(255-(getTime()-2500)/(2500.0/188.0)));
		else
			glColor4ub(255, 255, 255, 67);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(1.0, 0.0); glVertex2i(576, 112);            
			glTexCoord2f(0.0, 0.0); glVertex2i(64, 112);
			glTexCoord2f(0.0, 1.0); glVertex2i(64, 368);
			glTexCoord2f(1.0, 1.0); glVertex2i(576, 368);
		}
		glEnd();
		unsetOrtho();
	}

	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glTranslatef(0.0, 0.6,-5.0);
	glRotatef(rotation, 0.0, 1.0, 0.0);

	glColor3ub(0, 0, 0);
	glBegin(GL_POINTS);
	{
		for (int i = 0; i < p1->getNumber(); i++) {
			glVertex3fv(p1->getPosition(i));
		}
		for (int i = 0; i < p2->getNumber(); i++) {
			glVertex3fv(p2->getPosition(i));
		}
	}
	glEnd();

	// draw pc
	if (getTime() >= 25000 && getTime() <= 30000) {
		glColor4ub(247, 215, 107, 32);
		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < pc_numberFaces; i++) {
				glVertex3fv(pc_vertices[pc_faces[i][0]]);
				glVertex3fv(pc_vertices[pc_faces[i][1]]);
				glVertex3fv(pc_vertices[pc_faces[i][2]]);
			}
		}
		glEnd();

		// wireframe
		if (getTime() < 27500)
			glColor4ub(0, 0, 0, 255-
					(unsigned char)(255-(getTime()-27500)/(2500.0/255.0)));
		else
			glColor4ub(0, 0, 0, (unsigned char)(255-(getTime()-27500)/(2500.0/255.0)));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < pc_numberFaces; i++) {
				glVertex3fv(pc_vertices[pc_faces[i][0]]);
				glVertex3fv(pc_vertices[pc_faces[i][1]]);
				glVertex3fv(pc_vertices[pc_faces[i][2]]);
			}
		}
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// draw hall
	if (getTime() >= 40500 && getTime() <= 45500) {
		glColor4ub(247, 215, 107, 32);
		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < hall_numberFaces; i++) {
				glVertex3fv(hall_vertices[hall_faces[i][0]]);
				glVertex3fv(hall_vertices[hall_faces[i][1]]);
				glVertex3fv(hall_vertices[hall_faces[i][2]]);
			}
		}
		glEnd();

		// wireframe
		if (getTime() < 43000)
			glColor4ub(0, 0, 0, 255-
					(unsigned char)(255-(getTime()-42500)/(2500.0/255.0)));
		else
			glColor4ub(0, 0, 0, (unsigned char)(255-(getTime()-43000)/(2500.0/255.0)));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < hall_numberFaces; i++) {
				glVertex3fv(hall_vertices[hall_faces[i][0]]);
				glVertex3fv(hall_vertices[hall_faces[i][1]]);
				glVertex3fv(hall_vertices[hall_faces[i][2]]);
			}
		}
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	scroller->drawScroller();

	// blink screen when logo stops
	if (getTime() >= 2500 && getTime() < 2800) {
		setOrtho();
		glBindTexture(GL_TEXTURE_2D, GL_NONE);
		glColor4ub(255, 255, 255, 255-
				(unsigned char)((getTime()-2500.0)/(300.0/255.0)));
		glBegin(GL_QUADS);
		{
			glVertex2i(640, 0);
			glVertex2i(0, 0);
			glVertex2i(0, 480);
			glVertex2i(640, 480);
		}
		glEnd();
		unsetOrtho();
	}

	// start fading out right before the scene is complete
	if (getTime() >= 49000) {
		setOrtho();
		glBindTexture(GL_TEXTURE_2D, GL_NONE);
		glColor4ub(0, 0, 0, (unsigned char)((getTime()-49000.0)/(1000.0/255.0)));
		glBegin(GL_QUADS);
		{
			glVertex2i(640, 0);
			glVertex2i(0, 0);
			glVertex2i(0, 480);
			glVertex2i(640, 480);
		}
		glEnd();
		unsetOrtho();
	}

	//p1->morphToState((float)SDL_GetTicks()/10000.0);
	p1->morphToState((float)getTime()/5000.0);
	p2->morphToState(((float)getTime()-500)/5000.0);

	// fade out scene when escape was pressed
	if (done > 0) {
		setOrtho();
		glColor4f(0.0, 0.0, 0.0, (float)(getTime()-done)/500.0);
		glBegin(GL_QUADS);
		{
			glVertex2i(639, 0);
			glVertex2i(0, 0);
			glVertex2i(0, 479);
			glVertex2i(639, 479);
		}
		glEnd();
		unsetOrtho();
	}

	SDL_GL_SwapBuffers();

	// use 5 seconds to complete one full rotation
	rotation = ((float)getTime()/(5000.0/360.0));
	if (rotation >= 360.0)
		rotation -= 360.0;
}

int Intro::run()
{
	// run until esc is pressed or the window is closed while registering all
	while (true) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = getTime();
							break;
						case 'f':
							SDL_WM_ToggleFullScreen(surface);
						default:
							break;
					}
					break;
				case SDL_QUIT:
					return 1;
					break;
				default: break;
			}
		}
		if (done > 0 && getTime() - done > 500)
			break;
		else if (getTime() < 50000)
			render();
		else
			break;
	}

	// scene finished, return success
	return SCENE_MAIN_MENU;
}
