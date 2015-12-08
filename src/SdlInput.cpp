#include <algorithm>
#include <SDL2/SDL.h>
#include "SdlInput.h"
#include "utility/log.h"

// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256

//all 16 keys of TelMac + ESC
SdlInput::SdlInput() noexcept :
m_currentKeys{ 	{ 0x1, SDL_SCANCODE_KP_7 }, { 0x2, SDL_SCANCODE_KP_8 }, { 0x3, SDL_SCANCODE_KP_9 }, { 0xc, SDL_SCANCODE_KP_MULTIPLY },
		{ 0x4, SDL_SCANCODE_KP_4 }, { 0x5, SDL_SCANCODE_KP_5 }, { 0x6, SDL_SCANCODE_KP_6 }, { 0xd, SDL_SCANCODE_KP_MINUS },
		{ 0x7, SDL_SCANCODE_KP_1 }, { 0x8, SDL_SCANCODE_KP_2 }, { 0x9, SDL_SCANCODE_KP_3 }, { 0xe, SDL_SCANCODE_KP_PLUS },
		{ 0xa, SDL_SCANCODE_KP_0 }, { 0x0, SDL_SCANCODE_KP_COMMA }, { 0xb, SDL_SCANCODE_KP_ENTER }, { 0xf, SDL_SCANCODE_KP_PERIOD },
		{ ESCAPE_KEY_CODE, SDL_SCANCODE_ESCAPE}, { RETURN_KEY_CODE, SDL_SCANCODE_RETURN } }
{
	LOG("Creating SdlInput object...");
	this->UpdateKeys();
	
}



SdlInput::~SdlInput() noexcept
{
	
	LOG("Destroying SdlInput object...");
}






bool SdlInput::IsKeyPressed(const int key)  const noexcept
{
	
	return m_keys[ m_currentKeys.at(key) ] == SDL_TRUE;
}


int SdlInput::GetPressedKeyValue() const noexcept
{
	auto itr = std::find_if(m_currentKeys.begin(), m_currentKeys.end(),
		[&](const std::pair<const int,SDL_Scancode> &keyPair) {return m_keys[keyPair.second] == SDL_TRUE; });
	return (itr != m_currentKeys.end()) ? itr->first : NO_KEY_PRESSED;
}



inline void SdlInput::UpdateKeys() noexcept
{

	SDL_PumpEvents();
	m_keys = SDL_GetKeyboardState(NULL);

}







