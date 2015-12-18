#ifndef CHIP8_H
#define CHIP8_H


#include <memory>
#include "interfaces/iRenderer.h"
#include "interfaces/iInput.h"
#include "resolution_t.h"



constexpr size_t MEMORY_MAX        = 0xFFF;
constexpr size_t STACK_MAX         = 16;
constexpr size_t V_REGISTERS_MAX   = 16;
constexpr long   ROM_SIZE_MAX      =  MEMORY_MAX - 0x200;

constexpr unsigned int CHIP8_CLOCK_FREQUENCY = CLOCKS_PER_SEC / 60;
constexpr size_t WIDTH   = 64;
constexpr size_t HEIGHT  = 32;


class Chip8
{
public:
	Chip8();
	bool initialize() noexcept;
	bool loadRom(const char *romFileName) noexcept;

	inline bool getDrawFlag() const noexcept;
	inline bool wantToExit() const noexcept;
	inline void drawGraphics() noexcept;
	void cleanFlags() noexcept;
	
	bool setResolution(size_t x, size_t y) noexcept;
	void updateCpuState()  noexcept;
	void executeInstruction() noexcept;

	void dispose();
	~Chip8();

private:
	bool initGraphics() noexcept;
	bool initInput() noexcept;
	void reset() noexcept;
	
	bool m_drawFlag;
	bool m_interrupted;
	size_t m_gfxBytes;
	resolution_t m_gfxResolution;
	
	uint8_t	*m_memory;
	std::unique_ptr<uint32_t[]> m_gfx;
	std::unique_ptr<iRenderer> m_renderer;
	std::unique_ptr<iInput>	m_input;
	
	
	
	uint8_t m_V[V_REGISTERS_MAX];
	uint8_t m_delayTimer;
	uint8_t m_soundTimer;
	uint16_t m_opcode;
	uint16_t m_I;
	uint16_t m_pc;
	uint16_t m_stack[STACK_MAX];
	uint16_t m_sp;
};








inline bool Chip8::wantToExit() const noexcept
{
	return m_interrupted;
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
