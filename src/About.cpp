#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "Texture.h"
#include "About.h"
#include "x.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

About::About(SDL_Surface *sdlsurf)
{
	dudey = 400;
	done = 0;
	surface = sdlsurf;
	startTime = SDL_GetTicks();
	font = new Bitmapfont;
	dude = new Texture("data/nekkidboi.png");
	autoScroll = false;
	textYPosition = 0;

	text =
		"    __ __ ____  _ __   ___  __ __\n"
		"   |  Y  Y  _ ¯Y '_ \\F¯ _ ¯Y  Y  7\n"
		"   }-   -{  |  |  |  7  |  }-   -{\n"
		"___|  .  |  J  |  |  |  |  |  .  |___\n"
		"¯¯¯|  |  |  ___|  |  |  J  |  |  |¯¯¯\n"
		"   l  |__j.___.7__|__|.___.J._l  |\n"
		"   :  :           :  :        :  :\n"
		"   .  . X   L   2   0   0   4 .  .\n"
		"\n"
		"-------------------------------------\n"
		" -== THE BeSt ParTy SinCe XL03!! ==-\n"
		"-------------------------------------\n"
		"\n"
		"\n"
		"TID:\n"
		"----\n"
		"FRA TIRSDAG 24. FEBRUAR KLOKKEN 10:00\n"
		"TIL LØRDAG 28. FEBRUAR KLOKKEN 13:37\n"
		"\n"
		"\n"
		"\n"
		"STED:\n"
		"-----\n"
		"*STEINKJERHALLEN, STEINKJER\n"
		"\n"
		" 3000 kvadratmeter med gulvplass!\n"
		"\n"
		"\n"
		"\n"
		"INTERNETT:\n"
		"----------\n"
		"34 Mbps levert av NTE-Bredbånd\n"
		"\n"
		"\n"
		"\n"
		"NETTVERK:\n"
		"---------\n"
		"10/100 Mbps full-duplex\n"
		"Offisielle IP-er til alle\n"
		"\n"
		"\n"
		"\n"
		"GAME- OG SCENE-COMPOS:\n"
		"----------------------\n"
		"\n"
		"* GAME\n"
		"  \n"
		"  - Counter-Strike\n"
		"  \n"
		"  - Quake III Arena\n"
		"  \n"
		"  - WarCraft 3\n"
		"  \n"
		"  - FIFA 2004\n"
		"  \n"
		"  - Fragmovie\n"
		"    \n"
		"\n"
		"\n"
		"* SCENE\n"
		"  \n"
		"  - Music \n"
		"        - Tracked \n"
		"        - High Quality\n"
		"\n"
		"  - Graphics \n"
		"        - Drawn\n"
		"        - Rendered\n"
		"\n"
		"  - Demo\n"
		"\n"
		"  - Useless Utility\n"
		"\n"
		"  - Anim\n"
		"  \n"
		"\n"
		"\n"
		"SALG AV MAT OG HARDWARE:\n"
		"-----------------------  \n"
		"  - Cola, Bawls og Sjokolade  \n"
		"  \n"
		"  - Dagens middag til rundt 50,-\n"
		"  \n"
		"  - Pølser, Wraps, Burgere, \n"
		"    Pommes Frites og Baguetter\n"
		"  \n"
		"  - Kaffe\n"
		"  \n"
		"  - Gratis frukt fra COOP Mega!\n"
		"  \n"
		"  \n"
		"\n"
		"\n"
		"MASSE FOLK:\n"
		"----------\n"
		"Maksimum kapasitet: 600\n"
		"\n"
		"\n"
		"\n"
		"SCENESHOW:\n"
		"---------\n"
		"Jubileums-show. \n"
		"\n"
		"Interaktiv underholdning hele partyet\n"
		"\n"
		"Masse giveaways fra våre sponsorer\n"
		"\n"
		"\n"
		"\n"
		"GOD PLASS TIL SOVING:\n"
		"--------------------\n"
		"\n"
		"Bare husk å ta med sove-utstyr!\n"
		"\n"
		"\n"
		"\n"
		"CREW MED MASSE PARTY-ERFARING\n"
		"----------------------------\n"
		"Xenox har levert bra dataparty siden \n"
		"1999!\n"
		"\n"
		"Xenox XL04 blir det tiende og største \n"
		"xenox-party! \n"
		"\n"
		"\n"
		"\n"
		"Du trenger med andre ord ikke kle på \n"
		"deg i vinter.. \n"
		"\n"
		"         ... for du skal sitte inne!\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"  --==(Du kan trykke ESC nå..)==--\n";

	// count number of lines
	{
		lines = 0;
		for (int i = 0; i < (int)text.length(); i++)
			if (text[i] == '\n')
				lines++;
	}

	scrollbarHeight = 6240/lines;
	scrollbarHandleClicked = 0;
	tempYPos = 0;
	upArrowClicked = 0;
	downArrowClicked = 0;
	scrollBarClicked = 0;

	init();
}

