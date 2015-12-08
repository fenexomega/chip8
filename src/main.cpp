#include "Chip8.h"


int main(int argc, char **argv)
{

	
	if (argc < 0)
	{
		std::cout << "No game to load, exiting." << std::endl;
		return 0;
	}
	

	Chip8 *myChip8 = new(std::nothrow) Chip8();
	
	if(myChip8 == nullptr)
	{
		LOGerr("can't allocate memory for Chip8: ("<< sizeof(Chip8) << " Bytes), or memory problem.");
		return 1;
	}
	
	if(!myChip8->initialize())
	{
		myChip8->dispose();
		delete myChip8;
		return 1;
	}
	
	if(!myChip8->loadRom("BRIX"))
	{
		myChip8->dispose();
		delete myChip8;
		return 1;
	}
	
	
	while(!myChip8->wantToExit())
	{
	
		myChip8->updateCpuState();
		myChip8->executeInstruction();
	
		if(myChip8->getDrawFlag())
			myChip8->drawGraphics();
	
	}
	
	
	myChip8->dispose();
	delete myChip8;
	
	
	//std::cin.ignore(1); //for LOG read
	
	
	return 0;
}





void clean_resources(Chip8 *ptr){
	delete ptr;
}