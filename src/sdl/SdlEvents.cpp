#include <ctime>
#include <SDL2/SDL_events.h>
#include "../utility/timer.h"
SDL_Event g_sdlEvent;
void UpdateSdlEvents()
{
	
	SDL_PollEvent(&g_sdlEvent);
}
