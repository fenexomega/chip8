#ifndef CHIP8_H
#define CHIP8_H
#include "interfaces/iRenderer.h"
#include "interfaces/iInput.h"

#define MEMORY_MAX 0xFFF
#define STACK_MAX 16

constexpr int gfxResolution { 64 * 32 };
constexpr int gfxBytes{ gfxResolution * 4 };
constexpr int romMaxSize { MEMORY_MAX - 0x200 };

// Telmac operated 3.58MHz / 2
// Chip8 timers count down at 60Hz .
// ( 3580000 / 2 ) / 60

class Chip8
{
public:
	Chip8();
	bool initSystems();
	bool loadRom(const char *romFileName);
	bool getDrawFlag() const noexcept;
	inline bool wantToExit() const noexcept;
	void executeInstruction() noexcept ;
	inline void updateCycle()  noexcept;
	void drawGraphics() noexcept;
	void dispose();
	~Chip8();

private:
	bool initGraphics();
	bool initInput();
	int waitKeyPress() noexcept;
	
	bool drawFlag_;
	iRenderer *renderer_;
	iInput *input_;

	uint32_t *gfx_;
	uint8_t *memory_;
	uint8_t V_[16];
	uint8_t delayTimer_;
	uint8_t soundTimer_;
	uint16_t opcode_;
	uint16_t I_;
	uint16_t pc_;
	uint16_t stack_[STACK_MAX];
	uint16_t sp_;

};


#endif // CHIP8_H
