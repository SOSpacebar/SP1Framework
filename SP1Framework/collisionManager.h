#ifndef _COLLISIONMANAGER.H
#define _COLLISIONMANAGER_H

#include "game.h"
#include "ReadMap.h"
#include "enemyProperties.h"

bool checkPlayerCollision(SGameChar player, SMapData map, EKEYS direction, EGAMESTATES &g_eGameState, short &g_currLevel, SGameKey &g_iKey, SGameKey &g_dDoor, int indexEnemy, enemyStruct _enemy[]);

#endif