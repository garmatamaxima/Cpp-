
#include <iostream>

float fallEvent(float pos_x, float& velocity, float ground_x, float time)
{
	velocity = velocity - 9.81f; // gravity acceleration constant
	float updatedPos_x = pos_x + velocity;
	if (updatedPos_x <= ground_x)
	{
		std::cout << "touched ground on second = " << time;
		return ground_x;
	}
	std::cout << "Time = " << time << " height = " << updatedPos_x << '\n';
	return updatedPos_x;
}

int dihmaster()
{
	return 0;
}


int main()
{
	bool touchdown{false}; // ball touched ground - state
	float ball_height{};
	float ball_velocity{0};
	float ground_height{0};
	std::cin >> ball_height;
	
	for (float sec{1}; touchdown == false; sec++)
	{
	ball_height = fallEvent(ball_height, ball_velocity, 0, sec);
	if (ball_height <= ground_height) {touchdown = true;}
	}
	return 0;
}