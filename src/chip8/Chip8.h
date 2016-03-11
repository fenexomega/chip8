#ifndef CHIP8_H
#define CHIP8_H
#include <ctime>
#include <memory>
#include "../interfaces/iRenderer.h"
#include "../interfaces/iInput.h"
#include "../utility/resolution_t.h"
#include "../utility/timer.h"


class Chip8
{
	constexpr static size_t MEMORY_MAX = 0xFFF;
	constexpr static size_t STACK_MAX = 16;
	constexpr static size_t V_REGISTERS_MAX = 16;
	constexpr static long ROM_SIZE_MAX = MEMORY_MAX - 0x200;
	constexpr static size_t WIDTH = 64;
	constexpr static size_t HEIGHT = 32;
	friend class Chip8Instructions;
	
public:
	Chip8(const Chip8&) = delete;
	Chip8& operator=(const Chip8&) = delete;
	Chip8();
	~Chip8();


	bool initialize(iRenderer* rend, iInput* input);
	void dispose() noexcept;

	bool getDrawFlag() const;
	bool wantToExit() const;
	std::unique_ptr<iRenderer>& getRenderer();
	std::unique_ptr<iInput>& getInput();

	bool loadRom(const char* romFileName);
	void updateSystemState();
	void executeInstruction();
	void drawGraphics();
	void cleanFlags();
	void reset();

	void setRenderer(iRenderer* rend);
	void setInput(iInput* rend);
	void setInstrPerSec(unsigned short instrs);
	void setFramesPerSec(unsigned short frames);

private:
	bool initRenderer();
	bool initInput();
	static bool waitKeyPressCallback(void* const);

private:
	bool m_drawFlag;
	bool m_resetFlag;
	bool m_exitFlag;
	size_t m_gfxBytes;
	resolution_t m_gfxResolution;
	
	uint8_t* m_memory;
	std::unique_ptr<uint32_t[]> m_gfx;
	std::unique_ptr<iRenderer> m_renderer;
	std::unique_ptr<iInput>	m_input;
	
	uint8_t m_V[V_REGISTERS_MAX];
	uint8_t m_delayTimer;
	uint8_t m_soundTimer;
	uint8_t m_sp;	
	uint16_t m_opcode;
	uint16_t m_I;
	uint16_t m_pc;
	uint16_t m_stack[STACK_MAX];


	struct {
		Timer drawTimer;
		Timer instrTimer;
	}m_timers;
};


inline bool Chip8::wantToExit() const  {
	return m_exitFlag;
}


inline bool Chip8::getDrawFlag() const {
	return m_drawFlag;
}


inline std::unique_ptr<iRenderer>& Chip8::getRenderer() {
	return m_renderer;
}


inline std::unique_ptr<iInput>& Chip8::getInput() {
	return m_input;
}


inline void Chip8::setRenderer(iRenderer* rend) {
	m_renderer.reset(rend);
}


inline void Chip8::setInput(iInput* rend) {
	m_input.reset(rend);
}





#endif // CHIP8_H
