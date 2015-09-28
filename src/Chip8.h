#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"
#define dPrint(x) std::cout << x << std::endl


#define MEMORY_MAX 4096
#define STACK_MAX 16

constexpr size_t gfxResolution { 64 * 32 };
constexpr size_t romMaxSize { MEMORY_MAX - 0x200 };



class Chip8
{
public:
    Chip8();
    bool initSystems();
    bool loadRom(const char *romFileName);
    void executeOpcode();
    void emulateCycle();
    void drawGraphics();
    bool getDrawFlag() const;
    void setDrawFlag(const bool value);
	void setKeys();
	
	void update();
	bool wantToExit();
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
    unsigned char gfx_[gfxResolution];
    unsigned char delayTimer_;
    unsigned char soundTimer_;
    unsigned short stack_[STACK_MAX];
    unsigned short sp_;
    unsigned char key_[16];


    

};

#endif // CHIP8_H
