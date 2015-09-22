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
public:
    Chip8();
    bool initSystems();
    void emulateCycle();
    void drawGraphics();
    void setKeys();
    bool loadGame(const char *gamename);
    bool getDrawFlag() const;
    void setDrawFlag(bool value);
    void dispose();
    bool wantToExit();
    void update();

private:
    bool drawFlag_;
    unsigned short opcode_;
    unsigned char memory_[4096];
    unsigned char V_[16];
    unsigned short I_;
    unsigned short p_c;
    unsigned char gfx_[64 * 32];
    unsigned char delayTimer;
    unsigned char soundTimer;
    unsigned short stack_[16];
    unsigned short sp_;
    unsigned char key_[16];

    bool initGraphics();
    bool initSound();
    bool initInput();

    //Coisas do SDL2
	struct 
	{
    	SDL_Window *window;
    	SDL_Renderer *rend;
		SDL_Event event;
	
	} screen_;


};

#endif // CHIP8_H
