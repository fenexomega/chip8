#include <algorithm>
#include <SDL2/SDL.h>
#include "SdlInput.h"


// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256

SdlInput::SdlInput() noexcept :
m_currentKeys{ {  0x1, SDL_SCANCODE_1 }, { 0x2, SDL_SCANCODE_2 }, { 0x3, SDL_SCANCODE_3 }, { 0xc, SDL_SCANCODE_4 },
				{ 0x4, SDL_SCANCODE_Q }, { 0x5, SDL_SCANCODE_W }, { 0x6, SDL_SCANCODE_E }, { 0xd, SDL_SCANCODE_R },
				{ 0x7, SDL_SCANCODE_A }, { 0x8, SDL_SCANCODE_S }, { 0x9, SDL_SCANCODE_D }, { 0xe, SDL_SCANCODE_F },
				{ 0xa, SDL_SCANCODE_Z }, { 0x0, SDL_SCANCODE_X }, { 0xb, SDL_SCANCODE_C }, { 0xf, SDL_SCANCODE_V },
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
	
	m_upKeys.clear();
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
	auto itr = m_currentKeys.find(key);
	return ( itr != m_currentKeys.end() ) ? m_keys[itr->second] == SDL_TRUE : false;
}


int SdlInput::GetPressedKeyValue() const noexcept
{
	auto itr = std::find_if(m_currentKeys.begin(), m_currentKeys.end(), [&](const std::pair<int,int> &keyPair){return m_keys[keyPair.second] == SDL_TRUE;});
	return (itr != m_currentKeys.end()) ? itr->first : NO_KEY_PRESSED;
}







