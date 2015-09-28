#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"




class SdlRenderer : public iRenderer
{

public:
	SdlRenderer();

	bool Initialize() noexcept ;
    void Render(const unsigned char *fgx) noexcept;
	void Dispose() noexcept ;
	bool IsWindowClosed() noexcept ;

	~SdlRenderer();
private:
	void UpdateWindowState() noexcept;

	SDL_Window *m_window;
	SDL_Renderer *m_rend;
	bool m_userWannaClose;

	

};





#endif
