#include <SDL2/SDL.h>
#include "SdlInput.h"
#include "../utility/log.h"
#include "../utility/undearlyingtype.h"

extern SDL_Event g_sdlEvent;
extern void UpdateSdlEvents();

SdlInput::SdlInput() :
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
}

SdlInput::~SdlInput()
{
	LOG("Destroying SdlInput object...");
}




bool SdlInput::Initialize()
{
	return true;	
}



void SdlInput::Dispose() noexcept
{
	// ...
}


bool SdlInput::UpdateKeys()
{
	UpdateSdlEvents();
	return g_sdlEvent.type == SDL_KEYDOWN 
		|| g_sdlEvent.type == SDL_KEYUP;
	
}


void SdlInput::SetKey(const EmulatorKey key, int value)
{
	m_keyPairs[toUType(key)].second = static_cast<SDL_Scancode>(value);
}



bool SdlInput::IsKeyPressed(const EmulatorKey key) const
{
	return m_keyboardState[m_keyPairs[toUType(key)].second] == SDL_TRUE;
}


EmulatorKey SdlInput::GetPressedKey() const
{
	for (const auto& keyPair : m_keyPairs) 
	{
		if (m_keyboardState[keyPair.second] == SDL_TRUE)
			return keyPair.first;
	}

	return EmulatorKey::NO_KEY_PRESSED;
}



EmulatorKey SdlInput::WaitKeyPress()
{
	if (m_waitClbk != nullptr)
	{
		while (m_waitClbk(m_waitClbkArg))
		{
			for (auto &keyPair : m_keyPairs)
				if (m_keyboardState[keyPair.second] == SDL_TRUE)
					return keyPair.first;
		};
	}

	return EmulatorKey::NO_KEY_PRESSED;
}


void SdlInput::SetWaitKeyPressCallback(WaitKeyPressCallback callback, void* arg) {
	m_waitClbk = callback;
	m_waitClbkArg = arg;
}


void SdlInput::SetResetCallback(ResetCallback resetClbk, void* arg) {
	m_resetClbk = resetClbk;
	m_resetClbkArg = arg;
}

void SdlInput::SetEscapeCallback(EscapeCallback escapeClbk, void* arg) {
	m_escapeClbk = escapeClbk;
	m_escapeClbkArg = arg;
}
