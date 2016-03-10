#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include <SDL2/SDL_keyboard.h>
#include "../interfaces/iInput.h"

extern SDL_Event g_sdlEvent;
extern void UpdateSdlEvents();

class SdlInput final : public iInput
{
	using KeyPairs = std::pair<EmulatorKey, SDL_Scancode>;
public:
	SdlInput();
	SdlInput(const SdlInput&) = delete;
	SdlInput& operator=(const SdlInput&) = delete;
	~SdlInput();

	bool IsKeyPressed(const EmulatorKey key) const override;
	EmulatorKey GetPressedKey() const override;
	bool UpdateKeys() override;
	EmulatorKey WaitKeyPress(void* predArg, WaitKeyPressPred pred) override;

	
private:
	const unsigned char* m_keyboardState;
	std::vector<KeyPairs> m_keyPairs;
	
};










#endif // SDLINPUT_H
