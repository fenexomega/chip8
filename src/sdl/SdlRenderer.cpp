#include <SDL2/SDL.h>
#include "SdlRenderer.h"
#include "../utility/log.h"



SdlRenderer::SdlRenderer() :
	m_window (nullptr), 
	m_rend (nullptr), 
	m_texture (nullptr),
	m_needToDispose(false)
{
	LOG("Creating SdlRenderer object...");
}


void SdlRenderer::Dispose() noexcept
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_rend);
	SDL_DestroyWindow(m_window);
	m_needToDispose = false;
}


SdlRenderer::~SdlRenderer()
{
	LOG("Destroying SdlRenderer object...");
	if(m_needToDispose)
		this->Dispose();
	
	SDL_Quit();	
}


bool SdlRenderer::Initialize(const int width, const int height, WindowMode mode)
{

	
	if(m_needToDispose)
		this->Dispose();
	
	if( SDL_Init(SDL_INIT_VIDEO) != SDL_FALSE ) {
		LOGerr("Couldn't start the application: " << SDL_GetError());
		return false;
	}

	
	m_pitch = width * 4;
	
	
	m_window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 4, height * 6,
				    (mode == WindowMode::BORDLESS) ? SDL_WINDOW_BORDERLESS : SDL_WINDOW_RESIZABLE);
	
	m_windowMode = mode;

	if(m_window == nullptr) {
		LOGerr("Couldn't allocate SDL_Window. Error: " << SDL_GetError());
		return false;
	}

	m_rend = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);


	if(m_rend == nullptr)
	{
		LOGerr("Couldn't allocate SDL_Renderer. Error: " << SDL_GetError());
		SDL_DestroyWindow(m_window);
		return false;
	}

	
	m_texture = SDL_CreateTexture(m_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);


	if(m_texture == nullptr)
	{
		LOGerr("Couldn't allocate SDL_Texture. Error: " << SDL_GetError());
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


void SdlRenderer::UpdateEvents()
{
	UpdateSdlEvents();
	if (g_sdlEvent.type == SDL_WINDOWEVENT
		&& g_sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED
		|| g_sdlEvent.window.event == SDL_WINDOWEVENT_RESTORED)
		SDL_RenderPresent(m_rend);
}


void SdlRenderer::Render(const uint32_t *gfx)
{
	SDL_UpdateTexture(m_texture, nullptr, gfx, m_pitch);
	SDL_RenderCopy(m_rend, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_rend);
	SDL_Delay(FPS);
}


bool SdlRenderer::IsWindowClosed() const
{
	return g_sdlEvent.type == SDL_QUIT;
}


WindowMode SdlRenderer::GetMode() const 
{
	return m_windowMode;
}


bool SdlRenderer::SetWindowPosition(const unsigned x, const unsigned y)
{
	SDL_DisplayMode desktopDisplay;

	if ( SDL_GetDesktopDisplayMode(0, &desktopDisplay) != 0 ) {
		LOGerr("Failed to get desktop display mode: " << SDL_GetError());
		return false;
	}

	else if( x > static_cast<unsigned>(desktopDisplay.h) 
		|| y > static_cast<unsigned>(desktopDisplay.w)) 
	{
		
		LOGerr("SetWindowPosition: position is offscreen");
		return false;
	}

	SDL_SetWindowPosition(m_window, x, y);
	return true;
}





bool SdlRenderer::SetWindowSize(const unsigned width, const unsigned height)
{
	SDL_DisplayMode desktopDisplay;
	if ( SDL_GetDesktopDisplayMode(0, &desktopDisplay) != 0 ) {		
		LOGerr("Failed to get desktop display mode: " << SDL_GetError());
		return false;
	}

	else if( width > static_cast<unsigned>(desktopDisplay.w) ||
			height > static_cast<unsigned>(desktopDisplay.h))
	{
		LOGerr("SetWindowSize: size is too large");
		return false;
	}

	
	SDL_SetWindowSize(m_window, width, height);
	m_pitch = width * 4;
	return true;
}



