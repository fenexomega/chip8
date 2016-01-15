#include <SDL2/SDL.h>
#include "SdlInput.h"
#include "utility/log.h"


SdlInput::SdlInput() noexcept :

	m_keyboardState(SDL_GetKeyboardState(NULL)),
	m_keyPairs
	{
		{ EmulatorKey::KEY_0, SDL_SCANCODE_KP_0}, { EmulatorKey::KEY_1, SDL_SCANCODE_KP_7}, { EmulatorKey::KEY_2, SDL_SCANCODE_KP_8}, 
		{ EmulatorKey::KEY_3, SDL_SCANCODE_KP_9}, { EmulatorKey::KEY_4, SDL_SCANCODE_KP_4}, { EmulatorKey::KEY_5, SDL_SCANCODE_KP_5}, 
		{ EmulatorKey::KEY_6, SDL_SCANCODE_KP_6}, { EmulatorKey::KEY_7, SDL_SCANCODE_KP_1}, { EmulatorKey::KEY_8, SDL_SCANCODE_KP_2}, 
		{ EmulatorKey::KEY_9, SDL_SCANCODE_KP_3}, { EmulatorKey::KEY_A, SDL_SCANCODE_KP_DIVIDE}, { EmulatorKey::KEY_B, SDL_SCANCODE_KP_MULTIPLY}, 
		{ EmulatorKey::KEY_C, SDL_SCANCODE_KP_MINUS}, { EmulatorKey::KEY_D, SDL_SCANCODE_KP_PLUS}, { EmulatorKey::KEY_E, SDL_SCANCODE_KP_PERIOD}, 
		{ EmulatorKey::KEY_F, SDL_SCANCODE_KP_ENTER}, { EmulatorKey::RESET, SDL_SCANCODE_RETURN}, { EmulatorKey::ESCAPE, SDL_SCANCODE_ESCAPE}
	}
{
	LOG("Creating SdlInput object...");
	this->UpdateKeys();
}



SdlInput::~SdlInput()
{
	LOG("Destroying SdlInput object...");
}




bool SdlInput::UpdateKeys() noexcept
{
	SDL_PumpEvents();
	for(const auto &keyPair : m_keyPairs)
		if(m_keyboardState[ keyPair.second ] == SDL_TRUE) {
			m_currentKey =  keyPair.first;
			return true;
		}

	m_currentKey = EmulatorKey::NO_KEY_PRESSED;
	return false;
}




EmulatorKey SdlInput::WaitKeyPress() noexcept
{
	while(true)
	{
		SDL_PumpEvents();
		for(auto &keyPair : m_keyPairs)
			if(m_keyboardState[ keyPair.second ] == SDL_TRUE)
				return keyPair.first;
	};

}






