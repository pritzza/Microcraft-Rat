#pragma once

// http://prosepoetrycode.potterpcs.net/2015/07/a-simple-constexpr-power-function-c/
class Math
{
public:
    // todo: i should add a compiletime log2 function

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
};