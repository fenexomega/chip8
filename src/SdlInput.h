#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include <SDL2/SDL_keyboard.h>
#include "interfaces/iInput.h"


class SdlInput final : public iInput
{
	using KeyPairs = std::pair<EmulatorKey, SDL_Scancode>;
public:
	SdlInput();
	SdlInput(const SdlInput&) = delete;
	SdlInput& operator=(const SdlInput&) = delete;
	~SdlInput();

	bool UpdateKeys() override;
	EmulatorKey WaitKeyPress() override;
	
private:
	const unsigned char* m_keyboardState;
	std::vector<KeyPairs> m_keyPairs;
};










#endif // SDLINPUT_H
