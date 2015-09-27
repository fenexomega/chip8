#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"




class SdlRenderer : public iRenderer
{

public:
	SdlRenderer();

	bool initialize();
	void render();
	void dispose();

	~SdlRenderer();


private:
	SDL_Window *window_;
	SDL_Renderer *rend_;
	

};





#endif
