#include "portalGun.h"

bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection, Bullet &_bullet, bool type)
{
	if (key == K_SPACE)
	{
		if (lastDirection == K_UP && (map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == ' ' || map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == '-')) //Check is anything above the player.
		{
			if (_bullet.b_isActive == false)
				createBullet(player.m_cLocation.X, player.m_cLocation.Y - 1, K_UP, _bullet, type);
			return true;
		}

		if (lastDirection == K_DOWN && (map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == ' ' || map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == '-')) //Check is anything below the player.
		{
			if (_bullet.b_isActive == false)
				createBullet(player.m_cLocation.X, player.m_cLocation.Y + 1, K_DOWN, _bullet, type);
			return true;
		}


		if (lastDirection == K_RIGHT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == ' ' || map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == '-') //Check is anything to the right player.
		{
			if (_bullet.b_isActive == false)
				createBullet(player.m_cLocation.X + 1, player.m_cLocation.Y, K_RIGHT, _bullet, type);
			return true;
		}


		if (lastDirection == K_LEFT && (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == ' ' || map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == '-')) //Check is anything to the left player.
		{
			if (_bullet.b_isActive == false)
				createBullet(player.m_cLocation.X - 1, player.m_cLocation.Y, K_LEFT, _bullet, type);
			return true;
		}
	}

	return false;
}
