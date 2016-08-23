#include "enemyProperties.h"
#include "ReadMap.h"
#include "PathfindingAI.h"

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

		g_Console.writeToBuffer(_enemy[x].e_location, 'M', 0xF6);

	}
}