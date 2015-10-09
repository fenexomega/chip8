#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <unordered_map>
#include "interfaces/iInput.h"


using std::unordered_map;

class SdlInput : public iInput
{
    // iInput interface
public:
    inline void UpdateKeys() noexcept;
	//virtual bool IsKeyUp(const int key) const noexcept;
	//virtual bool IsKeyDown(const int key) const noexcept;
    bool IsKeyPressed(const int key)	const noexcept;
    int GetPressedKeyValue()			const noexcept;
    SdlInput() noexcept;
    ~SdlInput() noexcept;

private:
	bool getKey(const int i) const noexcept;
    unordered_map<int,int> m_currentKeys;
    const uint8_t* m_keys;
	

};

#endif // SDLINPUT_H
