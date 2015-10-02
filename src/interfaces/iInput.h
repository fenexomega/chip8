#ifndef IINPUT
#define IINPUT

#include <iostream>
#define LOG(X) std::cout << X << std::endl

class iInput
{
public:
    virtual void UpdateKeys() = 0;
    virtual bool IsKeyUp(int key) = 0;
    virtual bool IsKeyDown(int key) = 0;
    virtual bool IsKeyPressed(int key) = 0;
	virtual int GetPressedKeyValue() = 0;
    virtual ~iInput(){}
};

#endif // IINPUT

