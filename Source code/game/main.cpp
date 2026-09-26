#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "main.hpp"
#include "constants.hpp"

using namespace Globals;

namespace
{
	static std::vector<Entity> bullets_bufferVector{};
	static Entity bullets_buffer[projectileLimit];
}

int getNewId()
{
	int temp = ids;
	ids += 1;
	return temp;
}

void drawPointer( const Entity entity )
{
	DrawCircle ( entity.position.x + entity.direction.x * 20, entity.position.y + entity.direction.y * 20, 5, DARKGRAY );
}

int main()
{
	/// setup ///

	InitWindow(screenWidth, screenHeight, "PROGRAM");
	SetTargetFPS(144);

	/// initalising data ///

	inputHandler inputHandler{};

	// initalising both player and bullet entities
	Player player0{ Vector2{225,225}, getNewId() };

	for (int i1{ 0 }; i1 < projectileLimit; ++i1)
	{
		bullets_buffer[i1].init(0, 0, getNewId(), 5, 0, false);
	}

	// camera
	Camera2D camera = { 0 };
	Vector2 camera_target{};

	camera.target = player0.position_;
	camera.offset = player0.position_;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	// idk?
	int coom[100] {};
	
	/// main loop ///
	while (!WindowShouldClose()) // detects ESC.
	{
		dt = GetFrameTime();
		mousePos = GetMousePosition();

		camera_target = player0.position_;
		camera.target = camera_target;

		/// logic part

		inputHandler.inputPlayer(player0);
		player0.update();

		/// Render part
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);


		//player
		DrawCircleV(player0.position_, 25, RED);
		
		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}