About::~About()
{
	delete font;
	delete dude;
}

void About::drawScrollbar()
{
	// draw scrollbar arrows
	{
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
		glColor3ub(0, 0, 0);
		glBegin(GL_TRIANGLES);
		{
			// up-arrow
			glVertex2i(635, 27);
			glVertex2i(611, 27);
			glVertex2i(623, 4);

			// down-arrow
			glVertex2i(635, 451);
			glVertex2i(611, 451);
			glVertex2i(623, 475);

		}
		glEnd();

		glBindTexture(GL_TEXTURE_2D, GL_NONE);
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(639, 32);
			glVertex2i(607, 32);
			glVertex2i(607, 0);
			glVertex2i(639, 0);
		}
		glEnd();

		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(639, 479);
			glVertex2i(607, 479);
			glVertex2i(607, 447);
			glVertex2i(639, 447);
		}
		glEnd();
	}

	// draw scrollbar handle
	{
		// make sure the scrollbar handle never touches any of the arrows :)
		if (scrollbarTop+scrollbarHeight-32 > 415)
			scrollbarTop = 415 - scrollbarHeight + 32;
		else if (scrollbarTop < 31)
			scrollbarTop = 31;

		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(639, scrollbarTop);
			glVertex2i(607, scrollbarTop);
			glVertex2i(607, scrollbarTop+scrollbarHeight);
			glVertex2i(639, scrollbarTop+scrollbarHeight);
		}
		glEnd();

		// draw the three lines in the middle of the handle
		glBegin(GL_LINES);
		{
			glVertex2i(615, scrollbarTop+(int)(scrollbarHeight/2)-4);
			glVertex2i(631, scrollbarTop+(int)(scrollbarHeight/2)-4);

			glVertex2i(615, scrollbarTop+(int)(scrollbarHeight/2));
			glVertex2i(631, scrollbarTop+(int)(scrollbarHeight/2));

			glVertex2i(615, scrollbarTop+(int)(scrollbarHeight/2)+4);
			glVertex2i(631, scrollbarTop+(int)(scrollbarHeight/2)+4);
		}
		glEnd();
	}

}

void About::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawBackground();

	// draw rotating 'X'
	glTranslatef(0.0, 0.0,-5.0);
	glRotatef((float)getTime()/100.0, 0.0, 1.0, 0.0);
	glColor4ub(247, 215, 107, 32);
	glBegin(GL_TRIANGLES);
	{
		for (int i = 0; i < x_numberFaces; i++) {
			glVertex3fv(x_vertices[x_faces[i][0]]);
			glVertex3fv(x_vertices[x_faces[i][1]]);
			glVertex3fv(x_vertices[x_faces[i][2]]);
		}
	}
	glEnd();

	// wireframe
	glColor4ub(255, 195, 87, 255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	{
		for (int i = 0; i < x_numberFaces; i++) {
			glVertex3fv(x_vertices[x_faces[i][0]]);
			glVertex3fv(x_vertices[x_faces[i][1]]);
			glVertex3fv(x_vertices[x_faces[i][2]]);
		}
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// update textYPosition if autoScroll is true
	if (autoScroll) {
		textYPosition = (int)(getTime()/50);

		if (textYPosition > ((lines-15)*32))
				textYPosition = (lines-15)*32;
	}

	// move scrollbar
	scrollbarTop = 32+(416-scrollbarHeight)*
		textYPosition/((lines*32)-(15*32));

	// draw text
	setOrtho();
	font->drawString(surface, 0, -textYPosition, text);

	// draw scrollbar
	drawScrollbar();

	// draw dude
	if (textYPosition > 3650)
	{
		dudey = 4050-textYPosition;
		dude->bind();
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0, 0.03); glVertex2i(325, dudey);
			glTexCoord2f(0.0, 0.03); glVertex2i(-187, dudey);
			glTexCoord2f(0.0, 0.97); glVertex2i(-197, dudey+479);
			glTexCoord2f(1.0, 0.97); glVertex2i(325, dudey+479);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, GL_NONE);
	}
	unsetOrtho();

	// fade in scene
	if (getTime() < 1000) {
		setOrtho();
		glBindTexture(GL_TEXTURE_2D, GL_NONE);
		glColor4ub(0, 0, 0, 255-(unsigned char)(getTime()/(1000.0/255.0)));
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
}

