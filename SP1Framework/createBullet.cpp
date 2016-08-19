#include "portalGun.h"

void createBullet(short x, short y, EKEYS key, Bullet &_bullet, bool type)
{
	short num = 0;
	COORD bulletPosition;
	bulletPosition.X = x;
	bulletPosition.Y = y;

	_bullet.b_pos = bulletPosition;
	_bullet.b_direction = key;
	_bullet.b_isActive = true;
	_bullet.b_type = type;
}