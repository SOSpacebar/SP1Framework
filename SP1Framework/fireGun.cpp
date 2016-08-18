#include "portalGun.h"

bullet _bullet;

bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection)
{
	if (key == K_SPACE)
	{
		if (lastDirection == K_UP && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X] == ' ') //Check is anything above the player.
		{
			createBullet(player.m_cLocation.X, player.m_cLocation.Y - 1, K_UP);
			return true;
		}

		if (lastDirection == K_DOWN && map.mapGrid[player.m_cLocation.Y + 1][player.m_cLocation.X] == ' ') //Check is anything below the player.
		{
			createBullet(player.m_cLocation.X, player.m_cLocation.Y + 1, K_DOWN);
			return true;
		}


		if (lastDirection == K_RIGHT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == ' ') //Check is anything to the right player.
		{
			createBullet(player.m_cLocation.X + 1, player.m_cLocation.Y, K_RIGHT);
			return true;
		}


		if (lastDirection == K_LEFT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == ' ') //Check is anything to the left player.
		{
			createBullet(player.m_cLocation.X - 1, player.m_cLocation.Y, K_LEFT);
			return true;
		}
	}

	return false;
}

void createBullet(short x, short y, EKEYS key)
{
	short num = 0;
	COORD bulletPosition;
	bulletPosition.X = x;
	bulletPosition.Y = y;

	_bullet.b_pos = bulletPosition;
	_bullet.direction = key;
}