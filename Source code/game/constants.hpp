#pragma once
#ifndef CONSTANTS_HEADER
#define CONSTANTS_HEADER

#include "raylib.h"

inline namespace Globals
{
    int screenWidth = 1600;
    int screenHeight = 900;


    constexpr int worldX = 5500;
    constexpr int worldY = 5500;

    constexpr float gravity{ 9.81f };
    float dt{};
    Vector2 mousePos{};

    constexpr int projectileLimit{ 1000 };
    int playermode{ 0 };
    int ids{ 1 };
}

namespace TypeAliases // type aliases
{
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using float32 = float;
    using float64 = double;
}

#endif // !CONSTANTS_HEADER
