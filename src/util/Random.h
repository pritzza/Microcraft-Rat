//#pragma once
//
//#include <limits>
//#include <random>
//
//class Random
//{
//private:
//	// keyword mutable makes data member's value changeable within const methods
//	mutable std::mt19937 mt;	// Mersenne Twister pseudo-random generator
//	int seed;
//
//public:
//	Random()
//		:
//		seed{ std::random_device{}() },
//		mt{ seed }
//	{}
//
//	Random(const int seed)
//		:
//		seed{ seed },
//		mt{ seed }
//	{}
//
//	void seed(const int seed) { this->mt.seed(seed); }
//	const int getSeed() const { return this->seed;   }
//
//	inline const int getNum(
//		const int min = std::numeric_limits<int>::min(),
//		const int max = std::numeric_limits<int>::max()
//	) const
//	{
//		if (min >= max)
//			return 0;	// error case
//
//		std::uniform_int_distribution<int> num(min, max);
//		return num(this->mt);		// generates number between min and max inclusive
//	}
//
//	//inline const bool isUnder(const int odds, const int in = 100) const
//	//{
//	//	std::uniform_int_distribution<int> num(0, in);
//	//	return num(this->mt) < odds;
//	//}
//};