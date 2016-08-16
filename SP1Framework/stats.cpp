#include "stats.h"

void stats(int id, int speed, int PosX, int PosY)
{
	struct stats{
		int ID;
		int Speed;
		int X;
		int Y;
	};

	struct stats obstacle;

	obstacle.ID = id;
	obstacle.Speed = speed;
	obstacle.X = PosX;
	obstacle.Y = PosY;

}