#pragma once

#include <array>
#include <memory>
#include <unordered_map>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "constants.hpp"

#ifndef DRAW_STUPID_PROJECTILES
#define DRAW_STUPID_PROJECTILES

#endif

int getNewGID();
using namespace TypeAliases;

enum class vFunction
{
	player_moveLEFT,
	player_moveRIGHT,
	player_moveUP, 
	player_moveDOWN,
	player_shoot1,
	size_enum,
};

const static std::array<int, (size_t)255> default_keybinds{ KEY_A, KEY_D, KEY_W, KEY_S, KEY_SPACE, KEY_V };

// base class made to be inherited by other specialisations.
class Entity
{
public:

	Vector2 position{};
	Vector2 direction{};
	Vector2 velocity{};
	float angleRad{};

	Entity(float posX = 0, float posY = 0, int size_ = 10, float angle = 0, bool status_ = true)
	{
		position.x = posX;
		position.y = posY;

		angleRad = angle;
		direction.x = std::cos(angle);
		direction.y = std::sin(angle);

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


};

class Object2D
{
public:
	Vector2 position;
	Vector2 direction;
	float velocity;

	Object2D()
	{
		direction.x = std::cos(0);
		direction.y = std::sin(0);
	}
};

class Player : private Entity
{
private:

	int playerID{};

	float frictionCoeff{ 12 };
	constexpr static float frictionCutoff{ 0.5 };

	float maxVelocity{ 400 };
	float walkAcceleration{ 5000.0f }; // scale with dt to make acceleration consistent
	float runDirectionX{ 0 };
	float runDirectionY{ 0 };
	

	Vector2 aimDirection{};
	//offset from world position (as center of game entity) where bullets are created
	Vector2 weaponOffset{0,0};

	std::array<Vector2, 4> keyboard_keypress_buffer{};

public:

	const Vector2& position_{ position };
	const Vector2& velocity_{ velocity };
	const Vector2& direction_{ direction };
	const Vector2& aimDirection_{ aimDirection };



	// returns global world position for projectile start coordinate
	Vector2 muzzlePosition() const
	{
		return Vector2{ position.x + (aimDirection.x * weaponOffset.x), position.y + (aimDirection.y * weaponOffset.y) };
	}

	Player(Vector2 position_init, int player_id_)
	{
		playerID = player_id_;
		velocity = { 0,0 };
		position = position_init;
		setDirection(0.0f);
		weaponOffset = { 0, 0 };
		
	}
	Player() {}

	// handles updating player's position, aimDirection and applying friction by reducing velocity
	void update()
	{
		//



		// check if player is not walking - apply friction.
		if (runDirectionX == 0)
		{
			velocity.x -= ( velocity.x * frictionCoeff * dt );

			if (velocity.x < frictionCutoff && velocity.x > -frictionCutoff) { velocity.x = 0; }
		}
		
		if (runDirectionY == 0)
		{
			velocity.y -= (velocity.y * frictionCoeff * dt);

			if (velocity.y < frictionCutoff && velocity.y > -frictionCutoff) { velocity.y = 0; }
		}

		// aim direction
		aimDirection = Vector2Normalize(Vector2{ mousePos.x - screenWidth , mousePos.y - screenHeight });
		
		// set the run direction to zero to allow friction on next tick 
		runDirectionX = 0;
		runDirectionY = 0;
		
		keyboard_keypress_buffer.fill(Vector2{ 0,0 });

		// position updates should be scaled with dt for stability.
		position += velocity * dt;
	}

