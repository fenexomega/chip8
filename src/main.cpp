#include <memory>
#include "utility/log.h"
#include "Chip8.h"


int main(int argc, char **argv)
{
	if (argc < 2) {
		LOGerr("No game to load, exiting...");
		return 0;
	}
	
	auto uniqueChip8Cpu = std::unique_ptr<Chip8>(new(std::nothrow) Chip8());
	
	if (!uniqueChip8Cpu) {
		LOGerr("Cannot allocate space for Chip8 object");
		return 1;
	}

	Chip8 *chip8Cpu = uniqueChip8Cpu.get();


	if(!chip8Cpu->initialize())
		return 1;

	else if(!chip8Cpu->loadRom(argv[1]))
		return 1;


	while(!chip8Cpu->wantToExit())
	{
		chip8Cpu->updateSystemState();
		chip8Cpu->executeInstruction();
		chip8Cpu->drawGraphics();
	}

	/*  debug */
	std::atexit([]() {std::cin.ignore(); });
	return 0;
}

