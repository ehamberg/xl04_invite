#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Music
{
	public:
		Music(const char *filename);
		~Music();

		void fadeIn();
		void fadeIn(int milliSeconds);
		void fadeOut();
		void fadeOut(int milliSeconds);

	private:
		Mix_Music *music;
		int volume;
};

#endif
