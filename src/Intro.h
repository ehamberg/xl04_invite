#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include "Scene.h"
#include "Texture.h"
#include "Particle.h"
#include "Scroller.h"

class Intro : public Scene
{
	public:
		Intro(SDL_Surface *sdlsurf);
		~Intro();

		int run();
		void render();
	private:
		int done;
		float rotation;

		Scroller* scroller;
		Particle* p1;
		Particle* p2;
		Texture* xenoxLogo;

		GLuint blurtex;
		GLuint temptex;
};

#endif
