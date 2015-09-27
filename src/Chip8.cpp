#include <algorithm>
#include <fstream>
#include <iterator>
#include "SdlRenderer.h"
#include "Chip8.h"




Chip8::Chip8() : 
	renderer_ ( new SdlRenderer() )
{

}

bool Chip8::getDrawFlag() const
{
    return drawFlag_;
}

void Chip8::setDrawFlag(bool value)
{
    drawFlag_ = value;
}

void Chip8::dispose()
{
   
}

bool Chip8::wantToExit()
{
   // return sdl_->event.type == SDL_QUIT;
}

void Chip8::update()
{
    //SDL_PollEvent(&sdl_->event);
}

bool Chip8::initGraphics()
{
    if(!renderer_->initialize())
		return false;

	
	drawFlag_ = true;
   
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
    pc_     = 0x200;  // Program counter starts at 0x200
    opcode_ = 0;      // Reset current opcode
    I_      = 0;      // Reset index register
    sp_     = 0;      // Reset stack pointer

    std::fill(gfx_,gfx_ + ( gfxRes ), 0); 		// Clear display
    std::fill(stack_,stack_ + STACK_MAX, 0); 	// Clear stack
    std::fill(V_,V_+16,0);  					// Clear registers V0-VF
	std::fill(memory_,memory_+MEMORY_MAX,0);  	// Clear memory
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

	std::copy(chip8_fontset,chip8_fontset+80, memory_); // copy fontset to memory.


    
    return initGraphics() & initSound() & initInput();

}

void Chip8::emulateCycle()
{
    SDL_Delay(1000/60);

}

void Chip8::drawGraphics()
{
    update();
}

void Chip8::setKeys()
{

}


bool Chip8::loadGame(const char *gameName)
{
    dPrint("Loading " << gameName);
    std::ifstream game(gameName, std::ios::in | std::ios::binary | std::ios::ate);
   

    if(!game.is_open())
    {
        dPrint("Error at opening game file. Exiting!");
        return false;
    }

	size_t gameSize = game.tellg();

	if(gameSize > romMax)
	{
		dPrint("Error, ROM size not compatible. Exiting!");
		return false;
	}
	
	game.seekg(0,game.beg);

	std::copy(std::istream_iterator<unsigned char>(game), std::istream_iterator<unsigned char>(), memory_ + 0x200);
 	
	game.close();
		   
    return true;
}
Chip8::~Chip8()
{
    dPrint("Destroying Chip8...");
	this->dispose();
    delete renderer_;
}



void Chip8::executeOpcode()
{
	opcode_ = ( memory_[ pc_ ] << 8 | memory_[ pc_ + 1 ] );
	
    pc_ += 2;

	// NNN: address
	// NN: 8 bit constant
	// N: 4 bit constant
	// X and Y: (4-bit value) register identifier
	
	// para maioria dos casos VX e VY:
	#define VX V_ [ opcode_ & 0x0f00 ]
	#define VY V_ [ opcode_ & 0x00f0 ]
	
	
	switch( opcode_ & 0xf000 )
	{
		
		case 0x0000:
			switch( opcode_ )
			{
				case 0x0000: // 0NNN " calls RCA 1802 program at address NNN. not necessary for most ROMs. "
					break;



				case 0x00E0: // clear screen
					break;



				case 0x00EE: // return from a subrotine ( unwind stack )
					break;

			}
		
		

		case 0x1000: // 1NNN:  jumps to address NNN
			break;
	

		case 0x2000: // 2NNN: Calls subrotine at address NNN
			break;


		case 0x3000: // 3XNN: Skips the next instruction if VX equals NN
			if ( V_[ opcode_ & 0x0f00 ] == (opcode_ & 0x00ff ) )
                pc_ += 2;

            break;



        case 0x4000: // 4XNN: Skips the next instruction if VX doesn't equal NN
            if ( V_ [ opcode_ & 0x0f00 ] != ( opcode_ & 0x00ff ) )
                pc_ += 2;

            break;


        case 0x5000: // 5XY0: Skips the next instruction if VX equals VY
            if ( V_ [ opcode_ & 0x0f00 ] == V_ [ opcode_ & 0x00f0] )
                pc_ += 2;

            break;

		
		case 0x6000: // 6XNN: store number NN in register VX
			V_ [ opcode_ &  0x0f00   ] = ( opcode_ & 0x00ff );
			break;


		case 0x7000: // 7XNN: add the value NN to register VX
			V_ [ opcode_ & 0x0f00 ] = ( opcode_ & 0x00ff );
			break;


		case 0x8000:
			switch( opcode_ & 0x000f )
			{
				case 0x0: // 8XY0: store the value of register VY in register VX
					V_ [ opcode_ & 0x0f00 ] = V_ [ opcode_ & 0x00f0 ];
					break;


				case 0x1: // 8XY1: set VX to VX | VY
					V_ [ opcode_ & 0x0f00 ] = ( V_ [ opcode_ & 0x0f00 ] | V_ [ opcode_ & 0x00f0 ] ) ;
					break;

				case 0x2: // 8XY2: sets VX to VX and VY
					V_ [ opcode_ & 0x0f00 ] = ( V_ [ opcode_ & 0x0f00] & V_ [ opcode_ & 0x00f0] ) ;
					break;


				case 0x3: // 8XY3: sets VX to VX xor VY
					V_ [ opcode_ & 0x0f00 ] = ( V_ [ opocde_ & 0x0f00 ] ^ V_ [ opcode_ & 0x00f0 ] ); 
					break;
				
				
				case 0x4: // 8XY4: Adds VY to VX . VF is set to 1 when theres a carry, and to 0 when there isn't
				{
					/* demonstracao : 
					
					auto &VX = V_ [ opcode_ & 0x0f00 ];
					auto &VY = V_ [ opcode_ & 0x00f0 ];

					unsigned int result = VX + VY;
			
					if( ( result & 0xffff0000 ) != 0 )
						V_ [ 0xF ] = true;

					VX = result;
					*/
					// otimizado :
					unsigned int result = V_ [ opcode_ & 0x0f00 ] + V_ [ opcode_ & 0x00f0 ];
					if( result & 0xffff0000 )
						V_ [ 0xF ] = 1;

					V_ [ opcode_ & 0x0f00 ] = ( result & 0xffff );

					

				}	
					break;		

			}

	}	
    
	#undef VX
	#undef VY
}
