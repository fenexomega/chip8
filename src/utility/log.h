#ifndef LOG_H
#define LOG_H

#define __CHIP8_GUI__


#include <iostream>
#define LOG(x) std::cout << x << std::endl



#ifndef __CHIP8_GUI__
#define LOGerr(x) std::cerr << x << std::endl


#else
#include <sstream>
extern std::stringstream global_errorStream;

#define LOGerr(x) global_errorStream << x << std::endl

inline
std::string GetEmulatorErrorMsg()
{
	std::string error = global_errorStream.str();
	global_errorStream.str(std::string());		// clear global_errorStream
	return std::move(error);
}

#endif

#endif // LOG_H

