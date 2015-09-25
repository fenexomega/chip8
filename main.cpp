#include <iostream>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>

#include "Chip8.h"

Chip8 myChip8;

int main(int argc, char **argv)
{

   if(!myChip8.loadGame(argv[1]))
       return 1;

    myChip8.initSystems();

    while(!myChip8.wantToExit())
    {
        // Emulate one cycle
        myChip8.emulateCycle();
        // If the draw flag is set, update the screen
        if(myChip8.getDrawFlag())
            myChip8.drawGraphics();

        // Store key press state (Press and Release)
        myChip8.setKeys();
    }

    myChip8.dispose();
    return 0;
}

