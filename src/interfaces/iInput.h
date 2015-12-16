#ifndef IINPUT
#define IINPUT



enum EmulatorKey: unsigned char
{
	//Chip8 keypad, which will be emulated in the computer's keypad
	KEY_0,
	KEY_1,   KEY_2,   KEY_3, 
	KEY_4,   KEY_5,   KEY_6,
	KEY_7,   KEY_8,   KEY_9,
	KEY_A,   KEY_B,   KEY_C,
	KEY_D,   KEY_E,   KEY_F,
	
	
	// system keys
	NO_KEY_PRESSED,
	RESET,
	ESCAPE
};
constexpr int MAX_KEY_OFFSET = 18;

class iInput
{
public:
	virtual void UpdateKeys() noexcept = 0;
	//virtual bool IsKeyUp(const int key) const = 0;
	//virtual bool IsKeyDown(const int key) const = 0;
	virtual bool IsKeyPressed(const EmulatorKey key) const noexcept = 0;
	virtual EmulatorKey GetPressedKeyValue() const noexcept = 0;
	virtual ~iInput() {}
};

#endif // IINPUT

