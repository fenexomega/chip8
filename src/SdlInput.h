#ifndef SDLINPUT_H
#define SDLINPUT_H

#include <vector>
#include "interfaces/iInput.h"
#include <SDL2/SDL.h>

using std::vector;

class SdlInput : public iInput
{
// SINGLETON
    // iInput interface
public:
    static SdlInput GetSDLInput();
    void UpdateKeys();
    bool IsKeyUp(int key);
    bool IsKeyDown(int key);
    bool IsKeyPressed(int key);


private:
    SdlInput();
    ~SdlInput();

    bool getKey(int i);

    vector<int> m_upKeys;
    vector<int> m_downKeys;
    vector<int> m_currentKeys;
    const Uint8* m_keys;
    bool m_userWannaCloseWindow;


};

#endif // SDLINPUT_H
