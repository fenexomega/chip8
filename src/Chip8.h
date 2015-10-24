#ifndef CHIP8_H
#define CHIP8_H

#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"
#include "interfaces/iInput.h"
#include "resolution_t.h"
#undef main // for windows builds



#define MEMORY_MAX 0xFFF
#define STACK_MAX 16
#define V_REGISTERS_MAX 16
constexpr int romMaxSize { MEMORY_MAX - 0x200 };




/*
* With the possibility of implementing a GUI for this emulator
* I have added more Interfaces to the Chip8 class
* Hope I didn't make it hard to read.
*
* Basicaly, we do not use exceptions, so we have to try to keep most things with C algorithms
* for that reason our functions are noexcept.
* if an exception is throw from a C++ algorithm library, the program will terminate.
*
* if a Chip8 member function have the chance to fail. it have to return a bool ( true for success , false for failure )
* if the failure is critcal, the function have to set interrupted_ flag to true, and return false indicating failure.
*
*/

class Chip8
{
public:
	Chip8();
	bool initSystems() noexcept;
	bool loadRom(const char *romFileName) noexcept;

	inline bool getDrawFlag() const noexcept;
	inline bool wantToExit() const noexcept;
	inline void drawGraphics() noexcept;
	inline void cleanFlags() noexcept;
	
	bool setResolution(const int x, const int y) noexcept;
	void updateCpuState()  noexcept;
	void executeInstruction() noexcept;

	void dispose();
	~Chip8();

private:
	bool initGraphics() noexcept;
	bool initInput() noexcept;
	void reset() noexcept;
	uint8_t waitKeyPress() noexcept;

	bool drawFlag_;
	bool interrupted_;

	resolution_t gfxResolution_;
	size_t gfxBytes_;

	iRenderer *renderer_;
	iInput *input_;


	uint32_t *gfx_;
	uint8_t *memory_;
	uint8_t V_[V_REGISTERS_MAX];
	uint8_t delayTimer_;
	uint8_t soundTimer_;
	uint16_t opcode_;
	uint16_t I_;
	uint16_t pc_;
	uint16_t stack_[STACK_MAX];
	uint16_t sp_;



};




inline void Chip8::cleanFlags() noexcept
{
	drawFlag_ = false;
	interrupted_ = false;
}



inline bool Chip8::wantToExit() const noexcept
{
	return renderer_->IsWindowClosed() || input_->IsKeyPressed(ESCAPE_KEY_CODE) || interrupted_;
}


inline bool Chip8::getDrawFlag() const noexcept
{
	return drawFlag_;
}



inline void Chip8::drawGraphics() noexcept
{
	renderer_->Render(gfx_);
	drawFlag_ = false;
}







#endif // CHIP8_H
