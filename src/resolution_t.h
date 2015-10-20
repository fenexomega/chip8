#ifndef RESOLUTION_T_H
#define RESOLUTION_T_H



struct resolution_t
{

	inline resolution_t();
	inline resolution_t(size_t x, size_t y);

	inline void set(size_t x, size_t y);
	inline operator size_t();


	size_t x_, y_;
	size_t total_;

};


inline resolution_t::resolution_t() : x_ (0), y_(0), total_(0)
{}

inline resolution_t::resolution_t(size_t x, size_t y) : x_ (x), y_(y), total_(x*y)
{}	


inline void resolution_t::set(size_t x, size_t y)
{
	x_ = x;
	y_ = y;
	total_ = x_ * y_;
}

inline resolution_t::operator size_t()
{
	return total_;
}






#endif