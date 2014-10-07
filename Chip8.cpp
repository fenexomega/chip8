#include "Chip8.h"


bool Chip8::getDrawFlag() const
{
    return drawFlag;
}

void Chip8::setDrawFlag(bool value)
{
    drawFlag = value;
}

void Chip8::Dispose()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Chip8::WantToExit()
{
    return event.type == SDL_QUIT;
}

void Chip8::Update()
{
    SDL_PollEvent(&event);
}

bool Chip8::InitGraphics()
{
    drawFlag = true;
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        dPrint("Couldn't start the application: " << SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Chip8 Emulator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_RESIZABLE);
    rend = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(window == NULL || rend == NULL)
        return false;
    SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);

    return true;
}

bool Chip8::InitSound()
{

}

bool Chip8::InitInput()
{

}

Chip8::Chip8()
{
}

bool Chip8::InitSystems()
{
    pc     = 0x200;  // Program counter starts at 0x200
    opcode = 0;      // Reset current opcode
    I      = 0;      // Reset index register
    sp     = 0;      // Reset stack pointer

    // Clear display
    // Clear stack
    // Clear registers V0-VF
    // Clear memory
    // Load fontset
    for(int i = 0; i < 80; ++i)
        //        memory[i] = chip8_fontset[i];

        return InitGraphics() & InitSound() & InitInput();

}

void Chip8::EmulateCycle()
{

}

void Chip8::drawGraphics()
{
    Update();
    SDL_SetRenderDrawColor(rend,0,0,0,1);
    SDL_RenderClear(rend);
    // Renderizar Coisas do Emulador

    SDL_RenderPresent(rend);
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
//        cout << memoryChucks.data() << endl;
    }

}
