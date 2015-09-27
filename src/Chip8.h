#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <SDL2/SDL.h>
#include "interfaces/iRenderer.h"
#define dPrint(x) std::cout << x << std::endl


#define MEMORY_MAX 4096
#define STACK_MAX 16

constexpr size_t gfxRes { 64 * 32 };
constexpr size_t romMax { MEMORY_MAX - 0x200 };



class Chip8
{
public:
    Chip8();
    bool initSystems();
    void emulateCycle();
    void executeOpcode();
    void drawGraphics();
    void setKeys();
    bool loadGame(const char *gameName);
    bool getDrawFlag() const;
    void setDrawFlag(const bool value);
    void dispose();
    bool wantToExit();
    void update();
    ~Chip8();
private:
	iRenderer *renderer_;
    bool drawFlag_;
    unsigned short opcode_;
    unsigned char memory_[MEMORY_MAX];
    unsigned char V_[16];
    unsigned short I_;
    unsigned short pc_;
    unsigned char gfx_[gfxRes];
    unsigned char delayTimer_;
    unsigned char soundTimer_;
    unsigned short stack_[STACK_MAX];
    unsigned short sp_;
    unsigned char key_[16];

    bool initGraphics();
    bool initSound();
    bool initInput();
	
    

};

#endif // CHIP8_H