
#include <iostream>
#include <string>
#include <algorithm>

#include "util.h"

struct Player
{
	float health{ 100 };
	float speed{ 5.5f };
	float damage{ 25.0f };
};

bool checkPlayerDeath(const Player& player)
{
	if (player.health < 1)
	{
		return 1;
		// play death animation and return..
	}
	return 0;
}

int main()
{
	bool isDead1{ checkPlayerDeath( Player{ 0,5,5 }) }; // creating rvalue variable with type Player and initial data.
	bool isDead2{ checkPlayerDeath( { 25,5,5 } )}; // type deduced from type signature, but its very ambiguous..
	return 0;
}