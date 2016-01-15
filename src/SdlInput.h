#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include "interfaces/iInput.h"



class SdlInput final : public iInput
{
	using SDLKey = int;
	using KeyPairs = std::pair<EmulatorKey, SDLKey>;
public:
	SdlInput() noexcept;
	SdlInput(const SdlInput&) = delete;
	SdlInput& operator=(const SdlInput&) = delete;
	~SdlInput();
	bool UpdateKeys() noexcept override;
	EmulatorKey WaitKeyPress() noexcept override;
	
private:
	const unsigned char* m_keyboardState;
	std::vector<KeyPairs> m_keyPairs;
};










#endif // SDLINPUT_H
