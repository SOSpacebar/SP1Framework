#include "game.h"
#include "Framework\console.h"

struct enemyStruct
{
	COORD e_location;
	short e_health;
	short e_attack;
	short e_speed;
	bool e_alive;
};

void init_enemy(short level, enemyStruct _enemy[], short amountOfEnemy);
void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime);

