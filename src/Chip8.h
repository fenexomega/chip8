#ifndef CHIP8_H
#define CHIP8_H
#include <ctime>
#include <memory>
#include "interfaces/iRenderer.h"
#include "interfaces/iInput.h"
#include "resolution_t.h"



class Chip8
{
	constexpr static size_t MEMORY_MAX = 0xFFF;
	constexpr static size_t STACK_MAX = 16;
	constexpr static size_t V_REGISTERS_MAX = 16;
	constexpr static long ROM_SIZE_MAX = MEMORY_MAX - 0x200;
	constexpr static long CHIP8_CLOCK_FREQUENCY = CLOCKS_PER_SEC / 60;
	constexpr static size_t WIDTH = 64;
	constexpr static size_t HEIGHT = 32;
	friend class Chip8Instructions;
public:
	Chip8();
	Chip8(const Chip8&) = delete;
	Chip8& operator=(const Chip8&) = delete;
	~Chip8();


	bool initialize(WindowMode mode = WindowMode::RESIZABLE);
	bool loadRom(const char* romFileName);
	void drawGraphics();
	void updateSystemState();
	void executeInstruction();
	void cleanFlags();
	
	void setWindowPosition(const unsigned x, const unsigned y);
	void setWindowSize(const unsigned widht, const unsigned height);

	bool checkResetFlag();
	bool getResetFlag() const;
	bool getDrawFlag() const;
	bool wantToExit() const;
	void dispose() noexcept;
	

private:
	bool initRenderer(WindowMode mode);
	bool initInput();
	void reset();
	

private:
	bool m_drawFlag;
	bool m_exitFlag;
	bool m_resetFlag;
	size_t m_gfxBytes;
	resolution_t m_gfxResolution;
	
	uint8_t* m_memory;
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




inline bool Chip8::wantToExit() const  {
	return m_exitFlag;
}


inline bool Chip8::getDrawFlag() const {
	return m_drawFlag;
}

inline bool Chip8::getResetFlag() const {
	return m_resetFlag;
}


inline bool Chip8::checkResetFlag()
{
	if (m_resetFlag) {
		m_resetFlag = false;
		return true;
	}
	return false;
}






#endif // CHIP8_H
