#ifndef IINPUT_H
#define IINPUT_H

// system constants
enum class EmulatorKey : uint8_t
{
	//Chip8 keypad, which will be emulated in the computer's keypad
	KEY_0,
	KEY_1, KEY_2, KEY_3,
	KEY_4, KEY_5, KEY_6,
	KEY_7, KEY_8, KEY_9,
	KEY_A, KEY_B, KEY_C,
	KEY_D, KEY_E, KEY_F,


	// system keys
	RESET,
	ESCAPE,

	NO_KEY_PRESSED, // does not count as a key, but is returned if none of the others are pressed
	MAX_KEY_OFFSET = 17 // do not count as a key.
};

class iInput
{
public:
	virtual ~iInput() = default;

	bool IsKeyPressed(const EmulatorKey key) const noexcept;
	auto GetPressedKeyValue() const noexcept;

	virtual bool UpdateKeys() noexcept = 0;          // return true if there is a key press, store the key in m_currentKey
	virtual EmulatorKey WaitKeyPress() noexcept = 0; // Wait for the keypress and return the EmulatorKey

protected:
	EmulatorKey m_currentKey;


};




inline auto iInput::GetPressedKeyValue() const noexcept
{
	return static_cast<std::underlying_type_t<EmulatorKey>>(m_currentKey);
}

inline bool iInput::IsKeyPressed(const EmulatorKey key)  const noexcept
{
	return m_currentKey == key;
}



#endif // IINPUT

