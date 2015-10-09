#include "Chip8.h"
int main(int argc, char **argv)
{
	
	if (argc < 2)
	{
		std::cout << "No game to load, exiting." << std::endl;
		return 0;
	}
		
	Chip8 *myChip8 = new Chip8();
	

	if (!myChip8->initSystems())
		return 1;

	if (!myChip8->loadRom(argv[1]))
		return 1;

	while (!myChip8->wantToExit())
	{

		myChip8->updateCycle();
		myChip8->executeInstruction();
		if (myChip8->getDrawFlag())
			myChip8->drawGraphics();
	
	}

	// CLEAN
	myChip8->dispose();
	delete myChip8;

	
	//std::cin.ignore(1); //for LOG read

	
	return 0;
}

