#include "game.h"
#include "Framework\console.h"

struct enemyStruct
{
	short e_health;
	COORD e_location;
	short e_attack;
	short e_speed;
	bool e_alive;
	bool e_reverse;
};

void init_enemy(short level, enemyStruct _enemy[], short amountOfEnemy);
void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime);
void enemyCoordStart(int newX, int newY, int i);
