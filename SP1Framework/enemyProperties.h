#include "game.h"

struct enemyStruct
{
	COORD e_location;
	short e_health;
	short e_attack;
	short e_speed;
	bool e_alive;
};

void init_enemy(short level);
void WALKLA();
//void handleMovement(COORD pos, short speed);

