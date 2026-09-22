#pragma once
#include <cstdint>

namespace util
{   
    template <typename T> T clamp(T value, T min, T max)
    {
        if (value > max) { return max; }
        else if (value < min) { return min; }
        return value;
    }
    template <typename T> T clamp(T value, int min, int max)
    {
        if (value > max) { return max; }
        else if (value < min) { return min; }
        return value;
    }

    template <typename T> T clampmin(T value, T min)
    {
        if (value < min) { return min; }
        return value;
    }
    template <typename T> T clampmin(T value, int min)
    {
        if (value < min) { return min; }
        return value;
    }

};

namespace RustTypedefs // type aliases that take type identifiers from rust language.
{
    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using f32 = float;
    using f64 = double;
}