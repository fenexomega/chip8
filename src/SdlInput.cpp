#include <algorithm>
#include <SDL2/SDL.h>
#include "SdlInput.h"


// Max of keycodes to check. This covers all the ascii table.
#define NUM_KEYCODES 256



SdlInput::SdlInput() noexcept : 
	m_keys ( nullptr ) 
{
	LOG("Creating SdlInput object...");

}

SdlInput::~SdlInput() noexcept
{
	LOG("Destroying SdlInput object...");
}

bool SdlInput::getKey(const int i) const noexcept
{
    return m_keys[i] == SDL_TRUE;
}


void SdlInput::UpdateKeys() noexcept
{

    SDL_PumpEvents();
    m_keys = SDL_GetKeyboardState(NULL);
    static int i = 0;

    // Just a clean for speed up, not using up / down keys for input right now

    /*m_upKeys.clear();
    for(i = 0; i < NUM_KEYCODES; i++)
        if(!getKey(i) && (find(m_currentKeys.begin(),m_currentKeys.end(),i) != m_currentKeys.end()) )
            m_upKeys.push_back(i);
	

    m_downKeys.clear();
    for(i = 0; i < NUM_KEYCODES; i++)
        if(getKey(i) && !(find(m_currentKeys.begin(),m_currentKeys.end(),i) != m_currentKeys.end()))
            m_downKeys.push_back(i);

    */
       
    m_currentKeys.clear();
    for(i = 0; i < NUM_KEYCODES; i++)
        if(getKey(i))
            m_currentKeys.push_back(i);
	
}





bool SdlInput::IsKeyUp(int key) const noexcept
{
    return find(m_upKeys.begin(),m_upKeys.end(),key) != m_upKeys.end();

}

bool SdlInput::IsKeyDown(int key) const noexcept
{
    return find(m_downKeys.begin(),m_downKeys.end(),key) != m_downKeys.end();

}


bool SdlInput::IsKeyPressed(int key) const noexcept
{
   return find(m_currentKeys.begin(),m_currentKeys.end(),key) != m_currentKeys.end();
	
}


int SdlInput::GetPressedKeyValue() const noexcept
{
	return ((m_currentKeys.size() > 0) ? m_currentKeys[0] : NO_KEY_PRESSED);
}
