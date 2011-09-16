#ifndef ABOUT_H_INCLUDED
#define ABOUT_H_INCLUDED

#include <iostream>
#include "Scene.h"
#include "Bitmapfont.h"
#include "Texture.h"

using std::string;

class About : public Scene
{
	public:
		About(SDL_Surface *sdlsurf);
		~About();

		void render();
		int run();

	private:
		int done;
		Texture* dude;
		Bitmapfont* font;
		string text;

		int textYPosition;
		int dudey;
		int scrollbarTop; // position of scrollbar
		int scrollbarHeight; // height of scrollbar handle
		int lines; // number of linex in text
		bool autoScroll; // determines if the text should autoscroll or not
		int scrollbarHandleClicked; // set to cursors y-position
		int tempYPos; // used for temperarily storing the texts y-position
		int upArrowClicked;		// These are set to the return-value of
		int downArrowClicked;	// getTime() when the user clicks on an arrow
		int scrollBarClicked;	// or the scrollbar (not handle)

		void drawScrollbar();
};

#endif
