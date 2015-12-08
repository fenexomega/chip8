#ifndef CHIP8_H
#define CHIP8_H
#include <memory>
#include <SDL2/SDL.h>

#include "interfaces/iRenderer.h"
#include "interfaces/iInput.h"
#include "resolution_t.h"
#include "utility/log.h"
#undef main // for windows builds



#define MEMORY_MAX 0xFFF
#define STACK_MAX 16
#define V_REGISTERS_MAX 16
constexpr long ROM_MAX_SIZE { MEMORY_MAX - 0x200 };



class Chip8
{
public:
	Chip8();
	bool initialize() noexcept;
	bool loadRom(const char *romFileName) noexcept;

	inline bool getDrawFlag() const noexcept;
	inline bool wantToExit() const noexcept;
	inline void drawGraphics() noexcept;
	inline void cleanFlags() noexcept;
	
	bool setResolution(size_t x, size_t y) noexcept;
	void updateCpuState()  noexcept;
	void executeInstruction() noexcept;

	void dispose();
	~Chip8();

private:
	bool initGraphics() noexcept;
	bool initInput() noexcept;
	void reset() noexcept;
	uint8_t waitKeyPress() noexcept;
	
	bool m_drawFlag;
	bool m_interrupted;
	size_t m_gfxBytes;
	resolution_t m_gfxResolution;
	std::unique_ptr<iRenderer> m_renderer;
	std::unique_ptr<iInput>	m_input;
	std::unique_ptr<uint32_t[]> m_gfx;
	
	uint8_t	*m_memory;
	uint8_t m_V[V_REGISTERS_MAX];
	uint8_t m_delayTimer;
	uint8_t m_soundTimer;
	uint16_t m_opcode;
	uint16_t m_I;
	uint16_t m_pc;
	uint16_t m_stack[STACK_MAX];
	uint16_t m_sp;
};




inline void Chip8::cleanFlags() noexcept
{
	m_drawFlag = false;
	m_interrupted = false;
}



inline bool Chip8::wantToExit() const noexcept
{
	return m_renderer->IsWindowClosed() || m_input->IsKeyPressed(ESCAPE_KEY_CODE) || m_interrupted;
}


inline bool Chip8::getDrawFlag() const noexcept
{
	return m_drawFlag;
}



inline void Chip8::drawGraphics() noexcept
{
	m_renderer->Render(m_gfx.get());
	m_drawFlag = false;
}




#endif // CHIP8_H
