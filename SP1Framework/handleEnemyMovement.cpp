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

void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime, SGameChar _sChar, SMapData _mapData, EGAMESTATES &g_eGameState, Portal &_portal)
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	for (int x = 0; x < i; x++)
	{
		if (offsetTime1 % 20 == 0)
		{
			moveAI(_mapData, _sChar, _enemy, i, x, g_eGameState);
		}

		if (sqrt((_sChar.m_cLocation.X - _enemy[x].e_location.X) *
			(_sChar.m_cLocation.X - _enemy[x].e_location.X)		 +
			((_sChar.m_cLocation.Y - _enemy[x].e_location.Y)	 *
			(_sChar.m_cLocation.Y - _enemy[x].e_location.Y))) <= 8 ||
			(sqrt((_portal.p_pos[1].X - _enemy[x].e_location.X)  *
			(_portal.p_pos[1].X - _enemy[x].e_location.X)		 +
			((_portal.p_pos[1].Y - _enemy[x].e_location.Y)       *
			(_portal.p_pos[1].Y - _enemy[x].e_location.Y))) <= 3)	||
			(sqrt(((_portal.p_pos[0].Y - _enemy[x].e_location.Y) *
			(_portal.p_pos[0].Y - _enemy[x].e_location.Y)        +
			((_portal.p_pos[0].X - _enemy[x].e_location.X)       *
			(_portal.p_pos[0].X - _enemy[x].e_location.X))))<= 3))
		{
			if (_enemy[x].e_alive)
			{
				g_Console.writeToBuffer(_enemy[x].e_location, 'M', 0x06);
			}
			else if (_enemy[x].e_alive == false)
			{
				_enemy[x].e_location.X = 0;
				_enemy[x].e_location.Y = 0;
			}
		}
	}
}