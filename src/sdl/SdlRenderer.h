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

	bool Initialize(const int width, const int height) override; 
	void Dispose() noexcept override;

	bool IsWinClosed() const override;
	WindowMode GetMode() const override;
	void RenderBuffer() override;

	bool UpdateEvents() override;	
	void Render(const uint32_t *gfx) override;
	void SetBuffer(const uint32_t *gfx) override;
	bool SetWinPosition(const unsigned x, const unsigned y) override;
	bool SetWinSize(const unsigned width, const unsigned height) override;

	virtual void SetWinCloseCallback(WinCloseCallback callback, void* arg) override;
	virtual void SetWinResizeCallback(WinResizeCallback callback, void* arg) override;
private:
	SDL_Window* m_window;
	SDL_Renderer* m_rend;
	SDL_Texture* m_texture;
	const uint32_t* m_buffer;
	bool m_needToDispose;
	int m_pitch;
	WindowMode m_windowMode;
	WinCloseCallback m_closeClbk;
	WinResizeCallback m_resizeClbk;
	void* m_closeClbkArg;
	void* m_resizeClbkArg;


};





#endif
