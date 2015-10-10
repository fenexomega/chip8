#include "SdlRenderer.h"

constexpr int fps { 1000/ 60 };




SdlRenderer::SdlRenderer() :
	m_window (nullptr), m_rend (nullptr), m_texture (nullptr),  m_userWannaClose (false)
{
	LOG("Creating SdlRenderer object...");
}



bool SdlRenderer::Initialize(const int width,const int height) noexcept
{


	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG("Couldn't start the application: " << SDL_GetError());
		return false;
	}
	
	m_pitch = width * 4;
	
	m_window = SDL_CreateWindow("Chip8 Emulator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width * 4 , height * 6 , SDL_WINDOW_RESIZABLE);

	m_rend = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
	
	m_texture = SDL_CreateTexture(m_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);


	if(m_window == nullptr || m_rend == nullptr || m_texture == nullptr)
	{

		LOG("Couldn't allocate SDL_Window, SDL_Renderer or SDL_Texture: Error: " << SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);

	SDL_RenderClear(m_rend);

	SDL_RenderPresent(m_rend);
		
	return true;
}







void SdlRenderer::Render(const void *gfx) noexcept
{
	
	SDL_UpdateTexture(m_texture, nullptr, gfx, m_pitch);
	SDL_RenderCopy(m_rend, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_rend);

	SDL_Delay(fps);
}







void SdlRenderer::UpdateWindowState() noexcept
{
	static SDL_Event event;
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT)
		m_userWannaClose = true;
	
}



bool SdlRenderer::IsWindowClosed() noexcept
{
	UpdateWindowState();
	return m_userWannaClose;
}



void SdlRenderer::Dispose() noexcept
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_rend);
	SDL_DestroyWindow(m_window);
	m_texture = nullptr;
	m_rend = nullptr;
	m_window = nullptr;
}




SdlRenderer::~SdlRenderer()
{

	LOG("Destroying SdlRenderer object...");
	if( m_rend != nullptr || m_window  != nullptr  || m_texture != nullptr)
		this->Dispose();

	SDL_Quit();
}

