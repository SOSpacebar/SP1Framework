#include "portalGun.h"

bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection, Bullet &_bullet)
{
	if (key == K_SPACE)
	{
		if (lastDirection == K_UP && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X] == ' ') //Check is anything above the player.
		{
			createBullet(player.m_cLocation.X, player.m_cLocation.Y - 1, K_UP, _bullet);
			return true;
		}

		if (lastDirection == K_DOWN && map.mapGrid[player.m_cLocation.Y + 1][player.m_cLocation.X] == ' ') //Check is anything below the player.
		{
			createBullet(player.m_cLocation.X, player.m_cLocation.Y + 1, K_DOWN, _bullet);
			return true;
		}


		if (lastDirection == K_RIGHT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == ' ') //Check is anything to the right player.
		{
			createBullet(player.m_cLocation.X + 1, player.m_cLocation.Y, K_RIGHT, _bullet);
			return true;
		}


		if (lastDirection == K_LEFT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == ' ') //Check is anything to the left player.
		{
			createBullet(player.m_cLocation.X - 1, player.m_cLocation.Y, K_LEFT, _bullet);
			return true;
		}
	}

	return false;
}

