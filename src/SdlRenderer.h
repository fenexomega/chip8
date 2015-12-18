#ifndef SDLRENDERER_H
#define SDLRENDERER_H
#include "interfaces/iRenderer.h"


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;



class SdlRenderer final : public iRenderer
{

public:
	SdlRenderer();

	bool Initialize(const int width,const int height) noexcept;

	void Render(const uint32_t *gfx) noexcept;
	
	void Dispose() noexcept;

	bool IsWindowClosed() const noexcept;

	~SdlRenderer();
private:
	SDL_Window *m_window;
	SDL_Renderer *m_rend;
	SDL_Texture *m_texture;
	bool m_needToDispose;
	int m_pitch;
	

};





#endif
