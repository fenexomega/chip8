#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <unordered_map>
#include <SDL2/SDL.h>
#include "interfaces/iInput.h"


using std::unordered_map;

class SdlInput : public iInput
{
// iInput interface
public:
    inline void UpdateKeys() noexcept;
    bool IsKeyPressed(const int key)	const noexcept;
    int GetPressedKeyValue()	const noexcept;
    SdlInput() noexcept;
    ~SdlInput() noexcept;

private:
    unordered_map<int,SDL_Scancode> m_currentKeys;
    const uint8_t* m_keys;


};

#endif // SDLINPUT_H
