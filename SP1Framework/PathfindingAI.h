#ifndef _PATHFINDERAI_H
#define _PATHFINDERAI_H

#include "game.h"
#include "ReadMap.h"
#include "enemyProperties.h"
#include <stdio.h>
#include <math.h>
#include <string>

enum Sectors
{
	Wander,
	Up,
	UpRight,
	Right,
	BtmRight,
	Down,
	BtmLeft,
	Left,
	UpLeft
};

void scanSectorForPlayer(SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy);
void scanTiles(SMapData mapData, SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy);
void checkIfEngage(enemyStruct _enemy[], SGameChar player, EGAMESTATES &g_eGameState, int indexEnemy);
void moveAI(SMapData mapData, SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy, EGAMESTATES &g_eGameState);

#endif