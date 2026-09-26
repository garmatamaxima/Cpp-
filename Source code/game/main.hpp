#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "constants.hpp"

// player's input functions
enum vFunction
{
    player_moveLEFT,
    player_moveRIGHT,
    player_JUMP,
    player_DUCK,
    player_shoot1,
    player_flyMode,
	step_through_frames_mode,
    size_enum,
};

class Entity
{
public:


	Vector2 position;
	Vector2 direction;
	Vector2 velocity;
	float angleRad;
	bool status;

	int id;
	int size;

	void init(float posX, float posY, int id_, int size_ = 10, float angle = 0, bool status_ = true)
	{
		position.x = posX;
		position.y = posY;

		angleRad = angle;
		direction.x = std::cos(angle);
		direction.y = std::sin(angle);
		id = id_;
		size = size_;
		status = status_;

		velocity.x = 0;
		velocity.y = 0;
	}

	void updatePosition()
	{
		position.x += velocity.x;
		position.y += velocity.y;
	}



	void setVelocity(const Vector2& velocity_vector)
	{
		velocity = velocity_vector;
	}
	void setVelocity(float x, float y)
	{
		velocity.x = x;
		velocity.y = y;
	}

	void accelerate(const Vector2& velocity_vector)
	{
		velocity.x += velocity_vector.x;
		velocity.y += velocity_vector.y;
	}
	void accelerate(float x, float y)
	{
		velocity.x += x;
		velocity.y += y;

	}

	void accelerateDirection(float acceleration)
	{
		velocity.x += direction.x * acceleration;
		velocity.y += direction.y * acceleration;

	}

	void pointToMouse(Vector2 camera_target)
	{
		direction = Vector2Normalize(Vector2Subtract(mousePos, Vector2{ screenWidth / 2.0f, screenHeight / 2.0f }));
		angleRad = std::atan2(direction.y, direction.x);
	}

	void pointToTarget(const Vector2& target)
	{
		direction = Vector2Normalize(Vector2Subtract(target, position));
	}
	void pointToTarget(float x, float y)
	{
		Vector2 temp{ x,y };
		direction = Vector2Normalize(Vector2Subtract(temp, position));
	}

	void setDirection(float angleRad_)
	{
		direction.x = std::cos(angleRad_);
		direction.y = std::sin(angleRad_);
	}

	void wraparoundCheck()
	{
		if (position.x > worldX)
		{
			position.x = 0;
		}
		else if (position.x < 0)
		{
			position.x = worldX;
		}

		if (position.y > worldY)
		{
			position.y = 0;
		}
		else if (position.y < 0)
		{
			position.y = worldY;
		}

	}

};

class Player
{
private:

	Entity entity;
	Vector2& position{ entity.position };
	Vector2& velocity{ entity.velocity };
	Vector2& direction{ entity.direction };

	float frictionCoeff{ 12 };
	float frictionCutoff{ 0.5 };

	float maxVelocity{ 400 };
	float walkAcceleration{ 5000.0f }; // scale with dt to make acceleration consistent
	float runDirection{ 0 };

public:

	Player(Vector2 position_init, int id)
	{
		entity.id = id;
		velocity = { 0,0 };
		position = position_init;
		entity.setDirection(0.0f);
	}

	void update()
	{
		// check if player is not walking - apply friction.
		if (runDirection == 0)
		{
			velocity.x -= ( velocity.x * frictionCoeff * dt );

			if (velocity.x < frictionCutoff && velocity.x > -frictionCutoff) { velocity.x = 0; }
		}
		
		// set the run direction to zero to allow friction on next tick
		runDirection = 0;
		
		// position updates should be scaled with dt for stability.
		position += velocity * dt;
	}

	void walkLeft()
	{
		runDirection = -1;
		velocity.x = Clamp( velocity.x - (walkAcceleration * dt), -maxVelocity, maxVelocity);
	}

	void walkRight()
	{
		runDirection = 1;
		velocity.x = Clamp( velocity.x + (walkAcceleration * dt), -maxVelocity, maxVelocity);
	}

