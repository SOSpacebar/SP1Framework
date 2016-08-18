#include "enemyProperties.h"

enemyStruct _enemy[3];

void init_enemy(short level) //Preload the data of the enemy into memory.
{
	if (level == 1)
	{
		short num = 3;
		short x[3] = { 4, 4, 4 };
		short y[3] = { 6, 10, 15 };

		for (short i = 0; i < num; i++)
		{
			COORD pos;
			pos.X = x[i];
			pos.Y = y[i];

			_enemy[i].e_location = pos;
			_enemy[i].e_speed = 5;
			_enemy[i].e_health = 5;
			_enemy[i].e_attack = 5;
			_enemy[i].e_alive = true;
		}
	}
}

/*void handleMovement(COORD pos, short speed)
{
	double currTime;
	string monsterString = "M";

	bool reversing = false;
	int offsetTime = 0;

	currTime = g_dElapsedTime;
	offsetTime++;

	if (currTime == g_dElapsedTime && reversing == false && offsetTime == 20)
	{
		pos.X++;
		pos.Y = 15;
		offsetTime = 0;
		g_Console.writeToBuffer(pos, monsterString, 0xF6);
	}

	if (pos.X >= 50)
	{
		reversing = true;
	}

	if (reversing && offsetTime == 20)
	{
		pos.X--;
		pos.Y = 15;
		offsetTime = 0;
		g_Console.writeToBuffer(pos, monsterString, 0xF6);
		if (pos.X == 1)
		{
			reversing = false;
		}
	}
	g_Console.writeToBuffer(pos, monsterString, 0xF6);
}*/


