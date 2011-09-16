#include <iostream>
#include "Music.h"

using std::cerr;
using std::endl;

Music::Music(const char *filename)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		cerr << "Couldn't initialize SDL_mixer: " << Mix_GetError() << endl;

	if (!(music = Mix_LoadMUS(filename)))
		cerr << "Couldn't load music: " << Mix_GetError() << endl;

}

void Music::fadeIn()
{
	if (Mix_FadeInMusic(music, 1, 1000) == -1)
		cerr << "Couldn't play music: " << Mix_GetError() << endl;
}

void Music::fadeIn(int milliSeconds)
{
	if (Mix_FadeInMusic(music, 1, milliSeconds) == -1)
		cerr << "Couldn't play music: " << Mix_GetError() << endl;
}

void Music::fadeOut()
{
	Mix_FadeOutMusic(1000);
}

void Music::fadeOut(int milliSeconds = 1000)
{
	Mix_FadeOutMusic(milliSeconds);
}

Music::~Music()
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}
