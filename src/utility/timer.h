#ifndef TIMER_H
#define TIMER_H
#include <chrono>

constexpr std::chrono::microseconds operator""_sec(unsigned long long x) { 
	using namespace std::chrono;  
	return duration_cast<microseconds>(seconds(x)); 
}

constexpr std::chrono::microseconds operator""_milli(unsigned long long x) {
	using namespace std::chrono;
	return duration_cast<microseconds>(milliseconds(x));
}

constexpr std::chrono::microseconds operator""_micro(unsigned long long x) { 
	return std::chrono::microseconds(x); 
}


class Timer
{
public:
	Timer() noexcept = default;
	Timer(std::chrono::microseconds target) noexcept;
	void SetTargetTime(std::chrono::microseconds target);
	bool Finished() const;
	void Start();
private:
	std::chrono::steady_clock::time_point m_clk = std::chrono::steady_clock::now();
	std::chrono::microseconds m_target;
};


inline Timer::Timer(std::chrono::microseconds target) noexcept
	: m_target(target)
{
	
}

inline void Timer::SetTargetTime(std::chrono::microseconds target)
{
	m_target = target;
}

inline bool Timer::Finished() const
{
	return (( std::chrono::steady_clock::now() - m_clk ) > m_target );
}

inline void Timer::Start()
{
	m_clk = std::chrono::steady_clock::now();
}












#endif
