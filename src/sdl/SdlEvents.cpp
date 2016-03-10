#include <ctime>
#include <SDL2/SDL_events.h>

SDL_Event g_sdlEvent;
void UpdateSdlEvents()
{
	static std::clock_t updateTime = std::clock();
	if ((std::clock() - updateTime) > CLOCKS_PER_SEC / 512) {
		SDL_PollEvent(&g_sdlEvent);
		updateTime = std::clock();
	}
}