#include <GL/gl.h>
#include <GL/glu.h>
#include "Bitmapfont.h"
#include "Scroller.h"

Scroller::Scroller(string str, SDL_Surface* sdlsurf)
{
	surface = sdlsurf;
	text = str;

	startTime = SDL_GetTicks();

	displacement = 0;
	string_placement = 0;

	font = new Bitmapfont("data/scroller_font.png", 32, 32);
}

Scroller::~Scroller()
{
	delete font;
}

void Scroller::drawScroller()
{
	setOrtho();
	string str = string(text, string_placement, string_placement+21);
	font->drawString(surface, displacement, 447, text);
	unsetOrtho();

	// update position
	displacement = -(int)((float)SDL_GetTicks()/10.0)+string_placement*32;
}

void Scroller::setOrtho()
{
	// Set 2D matrices
	glMatrixMode(GL_PROJECTION);  
	glPushMatrix();            
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, 1, -1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Scroller::unsetOrtho()
{
	// Restore 3D matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

int Scroller::getTime()
{
	return SDL_GetTicks() - startTime;
}
