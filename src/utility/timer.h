#ifndef TIMER_H
#define TIMER_H
#include <ctime>


constexpr unsigned long long int operator""_sec(unsigned long long int x) { return x * CLOCKS_PER_SEC; }


class Timer
{
public:
	Timer() noexcept = default;
	Timer(const unsigned long target) noexcept;
	void SetTargetTime(const unsigned long target);
	bool Finished() const;
	void Start();
private:
	std::clock_t m_clk;
	std::clock_t m_target;
};


inline Timer::Timer(const unsigned long target) noexcept 
	: m_clk(std::clock()), 
	m_target(target)
{
	
}

inline void Timer::SetTargetTime(const unsigned long target)
{
	m_target = target;
}

inline bool Timer::Finished() const
{
	return (( std::clock() - m_clk ) > m_target );
}

inline void Timer::Start()
{
	m_clk = std::clock();
}












#endif
