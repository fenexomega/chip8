#ifndef SDLRENDERER_H
#define SDLRENDERER_H
#include "../interfaces/iRenderer.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class SdlRenderer final : public iRenderer
{

public:
	SdlRenderer();
	~SdlRenderer();

	bool Initialize(const int width,const int height, WindowMode mode) override; 
	bool IsWindowClosed() const override;
	WindowMode GetMode() const override;
	void RenderLastBuffer() const override;

	void UpdateEvents() override;	
	void Render(const uint32_t *gfx) override;
	void SetBuffer(const uint32_t *gfx) override;
	bool SetWindowPosition(const unsigned x, const unsigned y) override;
	bool SetWindowSize(const unsigned width, const unsigned height) override;
	void Dispose() noexcept override;
private:
	SDL_Window* m_window;
	SDL_Renderer* m_rend;
	SDL_Texture* m_texture;
	const uint32_t* m_buffer;
	WindowMode m_windowMode;
	bool m_needToDispose;
	int m_pitch;
};





#endif
