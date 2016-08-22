#include "enemyProperties.h"

//extern enemyStruct _enemy[3];
//extern double g_dElapsedTime;
//extern Console g_Console;

double currTime1;

bool reversing0 = false;
bool reversing1 = false;

int offsetTime1 = 0;

void enemyMovememt(enemyStruct _enemy[], Console &g_Console, double &g_dElapsedTime)
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	if (reversing0 == false && offsetTime1 % 30 == 0)
	{
		_enemy[0].e_location.X++;
	}

	if (_enemy[0].e_location.X >= 20)
	{
		reversing0 = true;
	}

	if (reversing0 && offsetTime1 % 30 == 0)
	{
		_enemy[0].e_location.X--;
	}

	if (_enemy[0].e_location.X <= 3)
	{
		reversing0 = false;
	}

	if (reversing1 == false && offsetTime1 % 20 == 0)
	{
		_enemy[1].e_location.X++;
		_enemy[2].e_location.X++;
	}

	g_Console.writeToBuffer(_enemy[0].e_location, 'M', 0xF6); 
	g_Console.writeToBuffer(_enemy[1].e_location, 'M', 0xF6);
	g_Console.writeToBuffer(_enemy[2].e_location, 'M', 0xF6);
}