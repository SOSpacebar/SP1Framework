#include "game.h"

struct enemyStruct
{
	COORD e_location;
	short e_health;
	short e_attack;
	short e_speed;
	bool e_alive;
};