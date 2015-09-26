#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"




class SdlRenderer : public iRenderer
{

public:
	SdlRenderer()
	{
		window_ = nullptr;
		rend_ = nullptr;
	}
	
	bool initialize()
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




	void dispose()
	{
		SDL_DestroyRenderer(rend_);
    	SDL_DestroyWindow(window_);
   	 	rend_ = nullptr;
   	 	window_ = nullptr;
	}





	~SdlRenderer()
	{
		if( rend_ != nullptr || window_  != nullptr )
			this->dispose();
	
		SDL_Quit();
	}




private:
	SDL_Window *window_;
	SDL_Renderer *rend_;
	

};





// Test

int main()
{
	SdlRenderer renderer_;

	if(!renderer_.initialize())
		return 1;

	SDL_Delay( 5000 );
	renderer_.dispose();
	SDL_Delay( 3000 );
	renderer_.dispose();
	SDL_Delay( 3000 );

}









#endif
