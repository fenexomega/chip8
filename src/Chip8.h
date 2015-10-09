#ifndef CHIP8_H
#define CHIP8_H
#include <cstdio>
#include <ctime>
#include <SDL2/SDL.h>
#undef main // for windows builds
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
	inline bool getDrawFlag() const noexcept;
	inline bool wantToExit() const noexcept;
	void executeInstruction() noexcept ;
	inline void updateCycle()  noexcept;
	inline void drawGraphics() noexcept;
	void dispose();
	~Chip8();

private:
	bool initGraphics();
	bool initInput();
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


inline void Chip8::updateCycle() noexcept
{
	input_->UpdateKeys();
	
	/* use this code if you want to check the key values that are send to chip8 core.
	static int key;
	if ((key = input_->GetPressedKeyValue()) != NO_KEY_PRESSED)
		LOG(key << " Pressed");
	*/

	if (soundTimer_ > 0)
	{
		if (soundTimer_ == 1)
		{
			// just temporary beep for tests, it is not very much portable, nor emulates exactly the orignal sound
			std::printf("\a");
			std::fflush(stdout);
		}
		--soundTimer_;
	}

	
	if (delayTimer_ > 0)
	{
		static auto delayTimeCounter = std::clock();
		// TODO: optimize time delay, optimize precision.
		if ((std::clock() - delayTimeCounter) >= 10)
		{
			--delayTimer_;
			delayTimeCounter = std::clock();
		}
	}

}





#endif // CHIP8_H
