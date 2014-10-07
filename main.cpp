#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "Chip8.h"

using namespace std;

Chip8 myChip8;

int main(int argc, char **argv)
{
    myChip8.InitSystems();

    myChip8.loadGame(argv[1]);

    while(!myChip8.WantToExit())
    {
        // Emulate one cycle
        myChip8.EmulateCycle();
        SDL_Delay(1000/60);
        // If the draw flag is set, update the screen
        if(myChip8.getDrawFlag())
            myChip8.drawGraphics();

        // Store key press state (Press and Release)
        myChip8.setKeys();
    }

    myChip8.Dispose();
    return 0;
}

