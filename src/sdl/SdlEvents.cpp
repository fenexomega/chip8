#include <ctime>
#include <SDL2/SDL_events.h>
#include "../utility/timer.h"

SDL_Event g_sdlEvent;
void UpdateSdlEvents()
{
	static Timer eventTimer(1_sec / 256);
	if( eventTimer.Finished() ) {
		SDL_PollEvent(&g_sdlEvent);
		eventTimer.Start();
	}
}
