#ifndef IINPUT
#define IINPUT

#include <iostream>
#define LOG(X) std::cout << X << std::endl
#define NO_KEY_PRESSED -1

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

