#pragma once
#include <random>
#include <chrono>

class Random
{
public:
	static int generate(int min, int max)
	{
		std::uniform_int_distribution uid{ min, max };
		return uid(mt);
	}

private:
	static inline std::random_device rd{};
	
	static inline std::seed_seq ss{ 
		rd(), rd(), rd(), rd(), rd(), rd(), rd(),
		static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())
	};

	static inline std::mt19937 mt{ ss };
};