#include "game.h"
#include "ReadMap.h"
#include "Framework\console.h"

struct Bullet
{
	COORD b_pos;
	short b_speed;
	EKEYS direction;
	bool b_isActive;
};


bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection, Bullet &_bullet, bool type);
void createBullet(short x, short y, EKEYS key, Bullet &_bullet);
void handleBulletProjectile(Bullet &_bullet, double &g_dElapsedTime, Console &g_Console, SMapData &map);
bool checkBulletCollision(Bullet &_bullet, SMapData &g_mapData, Console &g_Console);
