#ifndef IINPUT
#define IINPUT




#define NO_KEY_PRESSED -1
#define ESCAPE_KEY_CODE -2
#define RETURN_KEY_CODE -3

class iInput
{
public:
	virtual void UpdateKeys() = 0;
	//virtual bool IsKeyUp(const int key) const = 0;
	//virtual bool IsKeyDown(const int key) const = 0;
	virtual bool IsKeyPressed(const int key) const = 0;
	virtual int GetPressedKeyValue() const = 0;
	virtual ~iInput(){}
};

#endif // IINPUT

