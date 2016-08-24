#include "enemyProperties.h"
#include "ReadMap.h"
#include "PathfindingAI.h"
#include <math.h>
#include <stdio.h>

double currTime1;

bool reversing0 = false;
bool reversing1 = false;

int offsetTime1 = 0;

extern int i;

void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime, SGameChar _sChar, SMapData _mapData)
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	for (int x = 0; x < i; x++)
	{
		if (offsetTime1 % 20 == 0)
		{
			moveAI(_mapData, _sChar, _enemy, i, x);
		}

		if (sqrt((_sChar.m_cLocation.X - _enemy[x].e_location.X)*(_sChar.m_cLocation.X - _enemy[x].e_location.X) + ((_sChar.m_cLocation.Y - _enemy[x].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[x].e_location.Y))) <= 8)
		{
			g_Console.writeToBuffer(_enemy[x].e_location, 'M', 0x06);
		}
	}
}

void checkIfEngage(enemyStruct _enemy[], SGameChar player, EGAMESTATES &g_eGameState)
{
	if ((player.m_cLocation.Y == _enemy[i].e_location.Y) && (player.m_cLocation.X == _enemy[i].e_location.X))
	{
		g_eGameState = S_TRANSITION;
	}
}