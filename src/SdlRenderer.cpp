#include <iostream>
#include "SdlRenderer.h"





SdlRenderer::SdlRenderer()
{
	window_ = nullptr;
	rend_ = nullptr;
	m_userWannaClose = false;
}

bool SdlRenderer::IsWindowClosed()
{
	return m_userWannaClose;
}

bool SdlRenderer::Initialize()
{


	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG("Couldn't start the application: " << SDL_GetError());
		return false;
	}
	

	window_ = SDL_CreateWindow("Chip8 Emulator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_RESIZABLE);
	rend_ = SDL_CreateRenderer(window_,-1,SDL_RENDERER_ACCELERATED);

	if(window_ == nullptr || rend_ == nullptr)
	{

		LOG("Couldn't allocate SDL_Window or SDL_Renderer.");
		return false;
	}
	

	SDL_SetRenderDrawBlendMode(rend_,SDL_BLENDMODE_BLEND);


	return true;
}


void SdlRenderer::Render(const unsigned char *fgx)
{


    SDL_SetRenderDrawColor(rend_,0,0,0,1);
    SDL_RenderClear(rend_);
    // Renderizar Coisas do Emulador

    SDL_RenderPresent(rend_);

    UpdateWindowState();

}


void SdlRenderer::UpdateWindowState()
{
	static SDL_Event event;
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT)
	{
		m_userWannaClose = true;
	}
}

void SdlRenderer::Dispose()
{
	SDL_DestroyRenderer(rend_);
	SDL_DestroyWindow(window_);
	rend_ = nullptr;
	window_ = nullptr;
}



SdlRenderer::~SdlRenderer()
{
	if( rend_ != nullptr || window_  != nullptr )
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
