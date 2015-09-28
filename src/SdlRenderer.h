#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"




class SdlRenderer : public iRenderer
{

public:
	SdlRenderer();

	bool Initialize();
	void Render();
	void Dispose();
	bool IsWindowClosed();

	~SdlRenderer();


private:
	SDL_Window *window_;
	SDL_Renderer *rend_;
	bool m_userWannaClose;

	void UpdateWindowState();

	

};





#endif