	void jump()
	{

	}

	const Vector2& position_{ entity.position };
	const Vector2& velocity_{ entity.velocity };
	const Vector2& direction_{ entity.direction };

};

class object
{
private:

	struct point
	{
		Vector2 pos;
		float& x{ pos.x };
		float& y{ pos.y };

		bool state = false;
	};

public:
	Vector2 direction;
	Vector2 Center;
	Vector2 velocity;
	float angularVelocity; // in radians

	std::array<point, 32> points; // in local frame, they are offsets from center.

	void init(float posX, float posY, float angle)
	{
		Center.x = posX;
		Center.y = posY;
		direction.x = std::cos(angle);
		direction.y = std::sin(angle);

		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			points[i].state = false;
		}

		rotatePoints(angularVelocity);
	}

	void rotatePoints(float angle)
	{
		float cos{ std::cos(angle) };
		float sin{ std::sin(angle) };
		float tempx;
		float tempy;

		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			tempx = points[i].x;
			tempy = points[i].y;

			points[i].x = tempx * cos - tempy * sin;
			points[i].y = tempx * sin + tempy * cos;
		}
	}

	void rotatePoints1()
	{
		float cos{ std::cos(angularVelocity) };
		float sin{ std::sin(angularVelocity) };
		float tempx;
		float tempy;

		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			tempx = points[i].x;
			tempy = points[i].y;

			points[i].x = tempx * cos - tempy * sin;
			points[i].y = tempx * sin + tempy * cos;
		}
	}

	void scalePoints(float scaling_factor)
	{
		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			points[i].x *= scaling_factor;
			points[i].y *= scaling_factor;
		}
	}

	void resetPoints()
	{
		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			points[i].x = 0;
			points[i].y = 0;
			points[i].state = false;
		}
	}

	void render()
	{
		short lineNextIndex;

		DrawCircle((int)(Center.x), (int)(Center.y), 5, BLUE);
		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			if (points[i].state == true)
			{
				lineNextIndex = (i + 1) % 32;

				DrawLine(points[i].x + Center.x, points[i].y + Center.y, points[lineNextIndex].x + Center.x, points[lineNextIndex].y + Center.y, BLACK);
			}
			DrawCircle(points[i].x + Center.x, points[i].y + Center.y, 5, GREEN);
		}
	}

	Vector2 GlobalToLocal(const Vector2& global_point)
	{
		return Vector2Subtract(global_point, Center);
	}

	void createPoint(const Vector2& global_framePoint)
	{
		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			if (points[i].state == false)
			{
				points[i].state = true;
				points[i].pos = GlobalToLocal(global_framePoint);
				return;

			}
		}
	}

};

class inputHandler
{
public:

	// initalises input handler with default keybinds.
	inputHandler()
	{
		for (int i{ 0 }; i < (int)vFunction::size_enum; ++i)
		{
			keybinds[i].vfunction = (vFunction)(i);
			keybinds[i].key = default_keybinds[i];
		}
	}

	void inputPlayer(Player& player)
	{
		for (int i{ 0 }; i < (int)vFunction::size_enum; ++i)
		{
			switch (keybinds[i].vfunction)
			{
			case player_moveLEFT: {
				if (IsKeyDown(keybinds[i].key)) { player.walkLeft(); }
				break;
			}
			case player_moveRIGHT: {
				if (IsKeyDown(keybinds[i].key)) { player.walkRight(); }
				break;
			}

			case player_JUMP: {
				if (IsKeyDown(keybinds[i].key)) { player.jump(); }
				break;
			}

			case player_DUCK: {
				if (IsKeyDown(keybinds[i].key)) { player.jump(); }
				break;
			}
			}
		}
	}

private:

	struct pair
	{
		vFunction vfunction{};
		int key{};
	};

	std::array<int, (size_t)255> default_keybinds{ KEY_A, KEY_D, KEY_W, KEY_S, KEY_SPACE, KEY_V };

	std::array<int, (size_t)255> current_keybinds{ default_keybinds };

	std::array<pair, (size_t)vFunction::size_enum> keybinds{};

};
