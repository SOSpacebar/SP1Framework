#include "enemyProperties.h"
#include "Framework\console.h"

extern enemyStruct _enemy[3];
extern double g_dElapsedTime;
extern Console g_Console;

double currTime1;

bool reversing1 = false;
int offsetTime1 = 0;

void WALKLA()
{
	currTime1 = g_dElapsedTime;
	offsetTime1++;

	if (currTime1 == g_dElapsedTime && reversing1 == false && offsetTime1 == 20)
	{
		offsetTime1 = 0;
		_enemy[0].e_location.X++;
		_enemy[1].e_location.X++;
		_enemy[2].e_location.X++;
		g_Console.writeToBuffer(_enemy[0].e_location, 'M', 0xF6);
		g_Console.writeToBuffer(_enemy[1].e_location, 'M', 0xF6);
		g_Console.writeToBuffer(_enemy[2].e_location, 'M', 0xF6);
	}

	g_Console.writeToBuffer(_enemy[0].e_location, 'M', 0xF6); 
	g_Console.writeToBuffer(_enemy[1].e_location, 'M', 0xF6);
	g_Console.writeToBuffer(_enemy[2].e_location, 'M', 0xF6);
}