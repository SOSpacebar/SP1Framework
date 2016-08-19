#include "portalGun.h"

double _elapsedTime;
short travelTime;

void handleBulletProjectile(Bullet &_bullet, double &g_dElapsedTime, Console &g_Console, SMapData &map)
{
	_elapsedTime = g_dElapsedTime;
	travelTime++;

	if (_elapsedTime == g_dElapsedTime && travelTime == 5)
	{
		travelTime = 0;
		if (checkBulletCollision(_bullet, map, g_Console) == false)
		{
			if (_bullet.b_direction == K_UP)
			{
				_bullet.b_pos.Y--;
			}
			if (_bullet.b_direction == K_DOWN)
			{
				_bullet.b_pos.Y++;
			}
			if (_bullet.b_direction == K_LEFT)
			{
				_bullet.b_pos.X--;
			}
			if (_bullet.b_direction == K_RIGHT)
			{
				_bullet.b_pos.X++;
			}
		}
	}
	
	if (checkBulletCollision(_bullet, map, g_Console) == false)
	{
		if (_bullet.b_type == 1)
			g_Console.writeToBuffer(_bullet.b_pos, 'o', 0x6D);
		else
			g_Console.writeToBuffer(_bullet.b_pos, 'x', 0x6D);
	}
}