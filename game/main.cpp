#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <memory>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "main.hpp"
#include "constants.hpp"

using namespace Globals;

ProjectileData projectile_buffer{ 1000 };

int main()
{
	/// setup ///
	InitWindow(screenWidth, screenHeight, "PROGRAM");
	SetTargetFPS(144);

	/// initalising data ///

	inputHandler inputHandler{};
	LevelData world;

	Player player0{ playerSpawnPoint, 0 };

	// camera
	Camera2D camera = { 0 };
	Vector2 camera_target{};

	camera.target = player0.position_;
	camera.offset = Vector2{ (float)screenWidth/2 , (float)screenHeight/2};
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

		inputHandler.inputPlayer(player0, projectile_buffer);
		player0.update();
		

		/// Render part
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);

		projectile_buffer.updateALL();


		DrawCircleV(player0.position_, 25, GREEN);
		
		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}