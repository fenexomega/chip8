#include <memory>
#include "utility/log.h"
#include "Chip8.h"


int main(int argc, char **argv)
{

	if (argc < 2) {
		LOGerr("No game to load, exiting...");
		return 0;
	}
	
	auto uniqueChip8Cpu = std::make_unique<Chip8>();

	Chip8 *chip8Cpu = uniqueChip8Cpu.get();


	if(!chip8Cpu->initialize())
		return 1;

	else if(!chip8Cpu->loadRom(argv[1]))
		return 1;


	while(!chip8Cpu->wantToExit())
	{

		chip8Cpu->updateCpuState();
		chip8Cpu->executeInstruction();

		if(chip8Cpu->getDrawFlag())
			chip8Cpu->drawGraphics();
		
	}


	return 0;
}

