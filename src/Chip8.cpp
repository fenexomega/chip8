#include <cstring>
#include <cstdio>
#include <ctime>
#include <memory>
#include <SDL2/SDL.h>

#include "utility/log.h"
#include "SdlRenderer.h"
#include "SdlInput.h"

#include "Chip8.h"



Chip8::Chip8() : 
	m_drawFlag (false), m_interrupted (false), m_gfxResolution(WIDTH,HEIGHT), m_memory ( nullptr )
	
{
	LOG("Creating Chip8 object...");
	
}

/* After use Chip8::dispose(), be sure to call, chip8::initSystems() again before you use the object. */
void Chip8::dispose()
{
	// reverse deallocation
	m_input.reset();
	m_renderer->Dispose();
	m_renderer.reset();
	
	m_gfx.reset();
	
	delete[] m_memory;
	m_memory = nullptr;

}


Chip8::~Chip8()
{
	LOG("Destroying Chip8 object...");
	if(m_memory != nullptr)
		this->dispose(); // for deallocating in reverse order
}




bool Chip8::initRenderer(WindowMode mode) noexcept
{
	
	m_renderer.reset(new(std::nothrow) SdlRenderer());
	
	if(! m_renderer)
	{
		LOGerr("Couldn't allocate SdlRenderer.");
		return false;
	}
	
	return m_renderer->Initialize(m_gfxResolution.x, m_gfxResolution.y, mode);
}



bool Chip8::initInput() noexcept
{
	
	m_input.reset(new(std::nothrow) SdlInput());

	
	if(! m_input)
	{
		LOGerr("Couldn't allocate SdlInput.");
		return false;
	}
	
	return true;
}



bool Chip8::initialize(WindowMode mode) noexcept
{

	LOG("Initializing Chip8 Systems...");
	if(m_memory != nullptr)
		this->dispose();
	
	
	m_pc     = 0x200;	// Program counter starts at 0x200
	m_opcode = 0;		// Reset current opcode
	m_I      = 0;		// Reset index register
	m_sp     = 0;		// Reset stack pointer
	m_soundTimer = 0;	
	m_delayTimer = 0;
	m_drawFlag = false;
	
	m_memory = new(std::nothrow) uint8_t[MEMORY_MAX];
	
	m_gfx.reset( new(std::nothrow) uint32_t[m_gfxResolution]);
	m_gfxBytes = (m_gfxResolution * sizeof(uint32_t));
	

	if((m_memory == nullptr) || (m_gfx == nullptr))
	{
		LOGerr("Cannot allocate memory for GFX or emulated Memory, interrupting Chip8 instance.");
		m_interrupted = true;
		return false;
	}
	
	std::srand(std::time(0));						// seed rand
	std::memset(m_gfx.get(), 0, m_gfxResolution * sizeof(uint32_t));	// Clear display
	std::memset(m_stack, 0,     STACK_MAX 	    * sizeof(uint16_t));	// Clear stack
	std::memset(m_V, 0,         V_REGISTERS_MAX * sizeof(uint8_t));		// Clear registers V0-VF
	std::memset(m_memory, 0,    MEMORY_MAX      * sizeof(uint8_t)); 	// Clear memory

	// Load fontset
	uint8_t chip8_fontset[80] 
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
	
	
	std::memcpy(m_memory,chip8_fontset, sizeof(uint8_t) * 80); // copy fontset to memory.
	
	if( ! (initRenderer(mode) & initInput()) )
	{
		LOGerr("interrupting Chip8."); 
		m_interrupted = true; 
		return false;
	
	};
	
	return true;
}



bool Chip8::loadRom(const char *romFileName) noexcept
{
	LOG("Loading " << romFileName);
	std::FILE *romFile = std::fopen(romFileName,"rb");

	if (romFile == nullptr)
	{
		LOGerr("Error at opening ROM file, interrupting Chip8 instance.");
		m_interrupted = true;
		return false;
	}

	// get file size
	std::fseek(romFile, 0, SEEK_END);
	auto romFileSize = std::ftell(romFile);
	std::fseek(romFile, 0, SEEK_SET);

	// check if file size will not overflow emulated memory size
	if (romFileSize > ROM_SIZE_MAX)
	{
		LOGerr("Error, ROM size not compatible, interrupting Chip8 instance.");
		std::fclose(romFile);
		m_interrupted = true;
		return false;
	}

	std::fread(m_memory + 0x200, 1, romFileSize, romFile);
	std::fclose(romFile);
	LOG("Load Done!");

	return true;
}


inline void Chip8::cleanFlags() noexcept
{
	m_drawFlag = false;
	m_interrupted = false;
}

void Chip8::reset() noexcept
{
	this->cleanFlags();
	m_pc      = 0x200;
	m_opcode  = 0;	
	m_I = 0;			
	m_sp = 0;
	m_soundTimer = 0;
	m_delayTimer = 0;
	std::memset(m_gfx.get(), 0, m_gfxBytes);
	std::memset(m_stack,0, STACK_MAX        * sizeof(uint16_t));
	std::memset(m_V, 0,    V_REGISTERS_MAX  * sizeof(uint8_t));

}



