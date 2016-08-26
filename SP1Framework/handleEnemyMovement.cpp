#include "enemyProperties.h"
#include "HeaderIncludes.h"
#include "PathfindingAI.h"
#include <math.h>
#include <stdio.h>

double currTime1;

bool reversing0 = false;
bool reversing1 = false;

int offsetTime1 = 0;
int indexEnemy = 0;

extern int i;

void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime, SGameChar _sChar, SMapData _mapData, EGAMESTATES &g_eGameState, Portal &_portal)
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	for (indexEnemy = 0; indexEnemy < i; indexEnemy++)
	{
		if (offsetTime1 % 20 == 0)
		{
			moveAI(_mapData, _sChar, _enemy, i, indexEnemy, g_eGameState);
		}

		if (sqrt((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X) *
			(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X) +
			((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)	 *
			(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y))) <= 8 ||
			(sqrt((_portal.p_pos[1].X - _enemy[indexEnemy].e_location.X)  *
			(_portal.p_pos[1].X - _enemy[indexEnemy].e_location.X) +
			((_portal.p_pos[1].Y - _enemy[indexEnemy].e_location.Y)       *
			(_portal.p_pos[1].Y - _enemy[indexEnemy].e_location.Y))) <= 3) ||
			(sqrt(((_portal.p_pos[0].Y - _enemy[indexEnemy].e_location.Y) *
			(_portal.p_pos[0].Y - _enemy[indexEnemy].e_location.Y) +
			((_portal.p_pos[0].X - _enemy[indexEnemy].e_location.X)       *
			(_portal.p_pos[0].X - _enemy[indexEnemy].e_location.X)))) <= 3))
		{
			if (_enemy[indexEnemy].e_alive)
			{
				g_Console.writeToBuffer(_enemy[indexEnemy].e_location, 'M', 0x06);
			}
			else if (_enemy[indexEnemy].e_alive == false)
			{
				_enemy[indexEnemy].e_location.X = 0;
				_enemy[indexEnemy].e_location.Y = 0;
			}
		}
	}
}