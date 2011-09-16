#include <GL/gl.h>
#include "SDLWindow.h"
#include "Music.h"
#include "Intro.h"
#include "About.h"
#include "Bitmapfont.h"

int main(int argc, char *argv[])
{
	SDLWindow *mainWin = new SDLWindow("Xenox XL 2004", 640, 480, 16);
	SDL_EnableKeyRepeat(300, 40);

	Intro* in = new Intro(mainWin->screen);
	Music *mu = new Music("data/kenet-beautiful_or_not.xm");
	About* ab;

	// start playing music
	mu->fadeIn(100);

	SDL_ShowCursor(SDL_DISABLE);
	// run intro-scene and continue unless a rude user closed the window
	if (in->run() == 1)
		delete in;
	else {
		SDL_ShowCursor(SDL_ENABLE);
		ab = new About(mainWin->screen);
		ab->run();
		delete ab;
	}

	delete mainWin;

	return 0;
}
