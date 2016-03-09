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

	bool IsKeyPressed(const EmulatorKey key) const override;
	uint8_t GetPressedKeyValue() const override;
	bool UpdateKeys() override;
	EmulatorKey WaitKeyPress(WaitKeyPressPred pred) override;

	
private:
	const unsigned char* m_keyboardState;
	EmulatorKey m_currentKey;
	std::vector<KeyPairs> m_keyPairs;
};










#endif // SDLINPUT_H
