
#include <iostream>
#include <string>
#include <string_view>
#include <bitset>
#include <cstdint>
#include <stdfloat>

#include "bitsets.h"

inline static constexpr float midpoint(float start, float end)
{
    return (start + end) / 2;
}
inline static constexpr double midpoint(double start, double end)
{
    return (start + end) / 2;
}

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

// int main()
//{
//    incrementAndPrint();
//    incrementAndPrint();
//    incrementAndPrint();
//
//    return 0;
//}