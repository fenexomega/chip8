#include <cstring>
#include <chrono>

#include "Chip8.h"
#include "Chip8Instructions.h"
#include "../utility/log.h"
#include "../utility/timer.h"

/* debug variables ...*/
static Timer precisionCheck(1_sec);
static unsigned int instructions = 0;
static unsigned int fps = 0;

Chip8::Chip8() : 
	m_drawFlag (false),
	m_instrFlag(false),
	m_exitFlag (false),
	m_gfxResolution(WIDTH,HEIGHT),
	m_memory ( nullptr )
	
{
	LOG("Creating Chip8 object...");
}






Chip8::~Chip8()
{	
	if(m_memory != nullptr)
		this->dispose();

	LOG("Destroying Chip8 object...");
}





bool Chip8::initialize(iRenderer* rend, iInput* input)
{

	LOG("Initializing Chip8 Systems...");
	/* check need to dispose*/
	if (m_memory != nullptr)
		this->dispose();


	/* initialize base system */
	m_pc = 0x200;	// Program counter starts at 0x200
	m_opcode = 0;	// Reset current opcode
	m_I = 0;		// Reset index register
	m_sp = 0;		// Reset stack pointer
	m_soundTimer = 0;
	m_delayTimer = 0;
	m_drawFlag = false;

	m_memory = new(std::nothrow) uint8_t[MEMORY_MAX];
	m_gfx.reset(new(std::nothrow) uint32_t[m_gfxResolution]);
	m_gfxBytes = (m_gfxResolution * sizeof(uint32_t));


	if ((m_memory == nullptr) || (m_gfx == nullptr))
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

	std::memcpy(m_memory, chip8_fontset, sizeof(uint8_t) * 80); // copy fontset to memory.


	/* initialize renderer / input / instruction table */
	m_renderer.reset(rend);
	m_input.reset(input);

	if (!initRenderer() || !initInput() || !Chip8Instructions::Initialize())
	{
		this->dispose();
		LOGerr("interrupting Chip8.");
		m_exitFlag = true;
		return false;

	};

	m_renderer->SetBuffer(m_gfx.get());
	m_input->SetWaitKeyPressCallback(this, waitKeyPressCallback);

	/* set clocks */
	m_clocks.instr.SetTargetTime(128_hz);
	m_clocks.frame.SetTargetTime(32_hz);

	return true;
}





void Chip8::dispose() noexcept
{
	// reverse deallocation
	Chip8Instructions::Dispose();
	m_input.reset();
	m_renderer.reset();

	delete[] m_memory;
	m_memory = nullptr;
}





Timer::Duration Chip8::getNextFlagTime() const
{
	auto instrTime = m_clocks.instr.GetRemain();
	auto frameTime = m_clocks.frame.GetRemain();
	return instrTime < frameTime ? instrTime : frameTime;
}





void Chip8::haltForFlags()
{

	if (!m_instrFlag && !m_drawFlag)
	{
		auto nextFlag = this->getNextFlagTime();
		if (nextFlag >= 256_micro) {
			Timer::Halt(nextFlag);
		}
	}
}





void Chip8::updateSystemState()
{
	updateRenderer();
	updateInput();
	updateTimers();
	updateFlags();

	/* testing timers precisions */
	if (precisionCheck.Finished())
	{
		CLS();
		printf("INSTRUCTIONS PER SECOND: %i\n", instructions);
		printf("FRAMES PER SECOND: %i\n", fps);
		instructions = 0;
		fps = 0;

		precisionCheck.Start();
	}

}







void Chip8::executeInstruction()
{
	++instructions; /* debug counter */

	m_opcode = ((m_memory[m_pc] << 8) | m_memory[m_pc + 1]);
	m_pc += 2;

	Chip8Instructions::s_instrTbl[(m_opcode & 0xF000) >> 12](this);
	m_instrFlag = false;
}




void Chip8::drawGraphics()
{
	++fps; /* debug counter */
	m_renderer->RenderBuffer();
	m_drawFlag = false;
}





bool Chip8::loadRom(const char *romFileName)
{
	LOG("Loading " << romFileName);
	std::FILE *romFile = std::fopen(romFileName, "rb");

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

}







void Chip8::updateRenderer()
{
	if (m_renderer->UpdateEvents())
	{
		if (m_renderer->IsWinClosed()) {
			m_exitFlag = true;
		}
	}
}







void Chip8::updateInput()
{
	if (m_input->UpdateKeys())
	{
		if (m_input->IsKeyPressed(EmulatorKey::RESET)) {
			this->reset();
			return;
		}

		else if (m_input->IsKeyPressed(EmulatorKey::ESCAPE)) {
			m_exitFlag = true;
			return;
		}
	}
}







void Chip8::updateTimers()
{
	/* decrease the timers by 1, every 60th of 1 second */
	static Timer delayAndSoundTimer(60_hz);

	if (delayAndSoundTimer.Finished())
	{
		if (m_soundTimer > 0)
			--m_soundTimer;
		if (m_delayTimer > 0)
			--m_delayTimer;

		delayAndSoundTimer.Start();
	}
}







void Chip8::updateFlags()
{

	if (!m_instrFlag && m_clocks.instr.Finished())
	{
		m_instrFlag = true;
		m_clocks.instr.Start();
	}

	if (!m_drawFlag && m_clocks.frame.Finished())
	{
		m_drawFlag = true;
		m_clocks.frame.Start();
	}
}







bool Chip8::initRenderer()
{
	if (!m_renderer) {
		LOGerr("NULL iRenderer.");
		return false;
	}
	return m_renderer->Initialize(m_gfxResolution.x, m_gfxResolution.y);
}








bool Chip8::initInput()
{
	if (!m_input) {
		LOGerr("NULL iInput.");
		return false;
	}

	return m_input->Initialize();
}







void Chip8::cleanFlags()
{
	m_instrFlag = false;
	m_drawFlag = false;
	m_exitFlag = false;
}






std::unique_ptr<iRenderer>& Chip8::getRenderer() 
{
	return m_renderer;
}




std::unique_ptr<iInput>& Chip8::getInput() 
{
	return m_input;
}



void Chip8::setRenderer(iRenderer* rend) 
{
	m_renderer.reset(rend);
}




void Chip8::setInput(iInput* rend) 
{
	m_input.reset(rend);
}




void Chip8::setInstrPerSec(unsigned short instrs) 
{
	m_clocks.instr.SetTargetTime(1_sec / instrs);
}



void Chip8::setFramesPerSec(unsigned short frames) 
{
	m_clocks.frame.SetTargetTime(1_sec / frames);
}








#define _this ((Chip8*)chip)
bool Chip8::waitKeyPressCallback(void* chip)
{
	_this->updateRenderer();
	_this->haltForFlags();
	if (_this->m_clocks.frame.Finished()) {
		_this->drawGraphics();
		_this->m_clocks.frame.Start();
	}

	return !_this->wantToExit();
}
#undef _this