	enum class moveDirections
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	void walkKeyboard(moveDirections Move_direction)
	{
		Vector2 direction_result{};

		// select move direction
		switch (Move_direction)
		{
		case moveDirections::LEFT:
			keyboard_keypress_buffer[0] = Vector2{ -1,0 };
			break;
		case moveDirections::RIGHT:
			keyboard_keypress_buffer[1] = Vector2{ 1,0 };
			break;
		case moveDirections::UP:
			keyboard_keypress_buffer[2] = Vector2{ 0,-1 };
			break;
		case moveDirections::DOWN:
			keyboard_keypress_buffer[3] = Vector2{ 0,1 };
			break;
		}

		// combine vector directions.
		for (int i = 0; i < keyboard_keypress_buffer.size(); ++i)
		{
			direction_result = Vector2Normalize(direction_result + keyboard_keypress_buffer[i]);
		}

		// accelerate player and clamp their max velocity 
		velocity.x = Clamp(velocity.x + (direction_result.x * walkAcceleration * dt), -maxVelocity, maxVelocity);
		velocity.y = Clamp(velocity.y + (direction_result.y * walkAcceleration * dt), -maxVelocity, maxVelocity);


	}
	/*
	void walkLeft()
	{
		runDirectionX = -1;
		velocity.x = Clamp( velocity.x - (walkAcceleration * dt), -maxVelocity, maxVelocity);
	}
	void walkRight()
	{
		runDirectionX = 1;
		velocity.x = Clamp( velocity.x + (walkAcceleration * dt), -maxVelocity, maxVelocity);
	}
	void walkUp()
	{
		runDirectionY = -1;
		velocity.y = Clamp(velocity.y - (walkAcceleration * dt), -maxVelocity, maxVelocity);
	}
	void walkDown()
	{
		runDirectionY = 1;
		velocity.y = Clamp(velocity.y + (walkAcceleration * dt), -maxVelocity, maxVelocity);
	}
	*/
};

inline namespace Projectiles
{
	constexpr enum class ProjectileNames
	{
		null,
		fast,
		slow,
		pellet,
		magic
	};

	class Projectile : public Object2D
	{
	public:
		float lifetime_max{}; // in seconds.
		float lifetime{ 0 };
		float damage{ 1 };
		int size{ 5 };
		bool status{ false };

		
		ProjectileNames TYPE{ ProjectileNames::null };
		int projectileID{};

		// projectile type constructor
		Projectile(ProjectileNames TYPE_, int size_, float velocity_, float lifetime_max_, float damage_ = 5)
		{
			lifetime_max = lifetime_max_;
			velocity = velocity_;
			TYPE = TYPE_;
			size = size;
			lifetime_max = lifetime_max_;
			damage = damage_;
		}

		void update()
		{
			position.x = position.x + (velocity * direction.x * dt);
			position.y = position.y + (velocity * direction.y * dt);
			
			if (status == true ) lifetime += dt;
			
			if (lifetime > lifetime_max)
			{
				status = false;
			}
#ifdef DRAW_STUPID_PROJECTILES
			if (status == true) DrawCircle(position.x, position.y, size, BLACK);
			
#endif // DRAW_STUPID_PROJECTILES
		}

		void Nullify_state()
		{
			position = { 0,0 };
			direction = { 0,0 };
			velocity = 0;
			status = false;
		}

		// zero constructor
		Projectile() {}
	};

	static const Projectile fast{ ProjectileNames::fast, 10, 1220.0f, 1, 25 };
	static const Projectile slow{ ProjectileNames::slow, 10, 25.0f, 2, 45 };
	static const Projectile pellet{ ProjectileNames::pellet, 10, 90.0f, 0.5f, 5 };

}

class ObjectLEGACY
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

class ProjectileData
{
private:

	std::vector<Projectile> projectiles{ 5 };
	uint32 nextfreeID{};

	// search for next free ID to claim for new projectile creation, can claim more slots.
	void searchNewFreeID()
	{

		bool wrap = false;

		for (int64 i{ nextfreeID }; i < projectiles.size();++i)
		{
			// check if counter is in limits of uint32 size and less than or equal to projectiles buffer
			if ( (i < UINT32_MAX) && (i + 1 < projectiles.size()))
			{
				if (projectiles.at(i).status == false)
				{
					nextfreeID = i;
					return;
				}
			}
			else
			{
  				if (wrap) projectiles.push_back(Projectile{}); // create new projectile into buffer if there is no free Id's
				// wrap back
				i = 0;
				wrap = true;
			}
		}
		
	}

public:
	// initalise a buffer of zero initalised projectiles
	ProjectileData( uint32 buffer_size )
	{
		projectiles.reserve(size_t{ buffer_size });
		uint64 buffersize{ projectiles.size() };
		
		//assign ID's
		for (int64 i{};i < buffersize; ++i)
		{
			projectiles.at(i).projectileID = i;
		}
		nextfreeID = 0;
	}

	void createNew(const Projectile& projectile_template, const Player& shooter)
	{
		projectiles.at(nextfreeID) = projectile_template;
		projectiles.at(nextfreeID).direction = shooter.aimDirection_;
		projectiles.at(nextfreeID).projectileID = nextfreeID;
		projectiles.at(nextfreeID).position = shooter.muzzlePosition();
		projectiles.at(nextfreeID).status = true;
		projectiles.at(nextfreeID).lifetime = 0;

		searchNewFreeID();
	}

	void updateALL()
	{
		uint64 buffersize{ projectiles.size() };
		for (int64 i{}; i < buffersize; ++i)
		{
			projectiles.at(i).update();
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

	void inputPlayer(Player& player, ProjectileData& pdata)
	{
		for (int i{ 0 }; i < (int)vFunction::size_enum; ++i)
		{
			switch (keybinds[i].vfunction)
			{
			case vFunction::player_moveLEFT: {
				if (IsKeyDown(keybinds[i].key)) { player.walkKeyboard(Player::moveDirections::LEFT); }
				break;
			}
			case vFunction::player_moveRIGHT: {
				if (IsKeyDown(keybinds[i].key)) { player.walkKeyboard(Player::moveDirections::RIGHT); }
				break;
			}

			case vFunction::player_moveUP: {
				if (IsKeyDown(keybinds[i].key)) { player.walkKeyboard(Player::moveDirections::UP); }
				break;
			}

			case vFunction::player_moveDOWN: {
				if (IsKeyDown(keybinds[i].key)) { player.walkKeyboard(Player::moveDirections::DOWN); }
				break;
			}
			case vFunction::player_shoot1: {
				if (IsKeyPressed(keybinds[i].key)) { pdata.createNew(fast, player); }
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

	std::array<int, (size_t)255> current_keybinds{ default_keybinds };

	std::array<pair, (size_t)vFunction::size_enum> keybinds{};

};

class LevelData
{
private:
	  

public:
	LevelData()
	{

	}
};