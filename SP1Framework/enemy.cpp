#include "enemyProperties.h"

short xPos[50];
short yPos[50];

void init_enemy(short level, enemyStruct _enemy[], short amountOfEnemy) //Preload the data of the enemy into memory.
{
	short num = amountOfEnemy;
	//short xPos[3] = { 4, 4, 4 };
	//short yPos[3] = { 6, 10, 15 };


	//if (level == 1)
	//{
		for (short i = 0; i < num; i++)
		{
			COORD pos;
			pos.X = xPos[i];
			pos.Y = yPos[i];

			_enemy[i].e_location = pos;
			_enemy[i].e_speed = 5;
			_enemy[i].e_health = 5;
			_enemy[i].e_attack = 5;
			_enemy[i].e_alive = true;
		}
	//}
}

void enemyCoordStart(int newX, int newY, int i)
{
	xPos[i] = newX;
	yPos[i] = newY;
}