int About::run()
{
	// run until esc is pressed or the window is closed while registering all
	// SDL_MOUSEBUTTONDOWN events
	while (true) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_WHEELUP) {
						if (autoScroll)
							autoScroll = false;

						// scroll up 16 pixels unless we're already at the top
						(textYPosition > 0) ?
							textYPosition -= 16 :
							textYPosition = 0;

					}
					else if (event.button.button == SDL_BUTTON_WHEELDOWN) {
						if (autoScroll)
							autoScroll = false;

						// scroll down 16 pixels unless we're already at the
						// bottom
						(textYPosition < (lines-15)*32) ?
							textYPosition += 16 :
							textYPosition = (lines-15)*32;

					}
					else if (event.button.button == SDL_BUTTON_LEFT) {
						// user clicked on scrollbar
						if (event.motion.x > 608) {
							// turn off autoscrolling
							autoScroll = false;

							// up-arrow clicked
							if (event.motion.y <= 32) {
								upArrowClicked = getTime();
								tempYPos = textYPosition;
							}
							// down-arrow clicked
							else if (event.motion.y >= 448) {
								downArrowClicked = getTime();
								tempYPos = textYPosition;
							}
							// scrollbar handle clicked
							else if (event.motion.y >= scrollbarTop &&
									event.motion.y <=
									scrollbarTop+scrollbarHeight) {
								SDL_GetMouseState(NULL,
										&scrollbarHandleClicked);
								tempYPos = textYPosition;
							}
							// scrollbar (not handle) clicked
							else
								scrollBarClicked = getTime();
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					scrollbarHandleClicked = 0;
					if (upArrowClicked) {
						if (getTime()-upArrowClicked < 200)
							textYPosition -= 32;

						upArrowClicked = 0;
					}
					if (downArrowClicked) {
						if (getTime()-downArrowClicked < 200)
							textYPosition += 32;

						downArrowClicked = 0;
					}

					// set the text y-position to a sane value
					if (textYPosition < 0)
						textYPosition = 0;
					else if (textYPosition > (lines-15)*32)
						textYPosition = (lines-15)*32;

					// reset
					scrollBarClicked = 0;

					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = getTime();
							break;
						case SDLK_DOWN:
							autoScroll = false;
							textYPosition += 16;
							break;
						case SDLK_UP:
							autoScroll = false;
							textYPosition -= 16;
							break;
						case SDLK_PAGEDOWN:
						case SDLK_SPACE:
							autoScroll = false;
							textYPosition += 
								(((lines-15)*32)/(416-scrollbarHeight))*
								scrollbarHeight;
							break;
						case SDLK_PAGEUP:
						case SDLK_BACKSPACE:
							autoScroll = false;
							textYPosition -= 
								(((lines-15)*32)/(416-scrollbarHeight))*
								scrollbarHeight;
							break;
						default:
							break;
					}

					// set the text y-position to a sane value
					if (textYPosition < 0)
						textYPosition = 0;
					else if (textYPosition > 32*(lines-15))
						textYPosition = 32*(lines-15);

					break;
				case SDL_QUIT:
					done = getTime();
					break;
				default: break;
			}
		} // finished polling events

		// check if arrows are being pressed, or the scrollbars handle is
		// being dragged and if so, take action :)
		{
			if (upArrowClicked) {
				if (getTime()-upArrowClicked >= 200) {
					textYPosition = tempYPos -
						(getTime()-upArrowClicked-200)/10;
					if (textYPosition < 0)
						textYPosition = 0;
				}
			}
			else if (downArrowClicked) {
				if (getTime()-downArrowClicked >= 200) {
					textYPosition = tempYPos +
						(getTime()-downArrowClicked-200)/10;
					if (textYPosition > (lines-15)*32)
						textYPosition = (lines-15)*32;
				}
			}
			else if (scrollbarHandleClicked) {
				// get the mouse pointers y-coordinate
				int y;
				SDL_GetMouseState(NULL, &y);

				if (y > 32 && y < 448 && textYPosition >= 0 &&
						textYPosition < 32*lines)
				{
					textYPosition = tempYPos +
						(int)((y-scrollbarHandleClicked)*
							  ((lines-15)*32)/(416-scrollbarHeight));

					// set the text y-position to a sane value
					if (textYPosition < 0)
						textYPosition = 0;
					else if (textYPosition > 32*(lines-15))
						textYPosition = 32*(lines-15);
				}
			}
		}
		render();

		if (done > 0 && getTime() - done > 500)
			break;
	}

	// scene finished, return success
	return 0;
}
