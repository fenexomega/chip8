#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include "interfaces/iInput.h"

using KeyPairs = std::pair<EmulatorKey,int>;


class SdlInput final : public iInput
{
public:
	SdlInput() noexcept;
	~SdlInput();
	bool UpdateKeys() noexcept override;
	EmulatorKey WaitKeyPress() noexcept override;
	
private:
	const unsigned char* m_keyboardState;
	std::vector<KeyPairs> m_keyPairs;
};










#endif // SDLINPUT_H
