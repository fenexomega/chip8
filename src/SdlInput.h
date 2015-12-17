#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include "interfaces/iInput.h"



class SdlInput final : public iInput
{
// iInput interface
public:
	SdlInput() noexcept;
	~SdlInput();
	bool UpdateKeys() noexcept;
	bool IsKeyPressed(const EmulatorKey key) const noexcept;
	EmulatorKey GetPressedKeyValue() const noexcept;
	EmulatorKey WaitKeyPress() noexcept;
	
private:
	const unsigned char* m_keyboardState;
	EmulatorKey m_currentKey;
	std::vector<std::pair<EmulatorKey,int>> m_keyPairs;
};




inline EmulatorKey SdlInput::GetPressedKeyValue() const noexcept
{
	return m_currentKey;
}









#endif // SDLINPUT_H
