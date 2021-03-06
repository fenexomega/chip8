#include <memory>
#include <Chip8/Chip8.h>
#include <Chip8/Utility/log.h>
#include <Chip8/SDL/SdlRenderer.h>
#include <Chip8/SDL/SdlInput.h>



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

	if(!chip8Cpu->initialize(new(std::nothrow) SdlRenderer(), new(std::nothrow) SdlInput()))
		return 1;

	else if(!chip8Cpu->loadRom(argv[1]))
		return 1;


	chip8Cpu->setInstrPerSec(358); /* 358hz */
	chip8Cpu->setFramesPerSec(60);
	
	while (!chip8Cpu->getExitFlag())
	{
		chip8Cpu->haltForNextFlag();

		chip8Cpu->updateSystemState();

		if (chip8Cpu->getInstrFlag())
			chip8Cpu->executeInstruction();

		if (chip8Cpu->getDrawFlag())
			chip8Cpu->drawGraphics();
	}

	/*  debug */
	// std::atexit([]() {std::cin.ignore(); });
	return 0;
}

