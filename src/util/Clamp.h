#pragma once

//*****************
//Function name and purpose: clamp, a poor man's imitation of C++17's std::clamp()
//Inputs: T value (what you're clamping), T low, T high (the min and max of clamping range)
//Outputs: T value after being clamped
//*****************
template<typename T>
const T clamp(const T value, const T low, const T high)
{
	if (value > high)
		return high;
	else if (value < low)
		return low;

	return value;
}

//*****************
//Function name and purpose: overload incase value and low + high are different types
//Inputs: T1 value (what you're clamping), T2 low, T2 high (the min and max of clamping range)
//Outputs: T1 value after being clamped
//*****************
template<typename T1, typename T2>
const T1 clamp(const T1 value, const T2 low, const T2 high)
{
	if (value > high)
		return high;
	else if (value < low)
		return low;

	return value;
}

// etc
template<typename T1, typename T2, typename T3>
const T1 clamp(const T1 value, const T2 low, const T3 high)
{
	if (value > high)
		return high;
	else if (value < low)
		return low;

	return value;
}