#include "SdlInput.h"

#include <SDL2/SDL.h>

#include <algorithm>


// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256



SdlInput::SdlInput()
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
    return find(m_currentKeys.begin(),m_currentKeys.end(),key) != m_currentKeys.end();

}


