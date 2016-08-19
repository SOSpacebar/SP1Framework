#include "portalGun.h"
#include "Framework\console.h"


extern bullet _bullet;
extern double g_dElapsedTime;
extern Console g_Console;

extern SMapData g_mapData;

double _elapsedTime;
short travelTime;

void handleBulletProjectile()
{
	_elapsedTime = g_dElapsedTime;
	travelTime++;

	if (_elapsedTime == g_dElapsedTime && travelTime == 5)
	{
		travelTime = 0;
		if (checkBulletCollision() == false)
		{
			if (_bullet.direction == K_UP)
			{
				_bullet.b_pos.Y--;
			}
			if (_bullet.direction == K_DOWN)
			{
				_bullet.b_pos.Y++;
			}
			if (_bullet.direction == K_LEFT)
			{
				_bullet.b_pos.X--;
			}
			if (_bullet.direction == K_RIGHT)
			{
				_bullet.b_pos.X++;
			}
		}
	}
	
	if (checkBulletCollision() == false)
	g_Console.writeToBuffer(_bullet.b_pos, 'o', 0x6D);

}

bool checkBulletCollision()
{
	if (_bullet.direction == K_UP && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall above the bullet.
	{
		return true;
	}

	if (_bullet.direction == K_DOWN && g_mapData.mapGrid[_bullet.b_pos.Y + 1][_bullet.b_pos.X] == (char)219) //Check is a wall below the bullet.
	{
		return true;
	}

	if (_bullet.direction == K_RIGHT && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X + 1] == (char)219) //Check is a wall to the right of the bullet.
	{
		return true;
	}

	if (_bullet.direction == K_LEFT && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X - 1] == (char)219) //Check is a wall to the left of the bullet.
	{
		return true;
	}

	return false;
}