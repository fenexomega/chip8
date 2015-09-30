#include <ctime>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "SdlRenderer.h"
#include "Chip8.h"



Chip8::Chip8() : 
	renderer_ ( new SdlRenderer() )
{
	dPrint("Creating Chip8 object...");
}






bool Chip8::wantToExit()
{
	return renderer_->IsWindowClosed();
}


bool Chip8::initGraphics()
{
    if(!renderer_->Initialize(64,32))
		return false;

   
    return true;
}



bool Chip8::initSound()
{

    return true;
}



bool Chip8::initInput()
{

    return true;
}





bool Chip8::initSystems()
{

	dPrint("Initializing Chip8 Systems...");

	pc_     = 0x200;  // Program counter starts at 0x200
	opcode_ = 0;      // Reset current opcode
	I_      = 0;      // Reset index register
	sp_     = 0;      // Reset stack pointer
	soundTimer_ = 0;
	delayTimer_ = 0;
	drawFlag_ = false;

	std::srand(std::time(0));				// seed rand
	std::fill_n(gfx_,gfxResolution, 0);		// Clear display
	std::fill_n(stack_,STACK_MAX, 0);		// Clear stack
	std::fill_n(V_,16,0);					// Clear registers V0-VF
	std::fill_n(memory_,MEMORY_MAX,0); 		// Clear memory

	// Load fontset
	
	unsigned char chip8_fontset[80] 
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	std::copy_n(chip8_fontset, 80, memory_); // copy fontset to memory.

	return initGraphics() & initSound() & initInput();

}




bool Chip8::loadRom(const char *romFileName)
{
	dPrint("Loading " << romFileName);
	std::ifstream romFile(romFileName, std::ios::ate | std::ios::binary);


	if (!romFile.is_open())
	{
		dPrint("Error at opening ROM file. Exiting!");
		return false;
	}

	size_t romFileSize = romFile.tellg();
	romFile.seekg(0, romFile.beg);

	if (romFileSize > romMaxSize)
	{
		dPrint("Error, ROM size not compatible. Exiting!");
		return false;
	}

	std::copy(std::istreambuf_iterator<char>(romFile),
				std::istreambuf_iterator<char>(), memory_ + 0x200);

	romFile.close();

	dPrint("Load Done!");


	return true;
}




void Chip8::emulateCycle()
{

	SDL_Delay(1000/60);

}




void Chip8::drawGraphics()
{
	renderer_->Render(gfx_);
	drawFlag_ = false;
}




bool Chip8::getDrawFlag() const
{
	return drawFlag_;
}



void Chip8::waitKeyPress()
{
	while(!renderer_->IsWindowClosed());
}


void Chip8::dispose()
{
	if (renderer_ != nullptr)
	{
		renderer_->Dispose();
		delete renderer_;
	}
	renderer_ = nullptr;
}




Chip8::~Chip8()
{
	dPrint("Destroying Chip8 object...");
	
	if(renderer_ != nullptr)
		this->dispose();
}





