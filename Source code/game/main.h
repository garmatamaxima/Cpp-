#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <cstddef>

inline namespace mainGlobals
{
	constexpr int screenWidth = 1200;
	constexpr int screenHeight = 850;
	float dt{};
    Vector2 mousePos{};

    constexpr int projectileLimit{1000};
    int playermode{ 0 };
    int ids{ 1 };
}

namespace TypeAliases // type aliases that take type identifiers from rust language.
{
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using f32 = float;
    using f64 = double;
}