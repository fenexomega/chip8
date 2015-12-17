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
	void UpdateKeys() noexcept;
	bool IsKeyPressed(const EmulatorKey key) const noexcept;
	uint8_t GetPressedKeyValue() const noexcept;
	
private:
	const unsigned char* m_keyboardState;
	std::vector<std::pair<int,int>> m_keyPairs;
};













#endif // SDLINPUT_H
