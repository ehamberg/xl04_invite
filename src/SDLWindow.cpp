#include <iostream>
#include "SDLWindow.h"

using std::cerr;
using std::endl;

SDLWindow::SDLWindow(char *caption, int resolutionX, int resolutionY, int bpp)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, bpp);

	screen = SDL_SetVideoMode(resolutionX, resolutionY, bpp, SDL_OPENGL |
			SDL_FULLSCREEN);

	if (!screen)
		cerr << "Couldn't set video mode: " << SDL_GetError() << endl;

	SDL_WM_SetCaption(caption, "");
}

SDLWindow::~SDLWindow()
{
	SDL_FreeSurface(screen);
	SDL_Quit();
}

