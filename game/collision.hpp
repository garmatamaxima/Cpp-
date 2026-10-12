#pragma once
#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

class HitboxAAB
{
private:

	struct box
	{
		Vector2 min{}; // x,y
		Vector2 max{}; // x,y
		Vector2 halfLenght{}; // lenght x /2, lenght y/2.
	};

	box box{};

public:

	// initalises with given side lenghts, creates at position's center
	HitboxAAB( Vector2 position,  float lenght_x, float lenght_y)
	{
		box.halfLenght.x = lenght_x / 2;
		box.halfLenght.y = lenght_y / 2;

		box.min = { box.min.x - box.halfLenght.x, box.min.y - box.halfLenght.y };
		box.max = { box.min.x + box.halfLenght.x, box.min.y + box.halfLenght.y };
	}

	// moves hitbox by an offset.
	void move(const Vector2& offset)
	{

	}
	// implement moving HitboxAAB, collision detection of two hitbox AAB's ( how the detection shall be implemented? check projections? )

	void collisionCheck();


};




#endif