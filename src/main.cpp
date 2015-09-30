#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#undef main
#include "Chip8.h"

int main(int argc, char **argv)
{
		

	if(argc < 1 )
	{
		std::cout << "No game to load, exiting." << std::endl; 
		return 0;
	}

	std::unique_ptr<Chip8> myChip8(new Chip8()); // save stack memory using smart pointers.

	if (!myChip8->initSystems())
		return 1;

	if(!myChip8->loadRom("MAZE"))
		return 1;
	




	while(!myChip8->wantToExit())
	{
	    // Emulate one cycle
		myChip8->executeOpcode(); // test phase.
		//myChip8->drawGraphics();
	}
	
	myChip8->dispose();
	
	return 0;
}

