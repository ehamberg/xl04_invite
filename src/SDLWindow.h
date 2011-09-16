#ifndef SDLWINDOW_H_INCLUDED
#define SDLWINDOW_H_INCLUDED

#include <SDL/SDL.h>

class SDLWindow
{
	public:
		SDLWindow() {}
		SDLWindow(char *caption, int resolutionX, int resolutionY, int bpp);
		~SDLWindow();

		SDL_Surface *screen;
};

#endif
