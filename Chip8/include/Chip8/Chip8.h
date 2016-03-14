#ifndef CHIP8_H
#define CHIP8_H
#include "Utility/resolution_t.h"
#include "Utility/timer.h"

class iRenderer;
class iInput;

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

	Timer::Duration getNextFlagTime() const;
	void haltForNextFlag() const;

	void updateSystemState();
	void executeInstruction();
	bool loadRom(const char* romFileName);
	void drawGraphics();
	void cleanFlags();
	void reset();

	
	iRenderer* getRenderer();
	iInput* getInput();
	void setRenderer(iRenderer* rend);
	void setInput(iInput* input);
	void setInstrPerSec(unsigned short instrs);
	void setFramesPerSec(unsigned short frames);


	inline bool getExitFlag() const;
	inline bool getDrawFlag() const;
	inline bool getInstrFlag() const;

	inline void setExitFlag(bool);
	inline void setDrawFlag(bool);
	inline void setInstrFlag(bool);

private:
	bool initRenderer();
	bool initInput();
	void updateTimers();
	void updateFlags();
	static bool waitKeyPressCallback(void*);

private:
	bool m_instrFlag;
	bool m_drawFlag;
	bool m_exitFlag;
	size_t m_gfxBytes;
	resolution_t m_gfxResolution;
		
	uint8_t m_delayTimer;
	uint8_t m_soundTimer;

	iRenderer* m_renderer;
	iInput*	m_input;
	
	
	uint8_t* m_memory; /* also used to check if need to dispose ( when not nullptr ) */
	uint32_t* m_gfx;   /* graphics array */
	uint16_t m_opcode;
	uint16_t m_pc;  
	
	uint16_t m_I;      /* index register    */
	uint8_t* m_V;      /* registers V0 - VF */
	uint16_t* m_stack; /* stack array       */
	uint8_t m_sp;      /* stack index       */
	
	struct {
		Timer instr;
		Timer frame;
	}m_clocks;
};


inline bool Chip8::getExitFlag() const  {
	return m_exitFlag;
}

inline bool Chip8::getDrawFlag() const {
	return m_drawFlag;
}

inline bool Chip8::getInstrFlag() const {
	return m_instrFlag;
}


inline void Chip8::setExitFlag(bool val) {
	m_exitFlag = val;
}

inline void Chip8::setDrawFlag(bool val) {
	m_drawFlag = val;
}

inline void Chip8::setInstrFlag(bool val) {
	m_instrFlag = val;
}







#endif // CHIP8_H
