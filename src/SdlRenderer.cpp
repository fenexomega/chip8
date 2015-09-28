#include <iostream>
#include "SdlRenderer.h"





SdlRenderer::SdlRenderer()
{
	m_window = nullptr;
	m_rend = nullptr;
	m_userWannaClose = false;
}







bool SdlRenderer::Initialize() noexcept
{


	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG("Couldn't start the application: " << SDL_GetError());
		return false;
	}
	

	m_window = SDL_CreateWindow("Chip8 Emulator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_RESIZABLE);
	m_rend = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);

	if(m_window == nullptr || m_rend == nullptr)
	{

		LOG("Couldn't allocate SDL_Window or SDL_Renderer.");
		return false;
	}
	

	SDL_SetRenderDrawBlendMode(m_rend,SDL_BLENDMODE_BLEND);


	return true;
}







void SdlRenderer::Render(const unsigned char *fgx) noexcept
{


    SDL_SetRenderDrawColor(m_rend,0,0,0,1);
    SDL_RenderClear(m_rend);
    // Renderizar Coisas do Emulador

    SDL_RenderPresent(m_rend);

    UpdateWindowState();

}








void SdlRenderer::UpdateWindowState() noexcept
{
	static SDL_Event event;
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT)
	{
		m_userWannaClose = true;
	}
}






bool SdlRenderer::IsWindowClosed() noexcept
{
	return m_userWannaClose;
}







void SdlRenderer::Dispose() noexcept
{
	SDL_DestroyRenderer(m_rend);
	SDL_DestroyWindow(m_window);
	m_rend = nullptr;
	m_window = nullptr;
}







SdlRenderer::~SdlRenderer()
{
	if( m_rend != nullptr || m_window  != nullptr )
		this->Dispose();

	SDL_Quit();
}






/* SdlRender Tests
int main()
{
	iRenderer *renderer_ = new SdlRenderer;

	renderer_->initialize();
	SDL_Delay(5000);
	renderer_->dispose();
	SDL_Delay(3000);
	renderer_->dispose();
	SDL_Delay(3000);
	renderer_->initialize();
	SDL_Delay(5000);
	renderer_->dispose();
	SDL_Delay(3000);


	

}
*/
