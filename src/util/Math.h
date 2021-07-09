#pragma once

class Math
{
public:
    // todo: i should add a compiletime log2 function

    // http://prosepoetrycode.potterpcs.net/2015/07/a-simple-constexpr-power-function-c/
    template <typename T>
    inline static constexpr T ipow(const T num, unsigned int pow)
    {
        if (pow >= sizeof(unsigned int) * 8)
            return 0;
        else
            if (pow == 0)
                return 1;
            else
                return num * ipow(num, pow - 1);
    }

    template <typename T>
    inline static constexpr T round(const T num)
    {
        return num + 0.5f;
    }

    template<typename T1, typename T2, typename T3>
    inline static const T1 clamp(const T1 value, const T2 low, const T3 high)
    {
        if (value > high)
            return high;
        else if (value < low)
            return low;

        return value;
    }
};