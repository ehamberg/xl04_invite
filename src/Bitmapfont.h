#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#include <SDL/SDL.h>
#include <iostream>
#include "Texture.h"

using std::string;

// class used for drawing characters form fontmap.png
class Bitmapfont
{
	public:
		Bitmapfont();
		Bitmapfont(const char* filename);
		Bitmapfont(const char* filename, int char_width, int char_height);
		~Bitmapfont();

		void drawCharacter(SDL_Surface *surface, int x, int y, char c);
		void drawString(SDL_Surface *surface, int x, int y, string s);

	private:
		Texture *fontMap;
		char *characters;
		int characterWidth;
		int characterHeight;

		void getCharacterPosition(char c, float* s, float* t);
};

#endif
