#ifndef SDLINPUT_H
#define SDLINPUT_H

#include <vector>
#include <unordered_map>
#include "interfaces/iInput.h"
#include <SDL2/SDL.h>

using std::vector;

class SdlInput : public iInput
{
    // iInput interface
public:
    void UpdateKeys();
    bool IsKeyUp(int key);
    bool IsKeyDown(int key);
    bool IsKeyPressed(int key);
    SdlInput();
    ~SdlInput();

private:
    bool getKey(int i);

	SDL_Event m_event;
    vector<int> m_upKeys;
    vector<int> m_downKeys;
    vector<int> m_currentKeys;
    const Uint8* m_keys;
    bool m_userWannaCloseWindow;
	std::unordered_map<int, int> m_keymap;


};

#endif // SDLINPUT_H
