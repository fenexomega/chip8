#include "utility/log.h"
#include "Chip8.h"

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		LOGerr("No game to load, exiting...");
		return 0;
	}

	
	Chip8 *chip8Cpu = new(std::nothrow) Chip8();
	
	if(chip8Cpu == nullptr)
	{
		LOGerr("failed to allocate the chip8 object...");
		return 1;
	}
	
	if(!chip8Cpu->initialize())
	{
		chip8Cpu->dispose();
		delete chip8Cpu;
		return 1;
	}

	if(!chip8Cpu->loadRom(argv[1]))
	{
		chip8Cpu->dispose();
		delete chip8Cpu;
		return 1;
	}
	

	while(!chip8Cpu->wantToExit())
	{
	
	
		chip8Cpu->updateCpuState();
		chip8Cpu->executeInstruction();
	
		if(chip8Cpu->getDrawFlag())
			chip8Cpu->drawGraphics();
	}
	
	chip8Cpu->dispose();
	delete chip8Cpu;
	
	
	return 0;
}

