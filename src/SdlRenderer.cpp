#include <limits>
#include <SDL2/SDL.h>
#include "SdlRenderer.h"
#include "utility/log.h"






SdlRenderer::SdlRenderer() 
	:	m_window (nullptr), m_rend (nullptr), m_texture (nullptr), m_needToDispose(false)
{
	LOG("Creating SdlRenderer object...");
}


void SdlRenderer::Dispose() noexcept
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_rend);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	m_needToDispose = false;
}




SdlRenderer::~SdlRenderer()
{

	LOG("Destroying SdlRenderer object...");
	if(m_needToDispose)
		this->Dispose();

	
}


bool SdlRenderer::Initialize(const int width,const int height, WindowMode mode) noexcept
{

	
	if(m_needToDispose)
		this->Dispose();
	
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		LOG("Couldn't start the application: " << SDL_GetError());
		return false;
	}
	
	m_pitch = width * 4;
	
	m_window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 4, height * 6,
				    (mode == WindowMode::BORDLESS) ? SDL_WINDOW_BORDERLESS : SDL_WINDOW_RESIZABLE);
	

	if(m_window == nullptr)
	{
		LOG("Couldn't allocate SDL_Window. Error: " << SDL_GetError());
		return false;
	}

	m_rend = SDL_CreateRenderer(m_window,-1, SDL_RENDERER_ACCELERATED);


	if(m_rend == nullptr)
	{
		LOG("Couldn't allocate SDL_Renderer. Error: " << SDL_GetError());
		SDL_DestroyWindow(m_window);
		return false;
	}

	
	m_texture = SDL_CreateTexture(m_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);


	if(m_texture == nullptr)
	{

		LOG("Couldn't allocate SDL_Texture. Error: " << SDL_GetError());
		SDL_DestroyRenderer(m_rend);
		SDL_DestroyWindow(m_window);
		return false;
	}

	SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);
	SDL_RenderClear(m_rend);
	SDL_RenderPresent(m_rend);

	m_needToDispose = true;
	return true;
}



void SdlRenderer::Render(const uint32_t *gfx) noexcept
{
	
	SDL_UpdateTexture(m_texture, nullptr, gfx, m_pitch);
	SDL_RenderCopy(m_rend, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_rend);
	SDL_Delay(FPS);
}




bool SdlRenderer::IsWindowClosed() const noexcept
{
	static SDL_Event event;
	if(SDL_PollEvent(&event))
		return (event.type == SDL_QUIT);
	else
		return false;
}

bool SdlRenderer::SetWindowPosition(const unsigned x, const unsigned y) noexcept
{
	SDL_DisplayMode desktopDisplay;

	if(SDL_GetDesktopDisplayMode(0, &desktopDisplay) != 0){
		LOGerr("Failed to get desktop display mode: " << SDL_GetError());
		return false;
	}

	else if(x > static_cast<unsigned>(desktopDisplay.h) || y > static_cast<unsigned>(desktopDisplay.w))
		return false;

	SDL_SetWindowPosition(m_window, x, y);
	return true;
}



bool SdlRenderer::SetWindowSize(const unsigned width, const unsigned height) noexcept
{

	SDL_SetWindowSize(m_window, width, height);
	return true;
}



