#include "game.h"
#include "ReadMap.h"
#include "Framework\console.h"

struct Bullet
{
	short b_speed;
	COORD b_pos;
	EKEYS b_direction;
	bool b_isActive;
	bool b_type;
};

struct Portal
{
	COORD p_pos[2];
	bool p_isActive[2];
	bool p_type;
};

bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection, Bullet &_bullet, bool type);
void createBullet(short x, short y, EKEYS key, Bullet &_bullet, bool type);
void handleBulletProjectile(Bullet &_bullet, double &g_dElapsedTime, Console &g_Console, SMapData &map, Portal &_portal);
bool checkBulletCollision(Bullet &_bullet, SMapData &g_mapData, Console &g_Console, Portal &_portal);

void spawnPortal(Portal &_portal, COORD position, bool type);
void renderPortal(Portal &_portal, Console &g_Console);
void teleportPlayer(COORD playerPos, COORD portalPos);
