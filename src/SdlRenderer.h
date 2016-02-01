#ifndef SDLRENDERER_H
#define SDLRENDERER_H
#include "interfaces/iRenderer.h"


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
union SDL_Event;


class SdlRenderer final : public iRenderer
{

public:
	SdlRenderer();

	bool Initialize(const int width,const int height, WindowMode mode) override; 

	void Render(const uint32_t *gfx) override;
	
	bool IsWindowClosed() const override;

	bool SetWindowPosition(const unsigned x, const unsigned y) override;

	bool SetWindowSize(const unsigned width, const unsigned height) override;

	void Dispose() noexcept override;

	~SdlRenderer();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_rend;
	SDL_Texture* m_texture;
	SDL_Event* m_event;
	bool m_needToDispose;
	int m_pitch;
	

};





#endif
