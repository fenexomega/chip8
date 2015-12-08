#ifndef SDLRENDERER_H
#define SDLRENDERER_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
#include "interfaces/iRenderer.h"


class SdlRenderer : public iRenderer
{

public:
	SdlRenderer();

	bool Initialize(const int width,const int height) noexcept;

	void Render(const void *gfx) noexcept;
	
	void Dispose() noexcept;

	bool IsWindowClosed() noexcept;

	~SdlRenderer();
private:
	inline bool CheckWindowState() noexcept;
	SDL_Window *m_window;
	SDL_Renderer *m_rend;
	SDL_Texture *m_texture;
	bool m_needToDispose;
	int m_pitch;
	

};





#endif
