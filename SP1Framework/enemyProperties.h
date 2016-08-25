#ifndef _ENEMYPROPERTIES_H
#define _ENEMYPROPERTIES_H


#include "game.h"
#include "Framework\console.h"
#include "portalGun.h"
#include "HeaderIncludes.h"

struct enemyStruct
{
	bool e_alive;
	COORD e_location;
};

void init_enemy(short level, enemyStruct _enemy[], short amountOfEnemy);
void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime, SGameChar _sChar, SMapData _mapData, EGAMESTATES &g_eGameState, Portal &_portal);
void enemyCoordStart(int newX, int newY, int i);

#endif