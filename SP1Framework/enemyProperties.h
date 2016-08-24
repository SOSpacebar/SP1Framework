#ifndef _ENEMYPROPERTIES_H
#define _ENEMYPROPERTIES_H


#include "game.h"
#include "Framework\console.h"
#include "ReadMap.h"

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
void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime, SGameChar _sChar, SMapData _mapData);
void enemyCoordStart(int newX, int newY, int i);
void checkIfEngage(enemyStruct _enemy[], SGameChar player, EGAMESTATES &g_eGameState);

#endif