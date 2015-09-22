#include "Chip8.h"



Chip8::Chip8()
{




}

bool Chip8::getDrawFlag() const
{
    return drawFlag_;
}

void Chip8::setDrawFlag(bool value)
{
    drawFlag_ = value;
}

void Chip8::dispose()
{
    SDL_DestroyRenderer(screen_->rend);
    SDL_DestroyWindow(screen_->window);
    SDL_Quit();
}

bool Chip8::wantToExit()
{
    return sdl_->event.type == SDL_QUIT;
}

void Chip8::update()
{
    SDL_PollEvent(&sdl_->event);
}

bool Chip8::initGraphics()
{
    drawFlag_ = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        dPrint("Couldn't start the application: " << SDL_GetError());
        return false;
    }
    sdl_->window_ = SDL_CreateWindow("Chip8 Emulator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_RESIZABLE);
    sdl_->rend_ = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    if(window == NULL || rend == NULL)
        return false;
    
    SDL_SetRenderDrawBlendMode(sdl_->rend,SDL_BLENDMODE_BLEND);

    return true;
}

bool Chip8::initSound()
{

}

bool Chip8::initInput()
{

}

bool Chip8::initSystems()
{
    pc_     = 0x200;  // Program counter starts at 0x200
    opcode_ = 0;      // Reset current opcode
    I_      = 0;      // Reset index register
    sp_     = 0;      // Reset stack pointer

    // Clear display
    // Clear stack
    // Clear registers V0-VF
    // Clear memory
    // Load fontset
    for(int i = 0; i < 80; ++i)
        //        memory[i] = chip8_fontset[i];

        return initGraphics() & initSound() & initInput();

}

void Chip8::emulateCycle()
{
    SDL_Delay(1000/60);

}

void Chip8::drawGraphics()
{
    update();
    SDL_SetRenderDrawColor(sdl_->rend,0,0,0,1);
    SDL_RenderClear(sdl_->rend);
    // Renderizar Coisas do Emulador

    SDL_RenderPresent(sdl_->rend);
}

void Chip8::setKeys()
{

}

bool Chip8::loadGame(const char *gamename)
{
    dPrint("Loading " << gamename);
    ifstream Game(gamename,ios::in | ios::binary);
    //Para CONTINUAR https://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer
    if(!Game.is_open())
    {
        dPrint("Erro at opening game file. Exiting!");
        return false;
    }
    vector<char> memoryChucks(4000);
    if(Game.read(memoryChucks.data(),4000))
    {
        cout << memoryChucks.data() << endl;
    }

}





void Chip8::executeOpcode()
{
    opcode_ = (memory_[pc] & 0x0000)

    

}