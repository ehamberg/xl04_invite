#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#define SCENE_MAIN_MENU 100
#define SCENE_EXIT 200

#include <SDL/SDL.h>

class Scene
{
	public:
		Scene();
		virtual ~Scene();
		
		int getTime();
		virtual void init();
		virtual int run();
		virtual void drawBackground();
		virtual void render();

	protected:
		SDL_Surface *surface;
		SDL_Event event;
		bool done;
		unsigned int startTime;

		void setOrtho();
		void setOrtho(int left, int right, int bottom, int top);
		void unsetOrtho();
};

#endif
