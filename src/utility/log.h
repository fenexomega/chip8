#ifndef LOG_H
#define LOG_H




#include <iostream>
#define LOG(x) std::cout << x << std::endl



#ifndef QT_GUI_LIB
#define LOGerr(x) std::cerr << x << std::endl


#else
#include <sstream>
static std::stringstream global_errorStream;

#define LOGerr(x) global_errorStream << x << std::endl

static inline
std::string GetLogErrorMsg()
{
	std::string error = global_errorStream.str();
	global_errorStream.str(std::string());		// clear global_errorStream
	return std::move(error);
}

#endif

#endif // LOG_H

