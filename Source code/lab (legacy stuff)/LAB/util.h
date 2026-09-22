#pragma once

namespace util
{   
    template <typename T, typename P> T clamp(T value, P min, P max)
    {
        if (value > max) { return max; }
        else if (value < min) { return min; }
        return value;
    }

    template <typename T, typename P> T clampmin(T value, P min)
    {
        if (value < min) { return min; }
        return value;
    }



};