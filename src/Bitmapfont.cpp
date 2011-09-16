#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "Bitmapfont.h"
#include "Texture.h"

using std::string;

Bitmapfont::Bitmapfont()
{
	fontMap = new Texture("data/font.png");
	characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ∆ÿ≈ .,!?:;(){}<>\"'@*=+-|/\\_Ø";
	characterWidth = 16;
	characterHeight = 32;
}
Bitmapfont::Bitmapfont(const char* filename)
{
	fontMap = new Texture(filename);
	characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ∆ÿ≈ .,!?:;(){}<>\"'@*=+-|/\\_Ø";
	characterWidth = 16;
	characterHeight = 32;
}

Bitmapfont::Bitmapfont(const char* filename, int char_width, int char_height)
{
	fontMap = new Texture(filename);
	characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ∆ÿ≈ .,!?:;(){}<>\"'@*=+-|/\\_Ø";
	characterWidth = char_width;
	characterHeight = char_height;
}

Bitmapfont::~Bitmapfont()
{
}

void Bitmapfont::drawCharacter(SDL_Surface * surface, int x, int y, char c)
{
	float s, t; // used for temperarily storage of vertex-coordinates

	fontMap->bind();

	getCharacterPosition(c, &s, &t);

	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(s+0.0625, t); glVertex2i(x+characterWidth, y);            
		glTexCoord2f(s, t); glVertex2i(x, y);
		glTexCoord2f(s, t+0.25); glVertex2i(x, y+characterHeight);
		glTexCoord2f(s+0.0625, t+0.25); glVertex2i(x+characterWidth, y+characterHeight);
	}
	glEnd();
}

void Bitmapfont::drawString(SDL_Surface *surface, int x, int y, string s)
{
	int ix = x;
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == '\n') {
			ix = x;
			y += characterHeight;
		} else {
			drawCharacter(surface, ix, y, s[i]);
			ix+=characterWidth;
		}
	}
}

// for internal use
void Bitmapfont::getCharacterPosition(char c, float* s, float* t)
{
	int pos = 0;
	char *p = characters;

	// if c is lowercase, subtract 32 to make it uppercase
	if ((int)c >= 97 && (int)c <= 122)
		(int)c -= 32;
	// special cases for Ê, ¯ and Â
	else if (c == (int)'Ê')
		c = '∆';
	else if (c == (int)'¯')
		c = 'ÿ';
	else if (c == (int)'Â')
		c = '≈';

	if (c != '\0') { while (*p++ != c)
		{
			if (pos < 63)
				pos ++;
		}

		// if the caracter can't be found
		if (pos > 64 || pos < 0) {
			// return ' '
			pos = 40;
		}
	}

	*s = pos;
	*t = 0.0;

	while (*s > 15) {
		*s -= 16;
		*t += 1.0;
	}

	*s /= 16;
	*t /= 4;
}
