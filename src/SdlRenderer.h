#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"


class SdlRenderer : public iRenderer
{

public:
	SdlRenderer();

	bool Initialize(const int width,const int height) noexcept;

    void Render(const unsigned int *gfx) noexcept;
    
	void Dispose() noexcept;

	bool IsWindowClosed() noexcept;

	~SdlRenderer();
private:
	void UpdateWindowState() noexcept;

	SDL_Window *m_window;
	SDL_Renderer *m_rend;
	SDL_Texture *m_texture;
	
	bool m_userWannaClose;

	

};





#endif
