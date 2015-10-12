#ifndef CHIP8_H
#define CHIP8_H
#include <SDL2/SDL.h>
#undef main // for windows builds
#include "interfaces/iRenderer.h"
#include "interfaces/iInput.h"



#define MEMORY_MAX 0xFFF
#define STACK_MAX 16

constexpr int gfxResolution { 64 * 32 };
constexpr int gfxBytes{ gfxResolution * 4 };
constexpr int romMaxSize { MEMORY_MAX - 0x200 };


class Chip8
{
public:
	Chip8();
	bool initSystems();
	bool loadRom(const char *romFileName);
	inline bool getDrawFlag() const noexcept;
	inline bool wantToExit() const noexcept;
	void updateCycle()  noexcept;
	void executeInstruction() noexcept ;
	inline void drawGraphics() noexcept;
	void dispose();
	~Chip8();

private:
	bool initGraphics();
	bool initInput();
	void reset() noexcept;
	uint8_t waitKeyPress() noexcept;
	
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


inline bool Chip8::wantToExit() const noexcept
{
	// the type returned by the operation || is a bool, and operator | returns a int, with || we avoid casting i think..
	return renderer_->IsWindowClosed() || (input_->GetPressedKeyValue() == SDL_SCANCODE_ESCAPE);
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
