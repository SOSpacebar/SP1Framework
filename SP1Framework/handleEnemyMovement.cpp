#include "enemyProperties.h"
#include "ReadMap.h"
<<<<<<< HEAD
#include "PathfindingAI.h"
=======
#include <math.h>
#include <stdio.h>
>>>>>>> 22ac0e1f015f95342b294d321da3884a3c80e189

//extern enemyStruct _enemy[3];
//extern double g_dElapsedTime;
//extern Console g_Console;

double currTime1;

bool reversing0 = false;
bool reversing1 = false;

int offsetTime1 = 0;

extern int i;
extern SMapData g_mapData;
extern SGameChar g_sChar;
<<<<<<< HEAD

=======
>>>>>>> 22ac0e1f015f95342b294d321da3884a3c80e189
//int x = 0;

void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime)
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	for (int x = 0; x < i; x++)
	{
		//if (_enemy[x].e_reverse == false && offsetTime1 % 20 == 0)
		//{
		//	_enemy[x].e_location.X++;
		//}

		//if (g_mapData.mapGrid[_enemy[x].e_location.Y - 1][_enemy[x].e_location.X] == (char)219)
		//{
		//	_enemy[x].e_reverse = true;
		//}

		//if (_enemy[x].e_reverse && offsetTime1 % 20 == 0)
		//{
		//	_enemy[x].e_location.X--;
		//}

		//if (g_mapData.mapGrid[_enemy[x].e_location.Y - 1][_enemy[x].e_location.X - 1] == (char)219)
		//{
		//	_enemy[x].e_reverse = false;
		//}

		if (offsetTime1 % 20 == 0)
		{
			moveAI(g_mapData, g_sChar, _enemy, i, x);
		}

		if (sqrt((g_sChar.m_cLocation.X - _enemy[x].e_location.X)*(g_sChar.m_cLocation.X - _enemy[x].e_location.X) + ((g_sChar.m_cLocation.Y - _enemy[x].e_location.Y)*(g_sChar.m_cLocation.Y - _enemy[x].e_location.Y))) <= 8)
		{
			g_Console.writeToBuffer(_enemy[x].e_location, 'M', 0x06);
		}
		

	}
}