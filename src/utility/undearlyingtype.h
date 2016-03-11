#ifndef UNDERLYING_TYPE_H
#define UNDERLYING_TYPE_H
#include <type_traits>
template<class T>
using underlying_type_t = typename std::underlying_type<T>::type;


template<class T>
inline underlying_type_t<T> toUType(T t)
{
	return static_cast<underlying_type_t<T>>(t);
}







#endif
