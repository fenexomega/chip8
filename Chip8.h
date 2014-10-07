#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <vector>

#define dPrint(x) std::cout << x << std::endl

using namespace std;

class Chip8
{
private:
    bool drawFlag;
    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16];
    unsigned short I;
    unsigned short pc;
    unsigned char gfx[64 * 32];
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short stack[16];
    unsigned short sp;
    unsigned char key[16];

    bool InitGraphics();
    bool InitSound();
    bool InitInput();

    //Coisas do SDL2
    SDL_Window *window;
    SDL_Renderer *rend;

    SDL_Event event;

public:
    Chip8();
    bool InitSystems();
    void EmulateCycle();
    void drawGraphics();
    void setKeys();
    bool loadGame(const char *gamename);
    bool getDrawFlag() const;
    void setDrawFlag(bool value);
    void Dispose();
    bool WantToExit();
    void Update();
};

#endif // CHIP8_H
