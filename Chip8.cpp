#include "Chip8.h"


bool Chip8::getDrawFlag() const
{
    return drawFlag;
}

void Chip8::setDrawFlag(bool value)
{
    drawFlag = value;
}
bool Chip8::InitGraphics()
{

}

bool Chip8::InitSound()
{

}

bool Chip8::InitInput()
{

}

Chip8::Chip8()
{
}

bool Chip8::InitSystems()
{
    pc     = 0x200;  // Program counter starts at 0x200
    opcode = 0;      // Reset current opcode
    I      = 0;      // Reset index register
    sp     = 0;      // Reset stack pointer

    // Clear display
    // Clear stack
    // Clear registers V0-VF
    // Clear memory
    // Load fontset
    for(int i = 0; i < 80; ++i)
//        memory[i] = chip8_fontset[i];

    return InitGraphics() & InitSound() & InitInput();

}

void Chip8::EmulateCycle()
{

}

void Chip8::drawGraphics()
{

}

void Chip8::setKeys()
{

}

bool Chip8::loadGame(const char *gamename)
{
    dPrint("Loading " << gamename);
    ifstream Game(gamename,ios::in | ios::binary);
    //Para CONTINUAR https://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer
    if(!Game.is_open())
    {
        dPrint("Erro at opening game file. Exiting!");
        return false;
    }
}