void Chip8::updateCpuState() noexcept
{
	static auto timerCounter = std::clock();
	
	if(m_input->UpdateKeys())
	{
	
		if(m_input->IsKeyPressed(EmulatorKey::RESET))
			this->reset();
			
		else if(m_input->IsKeyPressed(EmulatorKey::ESCAPE))
			m_interrupted = true;

	}
	else if(m_renderer->IsWindowClosed())
		m_interrupted = true;
	

	// decrease the timers by 1. every 60th of 1 second
	if ((std::clock() - timerCounter) > CHIP8_CLOCK_FREQUENCY)
	{
		if (m_soundTimer > 0)
			--m_soundTimer;
		if (m_delayTimer > 0)
			--m_delayTimer;

		timerCounter = std::clock();
	}


}





bool Chip8::setWindowPosition(const unsigned x, const unsigned y) noexcept
{
	return m_renderer->SetWindowPosition(x,y);
}

bool Chip8::setWindowSize(const unsigned widht, const unsigned height) noexcept
{
	return m_renderer->SetWindowSize(widht, height);
}


void Chip8::executeInstruction() noexcept
{

	
	
	m_opcode = ( ( m_memory[ m_pc ] << 8 ) | m_memory [ m_pc + 1 ] );
	
	m_pc += 2;

	// NNN: address
	// NN: 8 bit constant
	// N: 4 bit constant
	// X and Y: (4-bit value) register identifier
	
	// para maior parte dos casos VX e VY:
	#define VX (m_V [ ( (m_opcode & 0x0f00 ) >> 8)  ])
	#define VY (m_V [ ( (m_opcode & 0x00f0 ) >> 4)  ])
	#define NNN (m_opcode & 0x0fff)
	#define NN (m_opcode & 0x00ff)
	#define N (m_opcode & 0x000f)
	
	static auto unkownOpcode = [](unsigned opcode, bool& interrupted)
	{
		LOGerr("Unknown Opcode: " << std::hex << opcode);
		interrupted = true;
	};
	
	
	
	switch( m_opcode & 0xf000 )
	{
		
		case 0x0000: // BEGIN OF 0xxx
		{
			switch( m_opcode )
			{
				case 0x0000: // 0NNN " calls RCA 1802 program at address NNN. not necessary for most ROMs. "
					break;

				case 0x00C0: // 00CN: scroll screen down N lines  ( SuperChip ) 
					LOG("Scrolling down");
					break;

				case 0x00FB: // scroll screen 4 pixels right ( SuperChip )
					LOG("Scrolling Right");
					break;

				case 0x00FC: // scroll screen 4 pixels left  ( SuperChip )
					LOG("Scrolling Left");					
					break;
				
				case 0x00FF: // increase resolution to 128x64 ( SuperChip )
					//this->setResolution(128,64);
					break;
				
				
				case 0x00E0: // clear screen
					std::memset(m_gfx.get(), 0, m_gfxBytes);
					break;



				case 0x00EE: // return from a subroutine ( unwind stack )
					if (m_sp > 0)
						m_pc = m_stack[--m_sp];
					
					break;

				default:
					unkownOpcode(m_opcode, m_interrupted);

			}

			break;// END OF 0xxx
		}

		case 0x1000: // 1NNN:  jumps to address NNN
			m_pc = NNN;
			break;
	

		case 0x2000: // 2NNN: Calls subroutine at address NNN
			if (m_sp	 < 16)
				m_stack [ m_sp++ ] = m_pc;
			
			m_pc = NNN;
			break;


		case 0x3000: // 3XNN: Skips the next instruction if VX equals NN
			if ( VX == NN )
				m_pc += 2;

			break;



		case 0x4000: // 4XNN: Skips the next instruction if VX doesn't equal NN
			if ( VX != NN )
				m_pc += 2;

			break;


		case 0x5000: // 5XY0: Skips the next instruction if VX equals VY
			if ( VX == VY )
				m_pc += 2;

			break;

		
		case 0x6000: // 6XNN: store number NN in register VX
			VX = NN;
			break;


		case 0x7000: // 7XNN: add the value NN to register VX
			VX =  ((VX + NN) & 0xFF);
			break;


		case 0x8000: // BEGIN OF 8xxx
		{
			switch ( m_opcode & 0x000f )
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

					int result = VX + VY; // compute sum
					m_V [ 0xF ] = ( ( result & 0xff00 ) != 0) ? 1 : 0; // check carry

					VX = (result & 0xff);


					break;
				}



				case 0x5: // 8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

					m_V[0xF] = (VX > VY); // checking if theres is a borrow

					VX -= VY;

					break;





				case 0x6: // 8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
					m_V[0xF] = (VX & 0x1); // check the least significant bit
					VX >>= 1;

					break;





				case 0x7: // 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.

					m_V[0xF] = (VY > VX); // check borrow ( VY > VX )

					VX = (VY - VX);

					break;




				case 0xE: // 8XYE Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.
					m_V[0xF] = ((VX & 0x80) >> 7 );  // check the most significant bit
					VX = (( VX <<  1) & 0xFF);

					break;

				default:
					unkownOpcode(m_opcode, m_interrupted);


			}
			
			
			
			break; // END OF 8xxx

		}



		case 0x9000: // 9XY0: skips the next instruction if VX doesn't equal VY
			if( VX != VY )
				m_pc += 2;
			
			break;



		case 0xA000: // ANNN: sets I to the address NNN
			m_I = NNN;
			break;



		case 0xB000: // BNNN: jumps to the address NNN plus V0
			m_pc = (( NNN + m_V [ 0 ]) & 0xFFFF);
			break;

	
		case 0xC000: // CXNN: Sets VX to a bitwise operation AND ( & ) between NN and a random number
			VX =  ((std::rand()%0xff) & NN );
			break;

		case 0xD000: // DXYN: DRAW INSTRUCTION
		{
			// from : http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/

			/*	Drawing pixels:
				The opcode responsible for drawing to our display is 0xDXYN. The Wikipedia description tells us the following:

				Draws a sprite at coordinate (VX, VY)
				that has a width of 8 pixels and a height of N pixels.
				Each row of 8 pixels is read as bit-coded starting from memory location I;
				I value doesn't change after the execution of this instruction.
				As described above,
				VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn,
				and to 0 if that doesn't happen.

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
			m_V[0xF] = 0;

			uint8_t Vx = VX, Vy = VY;
			int height = N;
			uint8_t *_8bitRow = &m_memory[m_I];
			
				for (int i = 0; i < height; ++i, ++_8bitRow)
				{
					for (int j = 0; j < 8; ++j)
					{
						int px = ((Vx + j) & 63);
						int py = ((Vy + i) & 31);

						int pixelPos = (64 * py) + px;

						bool pixel = (*_8bitRow & (1 << (7 - j))) != 0;

						m_V[0xF] |= ((m_gfx[pixelPos] > 0) & pixel);

						m_gfx[pixelPos] ^= (pixel) ? ~0 : 0;
					}
				}

			m_drawFlag = true;
			
			break;
		

		}


		case 0xE000:// BEGIN Exxx
		{
			switch (m_opcode & 0x000f)
			{
				case 0xE: // EX9E: Skips the next instruction if the key stored in VX is pressed.
					if(m_input->IsKeyPressed((EmulatorKey)VX))
						m_pc += 2;
					break;


				case 0x1: //0xEXA1	Skips the next instruction if the key stored in VX isn't pressed.
					if(!m_input->IsKeyPressed((EmulatorKey)VX))
						m_pc += 2;
					break;

				default:
					unkownOpcode(m_opcode, m_interrupted);
			}			
			
			break; // END OF Exxx
		}


		case 0xF000: // BEGIN OF Fxxx
		{
			switch (m_opcode & 0x000f)
			{
				case 0x7: // FX07	Sets VX to the value of the delay timer.
					VX = m_delayTimer;
					break;


				case 0xA: //FX0A	A key press is awaited, and then stored in VX.
					VX = ( m_input->WaitKeyPress() );
					break;

				

				case 0x8: // FX18	Sets the sound timer to VX.
					m_soundTimer = VX;
					break;



				case 0xE://	FX1E	Adds VX to I.
					m_I = ( ( m_I + VX) & 0xFFFF);
					break;

				case 0x9: // FX29   Sets I to the location of the sprite for the character in VX. 
						  // Characters 0-F (in hexadecimal) are represented by a 4x5 font.
					m_I = (VX) * 5;

					break;


				case 0x3: //FX33	Stores the Binary - coded decimal representation of VX, 
				{		 //with the most significant of three digits at the address in I, 
						 //the middle digit at I plus 1, and the least significant digit at I plus 2. 
						 //(In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, 
						 //the tens digit at location I + 1, and the ones digit at location I + 2.)
					uint8_t Vx = VX;

					m_memory[m_I + 2] = Vx % 10;
					m_memory[m_I + 1] = (Vx / 10) % 10;
					m_memory[m_I]     = (Vx / 100);

					break;
				}

				case 0x0: // FX30
				{
					LOG("FX30");
					m_I = VX;
					break;
				}





				case 0x5: // BEGIN OF FX*5
				{
					switch (m_opcode & 0x00ff)
					{
						case 0x15: // FX15	Sets the delay timer to VX.
							m_delayTimer = VX;
							break;

						case 0x55: //FX55	Stores V0 to VX in memory starting at address I
							std::memcpy(m_memory + m_I, m_V, ((m_opcode & 0x0f00) >> 8) + 1);
			
							break;

						case 0x65: //FX65	Fills V0 to VX with values from memory starting at address I.
							std::memcpy(m_V, m_memory + m_I, ((m_opcode & 0x0f00 ) >> 8) + 1);
						
							break;
						default:
							LOG("Unknow opcode " << std::hex << (unsigned) m_opcode);
							m_interrupted = true;

					}


					break; // END OF FX*5
				}

				default:
					unkownOpcode(m_opcode, m_interrupted);
				
				
			}


			break; // END OF Fxxx
		}
		default:
			unkownOpcode(m_opcode, m_interrupted);
		
		#undef VX
		#undef VY
		#undef NNN
		#undef NN
		#undef N		
	}	

}
