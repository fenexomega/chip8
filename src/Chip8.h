#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"
#define dPrint(x) std::cout << x << std::endl


#define MEMORY_MAX 0xFFF
#define STACK_MAX 16

constexpr size_t gfxResolution { 64 * 32 };
constexpr size_t romMaxSize { MEMORY_MAX - 0x200 };

// Telmac operated 3.58MHz / 2
// Chip8 timers count down at 60Hz .
// ( 3580000 / 2 ) / 60

class Chip8
{


public:
    Chip8();
    bool initSystems();
    bool loadRom(const char *romFileName);
    bool wantToExit();
    bool getDrawFlag() const;
  
    void executeOpcode();
    void emulateCycle();
    void drawGraphics();
	int waitKeyPress();
	void dispose();
	
	~Chip8();
private:
    bool initGraphics();
    bool initSound();
    bool initInput();
    

	iRenderer *renderer_;
    bool drawFlag_;
    unsigned short opcode_;
    unsigned char memory_[MEMORY_MAX];
    unsigned char V_[16];
    unsigned short I_;
    unsigned short pc_;
    uint32_t gfx_[gfxResolution];
    unsigned char delayTimer_;
    unsigned char soundTimer_;
    unsigned short stack_[STACK_MAX];
    unsigned short sp_;
    unsigned char key_[16];


    

};

#endif // CHIP8_H
