
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <cmath>
#include <string>
#include <vector>
#include <array>

#include "main.h"

using namespace mainGlobals;

class entity
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

	void pointToMouse()
	{
		direction = Vector2Normalize(Vector2Subtract(mousePos, position));
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
		if (position.x > screenWidth)
		{
			position.x = 0;
		}
		else if (position.x < 0)
		{
			position.x = screenWidth;
		}

		if (position.y > screenHeight)
		{
			position.y = 0;
		}
		else if (position.y < 0)
		{
			position.y = screenHeight;
		}

	}

};

namespace
{
	static std::vector<entity> bullets_bufferVector{};
	static entity bullets_buffer[projectileLimit];
}

struct point
{
	Vector2 pos;
	float& x{pos.x};
	float& y{pos.y};

	bool state = false ;
};

class object
{
public:
	Vector2 direction;
	Vector2 Center;
	Vector2 velocity;
	float angularVelocity; // in radians

	std::array<point,32> points; // in local frame, they are offsets from center.

	void init(float posX, float posY, float angle )
	{
		Center.x = posX;
		Center.y = posY;
		direction.x = std::cos(angle);
		direction.y = std::sin(angle);
		
		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			points[i].state = false;
		}
		
		rotatePoints( angularVelocity );
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

	void rotatePoints1( )
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

		DrawCircle( (int)(Center.x), (int)(Center.y), 5, BLUE );
		for (short i{ 0 }; i < ( sizeof(points) / sizeof(points[0]) ) ; ++i)
		{
			if (points[i].state == true)
			{
				lineNextIndex = (i + 1) % 32;

				DrawLine(points[i].x + Center.x, points[i].y + Center.y, points[lineNextIndex].x + Center.x, points[lineNextIndex].y + Center.y, BLACK);
			}
			DrawCircle( points[i].x + Center.x, points[i].y + Center.y, 5, GREEN );
		}
	}

	Vector2 GlobalToLocal(const Vector2& global_point)
	{
		return Vector2Subtract( global_point, Center );
	}

	void createPoint(const Vector2& global_framePoint)
	{
		for (short i{ 0 }; i < (sizeof(points) / sizeof(points[0])); ++i)
		{
			if (points[i].state == false)
			{
				points[i].state = true;
				points[i].pos = GlobalToLocal( global_framePoint ) ;
				return;

			}
		}
	}
	

};



namespace obj
{
	object rectangle{};
}

int getNewId()
{
	int temp = ids;
	ids += 1;
	return temp;
}

void drawPointer( const entity entity )
{
	DrawCircle ( entity.position.x + entity.direction.x * 20, entity.position.y + entity.direction.y * 20, 5, DARKGRAY );
}

void playerInput( entity& player, float speed )
{
	if (IsKeyPressed(KEY_Q)) 
	{
		if (playermode != 1 ) { playermode = 1; }
		else { playermode = 0; }
	}

	if (IsKeyDown(KEY_A)) {
		
		if (playermode == 0)
		{
			player.accelerate(-(dt * speed), 0);
		}
		else {
			player.position.x += dt * speed * -34.5; player.setVelocity(0, 0); }
	}
	else if (IsKeyDown(KEY_D))
	{
		if (playermode == 0)
		{
			player.accelerate(dt * speed, 0);
		}
		else { player.position.x += dt * speed * 34.5; player.setVelocity(0, 0);
		}
	}

	if (IsKeyDown(KEY_W)) 
	{ 
		if (playermode == 0)
		{
			player.accelerate(0, -(dt * speed));
		}
		else { player.position.y += -(dt * speed * 34.5); player.setVelocity(0,0); }
	}
	else if (IsKeyDown(KEY_S))
	{
		if (playermode == 0)
		{
			player.accelerate(0, (dt * speed));
		}
		else { player.position.y += dt * speed * 34.5; player.setVelocity(0, 0); }
	}
}

void shootInputChecker(const entity& player, float speed )
{
	int static idSelector{0};

	if (IsKeyPressed(KEY_SPACE))
	{
		if (idSelector > projectileLimit - 1 || idSelector < 0) { idSelector = 0; }

		bullets_buffer[idSelector].status = true;
		
		bullets_buffer[idSelector].position.x = player.position.x + player.direction.x * 25;
		bullets_buffer[idSelector].position.y = player.position.y + player.direction.y * 25;

		bullets_buffer[idSelector].setVelocity( player.direction.x * speed * dt + player.velocity.x, player.direction.y * speed * dt + player.velocity.y);

		idSelector += 1;
	}

	if (IsKeyPressed(KEY_LEFT_SHIFT))
	{
		obj::rectangle.createPoint( GetMousePosition());
	}
	if (IsKeyPressed(KEY_R))
	{
		obj::rectangle.resetPoints();
	}

	if (IsKeyPressed(KEY_F))
	{
		obj::rectangle.angularVelocity = obj::rectangle.angularVelocity + 0.02;
		if (obj::rectangle.angularVelocity > 0.04 || obj::rectangle.angularVelocity < 0)
		{
			obj::rectangle.angularVelocity = 0;
		}
	}

	if (IsKeyPressed(KEY_G)) { obj::rectangle.scalePoints(1.1); }
	if (IsKeyPressed(KEY_H)) { obj::rectangle.scalePoints(0.9); }

}




void renderProjectiles()
{
	int bulletsActive{};

	for (int i1{ 0 }; i1 < projectileLimit - 1; ++i1)
	{
		if (bullets_buffer[i1].status == true)
		{
			bulletsActive += 1;

			bullets_buffer[i1].updatePosition();
			bullets_buffer[i1].wraparoundCheck();

			DrawCircle( bullets_buffer[i1].position.x, bullets_buffer[i1].position.y , bullets_buffer[i1].size, RED );
		}
	}
	DrawText(TextFormat("Bullets created: %i", bulletsActive), 55, 55, 25, BLACK);
}

int main()
{
	InitWindow(screenWidth, screenHeight, "PROGRAM");
	SetTargetFPS(144);

	// initalising both player and bullet entities
	entity player1{ }; player1.init(screenWidth/2, screenHeight/2, getNewId(), 15, 0);

	for (int i1{ 0 }; i1 < projectileLimit; ++i1)
	{
		bullets_buffer[i1].init(0, 0, getNewId(), 5, 0, false);
	}

	int coom[100] {};

	obj::rectangle.init(screenWidth / 2, screenHeight / 2, 1.5);
	obj::rectangle.angularVelocity = 0.001;
	
	/// main loop
	while (!WindowShouldClose()) // detects ESC.
	{
		//
		dt = GetFrameTime();
		mousePos = GetMousePosition();

		/// logic part

		playerInput( player1 , 10.0f );
		player1.pointToMouse();
		player1.updatePosition();
		

		player1.wraparoundCheck();
		shootInputChecker(player1, 425);

		obj::rectangle.rotatePoints1();

		/// Render part
		BeginDrawing();
		ClearBackground(RAYWHITE);

		obj::rectangle.render();

		renderProjectiles();

		// text that appears when user hovers their mouse over player
		if ( Vector2Distance( mousePos, player1.position ) < player1.size + 5 )
		{
			DrawText("you", player1.position.x - 14, player1.position.y - 44, 18, BLACK);
		}
		//player
		DrawCircleV(player1.position, player1.size, BLACK);
		drawPointer( player1 );
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}