#include "portalGun.h"

bool checkBulletCollision(Bullet &_bullet, SMapData &g_mapData, Console &g_Console)
{
	if (_bullet.direction == K_UP && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall above the bullet.
	{
		return true;
	}

	if (_bullet.direction == K_DOWN && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall below the bullet.
	{
		return true;
	}

	if (_bullet.direction == K_RIGHT && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall to the right of the bullet.
	{
		return true;
	}

	if (_bullet.direction == K_LEFT && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall to the left of the bullet.
	{
		return true;
	}

	return false;
}