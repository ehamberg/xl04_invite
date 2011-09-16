#ifndef SCROLLER_H_INCLUDED
#define SCROLLER_H_INCLUDED

#include <string>
#include "Bitmapfont.h"

using std::string;

class Scroller
{
	public:
		Scroller(string str, SDL_Surface* sdlsurf);
		~Scroller();

		void drawScroller();

	private:
		string text;
		Bitmapfont* font;
		int displacement;
		int string_placement;
		int startTime;

		// constants
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int CHAR_WIDTH;
		int CHAR_HEIGHT;
		char* CHARACTERS;

		void setOrtho();
		void unsetOrtho();
		int getTime();

		SDL_Surface* surface;
};

#endif
