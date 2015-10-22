#ifndef RESOLUTION_T_H
#define RESOLUTION_T_H



struct resolution_t
{

	inline resolution_t();
	inline resolution_t(const int new_x, const int new_y);

	inline void set(const int newX, const int newY);
	inline operator size_t();


	int x, y;
	size_t total;

};


inline resolution_t::resolution_t() : x(0), y(0), total(0)
{}

inline resolution_t::resolution_t(const int new_x, const int new_y) : x(new_x), y(new_y), total(x*y)
{}


inline void resolution_t::set(const int new_x, const int new_y)
{
	x = new_x;
	y = new_y;
	total = x * y;
}

inline resolution_t::operator size_t()
{
	return total;
}






#endif