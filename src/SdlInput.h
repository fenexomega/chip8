#ifndef SDLINPUT_H
#define SDLINPUT_H

#include <vector>
#include "interfaces/iInput.h"

using std::vector;

class SdlInput : public iInput
{
    // iInput interface
public:
    void UpdateKeys() noexcept;
    bool IsKeyUp(const int key)         const noexcept;
    bool IsKeyDown(const int key)       const noexcept;
    bool IsKeyPressed(const int key)    const noexcept;
    int GetPressedKeyValue()            const noexcept;
    SdlInput();
    ~SdlInput();

private:
    bool getKey(const int i) const noexcept;

    vector<int> m_upKeys;
    vector<int> m_downKeys;
    vector<int> m_currentKeys;
    const uint8_t* m_keys;
    bool m_userWannaCloseWindow;

};

#endif // SDLINPUT_H
