#include "enemyProperties.h"

short xPos[50];
short yPos[50];

void init_enemy(short level, enemyStruct _enemy[], short amountOfEnemy) //Preload the data of the enemy into memory.
{
	short num = amountOfEnemy;
	for (short i = 0; i < num; i++)
	{
		COORD pos;
		pos.X = xPos[i];
		pos.Y = yPos[i];

		_enemy[i].e_alive = true;
		_enemy[i].e_location = pos;
	}

}

void enemyCoordStart(int newX, int newY, int i)
{
	xPos[i] = newX;
	yPos[i] = newY;
}

