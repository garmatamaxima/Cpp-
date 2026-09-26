#pragma once
#ifndef COLLISION_TYPEDEFS
#define COLLISION_TYPEDEFS
#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

class HitboxAAB
{
private:

	struct interval
	{
		float min{};
		float max{};
		float lenght{};
	};

	interval x{};
	interval y{};

	interval xOld{};
	interval yOld{};

public:

	// initalises with given side lenghts, creates at position's center
	HitboxAAB( Vector2 position,  float lenght_x, float lenght_y)
	{
		x.lenght = lenght_x;
		y.lenght = lenght_y;

		x.min = position.x - lenght_x / 2;
		x.max = position.x + lenght_x / 2;

		y.min = position.y - lenght_y / 2;
		y.max = position.y + lenght_y / 2;
	}

	// moves to center of position
	void moveTo(const Vector2& position)
	{
		xOld = x;
		yOld = y;

		x.min = position.x - x.lenght / 2;
		x.max = position.x + x.lenght / 2;

		y.min = position.y - y.lenght / 2;
		y.max = position.y + y.lenght / 2;
	}

	// moves hitbox by an offset.
	void move(const Vector2& offset)
	{
		xOld = x;
		yOld = y;

		x.min += offset.x;
		x.max += offset.x;

		y.min += offset.y;
		y.max += offset.y;
	}

	// implement moving HitboxAAB, collision detection of two hitbox AAB's ( how the detection shall be implemented? check projections? )


};




#endif