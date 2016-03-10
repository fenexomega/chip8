#include <cstring>
#include <SDL2/SDL.h>

#include "utility/log.h"
#include "sdl/SdlRenderer.h"
#include "sdl/SdlInput.h"
#include "Chip8.h"
#include "Chip8Instructions.h"




Chip8::Chip8() : 
	m_drawFlag (false),
	m_exitFlag (false),
	m_resetFlag (false),
	m_gfxResolution(WIDTH,HEIGHT),
	m_memory ( nullptr )
	
{
	LOG("Creating Chip8 object...");
}

void Chip8::dispose() noexcept
{
	// reverse deallocation
	Chip8Instructions::Dispose();

	m_input.reset();

	if(m_renderer != nullptr)
		m_renderer->Dispose();

	m_renderer.reset();
	
	delete[] m_memory;
	m_memory = nullptr;
}


Chip8::~Chip8()
{
	
	if(m_memory != nullptr)
		this->dispose(); // for deallocating in reverse order

	LOG("Destroying Chip8 object...");
}





bool Chip8::initRenderer(WindowMode mode)
{
	
	m_renderer.reset(new(std::nothrow) SdlRenderer());
	
	if(! m_renderer)
	{
		LOGerr("Couldn't allocate SdlRenderer.");
		return false;
	}
	
	return m_renderer->Initialize(m_gfxResolution.x, m_gfxResolution.y, mode);
}



bool Chip8::initInput()
{
	
	m_input.reset(new(std::nothrow) SdlInput());

	
	if(! m_input)
	{
		LOGerr("Couldn't allocate SdlInput.");
		return false;
	}
	
	return true;
}

void Chip8::cleanFlags() 
{
	m_drawFlag = false;
	m_exitFlag = false;
	m_resetFlag = false;
}




bool Chip8::initialize(WindowMode mode)
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
		this->dispose();
		m_exitFlag = true;
		return false;
	}
	
	std::srand(static_cast<unsigned int>(std::time(0)));             // seed rand
	std::memset(m_gfx.get(), 0, m_gfxResolution * sizeof(uint32_t)); // Clear display
	std::memset(m_stack, 0, STACK_MAX * sizeof(uint16_t));           // Clear stack
	std::memset(m_V, 0, V_REGISTERS_MAX * sizeof(uint8_t));          // Clear registers V0-VF
	std::memset(m_memory, 0, MEMORY_MAX * sizeof(uint8_t));          // Clear memory

	// Load fontset
	static uint8_t chip8_fontset[80] 
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
	
	if( !initRenderer(mode) || !initInput() || !Chip8Instructions::Initialize())
	{
		this->dispose();
		LOGerr("interrupting Chip8."); 
		m_exitFlag = true; 
		return false;
	
	};
	
	return true;
}



bool Chip8::loadRom(const char *romFileName)
{
	LOG("Loading " << romFileName);
	std::FILE *romFile = std::fopen(romFileName,"rb");

	if (romFile == nullptr)
	{
		LOGerr("Error at opening ROM file, interrupting Chip8 instance.");
		m_exitFlag = true;
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
		m_exitFlag = true;
		return false;
	}

	std::fread(m_memory + 0x200, 1, romFileSize, romFile);
	std::fclose(romFile);
	LOG("Load Done!");

	return true;
}




void Chip8::reset()
{
	this->cleanFlags();
	m_pc      = 0x200;
	m_opcode  = 0;
	m_I = 0;
	m_sp = 0;
	m_soundTimer = 0;
	m_delayTimer = 0;
	std::memset(m_gfx.get(), 0, m_gfxBytes);
	std::memset(m_stack,0, STACK_MAX * sizeof(uint16_t));
	std::memset(m_V, 0, V_REGISTERS_MAX  * sizeof(uint8_t));
	m_resetFlag = true;

}



void Chip8::updateSystemState()
{
	static auto timer = std::clock();

	m_renderer->UpdateEvents();
	
	if(m_input->UpdateKeys())
	{
	
		if(m_input->IsKeyPressed(EmulatorKey::RESET)) {
			this->reset();
			return;
		}
			
		else if(m_input->IsKeyPressed(EmulatorKey::ESCAPE)) {
			m_exitFlag = true;
			return;
		}

	}

	else if (m_renderer->IsWindowClosed()) {
		m_exitFlag = true;
		return;
	}


	// decrease the timers by 1. every 60th of 1 second
	if ((std::clock() - timer) > CHIP8_CLOCK_FREQUENCY)
	{
		if (m_soundTimer > 0)
			--m_soundTimer;
		if (m_delayTimer > 0)
			--m_delayTimer;

		timer = std::clock();
	}


}


void Chip8::drawGraphics() {
	m_renderer->Render(m_gfx.get());
	m_drawFlag = false;
}


void Chip8::setWindowPosition(const unsigned x, const unsigned y) {
	m_renderer->SetWindowPosition(x,y);
}

void Chip8::setWindowSize(const unsigned widht, const unsigned height) {
	m_renderer->SetWindowSize(widht, height);
}


void Chip8::executeInstruction()
{
	m_opcode = ((m_memory[m_pc] << 8) | m_memory[m_pc + 1]);
	m_pc += 2;
	Chip8Instructions::s_instrPtr[(m_opcode & 0xF000) >> 12](this);
}










