#include <algorithm>
#include <SDL2/SDL.h>
#include "SdlInput.h"


// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256

SdlInput::SdlInput() noexcept :
m_currentKeys{ { SDL_SCANCODE_1, 0x1 }, {SDL_SCANCODE_2, 0x2}, { SDL_SCANCODE_3, 0x3 }, {SDL_SCANCODE_4,0xc}, 
				{SDL_SCANCODE_Q, 0x4},{ SDL_SCANCODE_W, 0x5}, { SDL_SCANCODE_E, 0x6}, { SDL_SCANCODE_R, 0xd}, 
				{ SDL_SCANCODE_A, 0x7}, { SDL_SCANCODE_S,0x8},{ SDL_SCANCODE_D,0x9}, { SDL_SCANCODE_F,0xe}, 
				{ SDL_SCANCODE_Z,0xa}, { SDL_SCANCODE_X,0x0}, { SDL_SCANCODE_C,0xb}, { SDL_SCANCODE_V,0xf}, 
				{ SDL_SCANCODE_ESCAPE, SDL_SCANCODE_ESCAPE} }
{
	LOG("Creating SdlInput object...");
	this->UpdateKeys();
}

SdlInput::~SdlInput() noexcept
{
	LOG("Destroying SdlInput object...");
}

bool SdlInput::getKey(const int i) const noexcept
{
	return m_keys[i] == SDL_TRUE;
}


inline void SdlInput::UpdateKeys() noexcept
{

	SDL_PumpEvents();
	m_keys = SDL_GetKeyboardState(NULL);
	/*
	//static int i = 0;



	/*m_upKeys.clear();
	for(i = 0; i < NUM_KEYCODES; i++)
	if(!getKey(i) && (find(m_currentKeys.begin(),m_currentKeys.end(),i) != m_currentKeys.end()) )
	m_upKeys.push_back(i);

	m_downKeys.clear();
	for(i = 0; i < NUM_KEYCODES; i++)
	if(getKey(i) && !(find(m_currentKeys.begin(),m_currentKeys.end(),i) != m_currentKeys.end()))
	m_downKeys.push_back(i);
	

	m_currentKeys.clear();
	for (i = 0; i < NUM_KEYCODES; i++)
		if (getKey(i))
			m_currentKeys.push_back(i);

	*/
	
}


/*

bool SdlInput::IsKeyUp(int key) const noexcept
{
	return find(m_upKeys.begin(),m_upKeys.end(),key) != m_upKeys.end();

}

bool SdlInput::IsKeyDown(int key) const noexcept
{
	return find(m_downKeys.begin(),m_downKeys.end(),key) != m_downKeys.end();

}

*/







bool SdlInput::IsKeyPressed(const int key)  const noexcept
{
	for (auto itr = m_currentKeys.begin(); itr != m_currentKeys.end(); itr++)
		if (itr->second == key)
			return m_keys[itr->first] == SDL_TRUE;

	return false;
}


int SdlInput::GetPressedKeyValue() const noexcept
{
	for (auto itr = m_currentKeys.begin(); itr != m_currentKeys.end(); itr++)
		if (m_keys[itr->first] == SDL_TRUE)
			return itr->second;

	return NO_KEY_PRESSED;
}