void Chip8::executeOpcode()
{
	
	opcode_ = ( ( memory_[ pc_ ] << 8 ) | memory_ [ pc_ + 1 ] );
	
	pc_ += 2;

	// NNN: address
	// NN: 8 bit constant
	// N: 4 bit constant
	// X and Y: (4-bit value) register identifier
	
	// para maioria dos casos VX e VY:
	#define VX V_ [ ( (opcode_ & 0x0f00 ) >> 8)  ]
	#define VY V_ [ ( (opcode_ & 0x00f0 ) >> 4)  ]
	#define NNN (opcode_ & 0x0fff)
	#define NN (opcode_ & 0x00ff)
	#define N (opcode_ & 0x000f)
	
	switch( opcode_ & 0xf000 )
	{
		
		case 0x0000: // BEGIN OF 0xxx
		{
			switch( opcode_ )
			{
				case 0x0000: // 0NNN " calls RCA 1802 program at address NNN. not necessary for most ROMs. "
					break;



				case 0x00E0: // clear screen
					//renderer_->Render(NULL);
					break;



				case 0x00EE: // return from a subrotine ( unwind stack )
					if (sp_ > 0)
						pc_ = stack_[--sp_];
					
					break;

			}

			break;// END OF 0xxx
		}

		case 0x1000: // 1NNN:  jumps to address NNN
			pc_ = NNN;
			break;
	

		case 0x2000: // 2NNN: Calls subrotine at address NNN
			if (sp_	 < 16)
				stack_ [ sp_++ ] = pc_;
			
			pc_ = NNN;
			break;


		case 0x3000: // 3XNN: Skips the next instruction if VX equals NN
			if ( VX == NN )
                pc_ += 2;

            break;



        case 0x4000: // 4XNN: Skips the next instruction if VX doesn't equal NN
            if ( VX != NN )
                pc_ += 2;

            break;


        case 0x5000: // 5XY0: Skips the next instruction if VX equals VY
            if ( VX == VY )
                pc_ += 2;

            break;

		
		case 0x6000: // 6XNN: store number NN in register VX
			VX = NN;
			break;


		case 0x7000: // 7XNN: add the value NN to register VX
			VX =  ((VX + NN) & 0xFF);
			break;


		case 0x8000: // BEGIN OF 8xxx
		{
			switch ( opcode_ & 0x000f )
			{
				case 0x0: // 8XY0: store the value of register VY in register VX
					VX = VY;
					break;


				case 0x1: // 8XY1: set VX to VX | VY
					VX = (VY | VX );
					break;

				case 0x2: // 8XY2: sets VX to VX and VY
					VX = (VY & VX);
					break;


				case 0x3: // 8XY3: sets VX to VX xor VY
					VX = ((VY ^ VX) & 0xFF);
					break;


				case 0x4: // 8XY4: Adds VY to VX . VF is set to 1 when theres a carry, and to 0 when there isn't
				{
					/* demonstracao :

					auto &VX = V_ [ (opcode_ & 0x0f00)  >> 8];
					auto &VY = V_ [ (opcode_ & 0x00f0) >> 4];

					unsigned int result = VX + VY;

					if( ( result & 0xffffff00 ) != 0 )
						V_ [ 0xF ] = true;
					else
						V_ [ 0xF ] = false;

					VX = result;
					*/
					// otimizado :

					unsigned int result = VX + VY; // compute sum
					V_ [ 0xF ] = ( ( result & 0xffffff00 ) != 0) ? 1 : 0; // check carry

					VX = (result & 0xff);


					break;
			}



				case 0x5: // 8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

					V_[0xF] = (VX > VY); // checking if theres is a borrow

					VX -= VY;

					break;





				case 0x6: // 8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
					V_[0xF] = (VX & 0x1); // check the least significant bit
					VX >>= 1;

					break;





				case 0x7: // 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

					V_[0xF] = (VY > VX); // check borrow ( VY > VX )

					VX = (VY - VX);

					break;




				case 0xE: // 8XYE Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.
					V_[0xF] = ((VX & 0x80) >> 7 );  // check the most signifcant bit
					VX = (( VX <<  1) & 0xFF);

					break;


			}
			
			
			
			break; // END OF 8xxx

		}



		case 0x9000: // 9XY0: skips the next instruction if VX doesn't equal VY
			if( VX != VY )
				pc_ += 2;
			
			break;



		case 0xA000: // ANNN: sets I to the address NNN
			I_ = NNN;
			break;



		case 0xB000: // BNNN: jumps to the address NNN plus V0
			pc_ = (( NNN + V_ [ 0 ]) & 0xFFFF);
			break;

	
		case 0xC000: // CXNN: Sets VX to a bitwise operation AND ( & ) between NN and a random number
			VX =  (( (std::rand()%0xff) & NN ) & 0xFF);
			break;

		case 0xD000: // DXYN: DRAW INSTRUCTION
		{
			// from : http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/

			/*	Drawing pixels: 
				The opcode responsible for drawing to our display is 0xDXYN. The Wikipedia description tells us the following:

				Draws a sprite at coordinate (VX, VY) 
				that has a width of 8 pixels and a height of N pixels.
				Each row of 8 pixels is read as bit-coded starting from memory location I; 
				I value doesn’t change after the execution of this instruction. 
				As described above, 
				VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, 
				and to 0 if that doesn’t happen.



				As the description of the opcode is telling us, 
				the Chip 8 actually draws on the screen by drawing sprites. 
				It will give us the location of where the sprite needs to be drawn 
				(the opcode tells us which V register we need to check to fetch the X and Y coordinates) and the number of rows (N).
				 The width of each sprite is fixed (8 bits / 1 byte). 
				 The state of each pixel is set by using a bitwise XOR operation. 
				 This means that it will compare the current pixel state with the current value in the memory. 
				 If the current value is different from the value in the memory, the bit value will be 1. 
				 If both values match, the bit value will be 0.
			*/
			//dPrint("DRAWING");
			
			V_ [0xF] = 0;

			unsigned char Vx = VX, Vy = VY;
			int height = N;

			for (int i = 0; i < height; ++i)
			{
				unsigned char _8bitRow  = memory_[ I_ + i ];

				for (int j = 0; j < 8; ++j)
				{
					int px = ((Vx + j) & 63);
					int py = ((Vy + i) & 31);

					int pixelPos = (64 * py) + px;

					int pixel = (_8bitRow & (1 << (7-j))) != 0;

					V_ [0xF] |= ( gfx_ [pixelPos] & pixel );

					gfx_ [pixelPos] ^= ( pixel != 0) ? 0xffffffff : 0;
					
				
					

				}
				
			}
			
			renderer_->Render(gfx_);

			

			break;
		}



		case 0xE000:// BEGIN Exxx
		{
			switch (opcode_ & 0x000f)
			{
				case 0xE: // EX9E: Skips the next instruction if the key stored in VX is pressed.
					break;


				case 0x1: //0xEXA1	Skips the next instruction if the key stored in VX isn't pressed.
					break;
			}			
			
			break; // END OF Exxx
		}


		case 0xF000: // BEGIN OF Fxxx
		{
			switch (opcode_ & 0x000f)
			{
				case 0x7: // FX07	Sets VX to the value of the delay timer.
					VX = delayTimer_;
					break;


				case 0xA: //FX0A	A key press is awaited, and then stored in VX.
					this->waitKeyPress();
					break;

				

				case 0x8: // FX18	Sets the sound timer to VX.
					soundTimer_ = VX;
					break;



				case 0xE://	FX1E	Adds VX to I.
					I_ = ( ( I_ + VX) & 0xFFFF);
					break;

				case 0x9: // FX29   Sets I to the location of the sprite for the character in VX. 
						  // Characters 0-F (in hexadecimal) are represented by a 4x5 font.
					I_ =  (VX & 0xf);

					break;


				case 0x3: //FX33	Stores the Binary - coded decimal representation of VX, 
				{		 //with the most significant of three digits at the address in I, 
						 //the middle digit at I plus 1, and the least significant digit at I plus 2. 
						 //(In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, 
						 //the tens digit at location I + 1, and the ones digit at location I + 2.)
					auto Vx = VX;

					memory_[I_ + 2] = Vx % 10;
					memory_[I_ + 1] = (Vx / 10) % 10;
					memory_[I_] = (Vx / 100);

					break;
				}




				case 0x5: // BEGIN OF FX*5
				{
					switch (opcode_ & 0x00ff)
					{
						case 0x15: // FX15	Sets the delay timer to VX.
							delayTimer_ = VX;
							break;

						case 0x55: //FX55	Stores V0 to VX in memory starting at address I
							std::copy_n(V_, VX + 1, memory_ + I_);
							break;

						case 0x65: //FX65	Fills V0 to VX with values from memory starting at address I.
							std::copy_n(memory_ + I_, VX + 1, V_);
							break;

					}


					break; // END OF FX*5
				}



				
				
			}


			break; // END OF Fxxx
		}
		
		
		#undef VX
		#undef VY
		#undef NNN
		#undef NN
		#undef N		
	}	

	if (soundTimer_ > 0)
		--soundTimer_;

	if (delayTimer_ > 0)
		--delayTimer_;

    

}
