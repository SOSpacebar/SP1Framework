#include "portalGun.h";

void createBullet(short x, short y, EKEYS key, Bullet &_bullet)
{
	short num = 0;
	COORD bulletPosition;
	bulletPosition.X = x;
	bulletPosition.Y = y;

	_bullet.b_pos = bulletPosition;
	_bullet.direction = key;
}