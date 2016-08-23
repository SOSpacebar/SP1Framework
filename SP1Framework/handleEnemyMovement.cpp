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
extern SMapData g_mapData;
extern SGameChar g_sChar;

void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime)
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	for (int x = 0; x < i; x++)
	{
		if (offsetTime1 % 20 == 0)
		{
			moveAI(g_mapData, g_sChar, _enemy, i, x);
		}

		//if (sqrt((g_sChar.m_cLocation.X - _enemy[x].e_location.X)*(g_sChar.m_cLocation.X - _enemy[x].e_location.X) + ((g_sChar.m_cLocation.Y - _enemy[x].e_location.Y)*(g_sChar.m_cLocation.Y - _enemy[x].e_location.Y))) <= 8)
		//{
		//	// DO NOT DELETE. THIS IS TO CHECK IF ENEMY IS WITHIN SIGHT!!! 
		///// NO DELETE
		///// NO DELETE!!!
		//}
		
		g_Console.writeToBuffer(_enemy[x].e_location, 'M', 0x06);
	}
}