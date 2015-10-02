#include "SdlInput.h"

#include <SDL2/SDL.h>

#include <algorithm>


// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256



SdlInput::SdlInput() : 
	m_keymap{
		{ SDLK_1, 0x1 },{ SDLK_2, 0x2 },{ SDLK_3, 0x3 },{ SDLK_4, 0xC },
		{ SDLK_q, 0x4 },{ SDLK_w, 0x5 },{ SDLK_e, 0x6 },{ SDLK_r, 0xD },
		{ SDLK_a, 0x7 },{ SDLK_s, 0x8 },{ SDLK_d, 0x9 },{ SDLK_f, 0xE },
		{ SDLK_z, 0xA },{ SDLK_x, 0x0 },{ SDLK_c, 0xB },{ SDLK_v, 0xF },
		{ SDLK_5, 0x5 },{ SDLK_6, 0x6 },{ SDLK_7, 0x7 },
		{ SDLK_8, 0x8 },{ SDLK_9, 0x9 },{ SDLK_0, 0x0 }}
{
	LOG("Creating SdlInput object...");

}

SdlInput::~SdlInput()
{
	LOG("Destroying SdlInput object...");
}

bool SdlInput::getKey(int i)
{
    return m_keys[i] == SDL_TRUE;
}


void SdlInput::UpdateKeys()
{

    SDL_PumpEvents();
    m_keys = SDL_GetKeyboardState(NULL);
    int i;

    m_upKeys.clear();
    for(i = 0; i < NUM_KEYCODES; i++)
        if(!getKey(i) && (find(m_currentKeys.begin(),m_currentKeys.end(),i) != m_currentKeys.end()) )
            m_upKeys.push_back(i);

    m_downKeys.clear();
    for(i = 0; i < NUM_KEYCODES; i++)
        if(getKey(i) && !(find(m_currentKeys.begin(),m_currentKeys.end(),i) != m_currentKeys.end()))
            m_downKeys.push_back(i);

    m_currentKeys.clear();
    for(i = 0; i < NUM_KEYCODES; i++)
        if(getKey(i))
            m_currentKeys.push_back(i);
}

bool SdlInput::IsKeyUp(int key)
{
    return find(m_upKeys.begin(),m_upKeys.end(),key) != m_upKeys.end();

}

bool SdlInput::IsKeyDown(int key)
{
    return find(m_downKeys.begin(),m_downKeys.end(),key) != m_downKeys.end();

}

bool SdlInput::IsKeyPressed(int key)
{
   // return find(m_currentKeys.begin(),m_currentKeys.end(),key) != m_currentKeys.end();
	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			auto itr = m_keymap.find(m_event.key.keysym.sym);
			if (itr != m_keymap.end())
				return (itr->second == key);
	}

	return false;
	
	
}

int SdlInput::GetPressedKeyValue()
{	
	SDL_PollEvent(&m_event);
	switch(m_event.type)
	{
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			auto itr = m_keymap.find(m_event.key.keysym.sym);
			if (itr != m_keymap.end())
				return itr->second;
	}
	
	return -1;
}
