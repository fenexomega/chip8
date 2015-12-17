#ifndef IINPUT
#define IINPUT



enum EmulatorKey: uint8_t
{
	//Chip8 keypad, which will be emulated in the computer's keypad
	KEY_0,
	KEY_1,   KEY_2,   KEY_3, 
	KEY_4,   KEY_5,   KEY_6,
	KEY_7,   KEY_8,   KEY_9,
	KEY_A,   KEY_B,   KEY_C,
	KEY_D,   KEY_E,   KEY_F,
	
	
	// system keys
	RESET,
	ESCAPE,
	
	NO_KEY_PRESSED // does not count as a key, but is returned if none of the others are pressed
};

constexpr int MAX_KEY_OFFSET = 17;

class iInput
{
public:
	virtual ~iInput() {}
	virtual void UpdateKeys() noexcept = 0;
	virtual bool IsKeyPressed(const EmulatorKey key) const noexcept = 0;
	virtual uint8_t GetPressedKeyValue() const noexcept = 0;
	
};

#endif // IINPUT

