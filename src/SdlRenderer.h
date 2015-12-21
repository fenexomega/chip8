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

	bool Initialize(const int width,const int height, WindowMode mode) noexcept override; 

	void Render(const uint32_t *gfx) noexcept override;
	
	bool IsWindowClosed() const noexcept override;

	bool SetWindowPosition(const unsigned x, const unsigned y) noexcept override;

	bool SetWindowSize(const unsigned width, const unsigned height) noexcept override;

	void Dispose() noexcept override;

	~SdlRenderer();
private:
	SDL_Window *m_window;
	SDL_Renderer *m_rend;
	SDL_Texture *m_texture;
	bool m_needToDispose;
	int m_pitch;
	

};





#endif
