#include <algorithm>
#include <SDL2/SDL.h>
#include "SdlInput.h"
#include "utility/log.h"

// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256

//all 16 keys of TelMac + ESC, RESET, NO_KEY_PRESSED
SdlInput::SdlInput() noexcept :
m_keyPairs	{{KEY_0, SDL_SCANCODE_KP_0}, 
		{KEY_1, SDL_SCANCODE_KP_7}, {KEY_2, SDL_SCANCODE_KP_8}, {KEY_3, SDL_SCANCODE_KP_9},
		{KEY_4, SDL_SCANCODE_KP_4}, {KEY_5, SDL_SCANCODE_KP_5}, {KEY_6, SDL_SCANCODE_KP_6}, 
		{KEY_7, SDL_SCANCODE_KP_1}, {KEY_8, SDL_SCANCODE_KP_2}, {KEY_9, SDL_SCANCODE_KP_3}, 
		{KEY_A, SDL_SCANCODE_KP_DIVIDE}, {KEY_B, SDL_SCANCODE_KP_MULTIPLY}, {KEY_C, SDL_SCANCODE_KP_MINUS},
		{KEY_D, SDL_SCANCODE_KP_PLUS}, {KEY_E, SDL_SCANCODE_KP_PERIOD}, {KEY_F, SDL_SCANCODE_KP_ENTER},
		{RESET, SDL_SCANCODE_RETURN}, {ESCAPE, SDL_SCANCODE_ESCAPE}}
	
{
	LOG("Creating SdlInput object...");
	this->UpdateKeys();
}



SdlInput::~SdlInput()
{
	
	LOG("Destroying SdlInput object...");
}






bool SdlInput::IsKeyPressed(const EmulatorKey key)  const noexcept
{
	if(key > MAX_KEY_OFFSET)
		return false;
	else
		return m_keyboardState[ m_keyPairs[key].second ] == SDL_TRUE;
}


EmulatorKey SdlInput::GetPressedKeyValue() const noexcept
{
	auto itr = std::find_if(m_keyPairs.begin(), m_keyPairs.end(),
		[&](auto &keyPair) {return m_keyboardState[keyPair.second] == SDL_TRUE; });
		
	return (itr != m_keyPairs.end()) ? (EmulatorKey)itr->first : NO_KEY_PRESSED;
}



inline void SdlInput::UpdateKeys() noexcept
{

	SDL_PumpEvents();
	m_keyboardState = SDL_GetKeyboardState(NULL);

}







