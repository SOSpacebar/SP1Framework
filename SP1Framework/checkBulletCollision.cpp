#include "portalGun.h"

bool checkBulletCollision(Bullet &_bullet, SMapData &g_mapData, Console &g_Console, Portal &_portal)
{
	COORD portalPosition;

	if (_bullet.b_direction == K_UP && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall above the bullet.
	{
		portalPosition.X = _bullet.b_pos.X;
		portalPosition.Y = _bullet.b_pos.Y + 1;
		spawnPortal(_portal, portalPosition, _bullet.b_type);
		_bullet.b_isActive = false;
		return true;
	}

	if (_bullet.b_direction == K_DOWN && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall below the bullet.
	{
		portalPosition.X = _bullet.b_pos.X;
		portalPosition.Y = _bullet.b_pos.Y - 1;
		spawnPortal(_portal, portalPosition, _bullet.b_type);
		_bullet.b_isActive = false;
		return true;
	}

	if (_bullet.b_direction == K_RIGHT && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall to the right of the bullet.
	{
		portalPosition.X = _bullet.b_pos.X - 1;
		portalPosition.Y = _bullet.b_pos.Y;
		spawnPortal(_portal, portalPosition, _bullet.b_type);
		_bullet.b_isActive = false;
		return true;
	}

	if (_bullet.b_direction == K_LEFT && g_mapData.mapGrid[_bullet.b_pos.Y - 1][_bullet.b_pos.X] == (char)219) //Check is a wall to the left of the bullet.
	{
		portalPosition.X = _bullet.b_pos.X + 1;
		portalPosition.Y = _bullet.b_pos.Y;
		spawnPortal(_portal, portalPosition, _bullet.b_type);
		_bullet.b_isActive = false;
		return true;
	}

	return false;
}