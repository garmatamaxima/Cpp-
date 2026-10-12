
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constant
{
    inline constexpr double g_gravity{ 9.815 };
}
namespace wordSizes
{
    inline const std::string g_tens[]{ "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy","ninety" };

    inline const std::string g_ones[]{ "","one", "two", "three", "four", "five", "six","seven", "eight", "nine",
                                     "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
                                     "nineteen" };

    inline const std::string g_scale_words[]{ "hundred", "thousand", "million", "billion", "trillion" };
}
namespace math
{
    inline constexpr double pi{ 3.14159265359 };
}
#endif // !CONSTANTS_H
