#ifndef _PORTALGUN_H
#define _PORTALGUN_H

#include "game.h"
#include "HeaderIncludes.h"
#include "Framework\console.h"

struct Bullet
{
	short b_speed;
	EKEYS b_direction;
	bool b_isActive;
	bool b_type;
	COORD b_pos;
};

struct Portal
{
	COORD p_pos[2];
	bool p_isActive[2];
	bool p_type;
};

//Gun Functions
bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection, Bullet &_bullet, bool type);
void createBullet(short x, short y, EKEYS key, Bullet &_bullet, bool type);
void handleBulletProjectile(Bullet &_bullet, double &g_dElapsedTime, Console &g_Console, SMapData &map, Portal &_portal);
bool checkBulletCollision(Bullet &_bullet, SMapData &g_mapData, Console &g_Console, Portal &_portal);

//Portal Functions
void spawnPortal(Portal &_portal, COORD position, bool type);
void renderPortal(Portal &_portal, Console &g_Console);

void checkPlayerCollisionWithPortal(SGameChar &player, Portal portal);
void teleportPlayer(SGameChar &playerPos, COORD portalPos, Portal portalFlag);

void checkEBallCollsionWithPortal(COORD &xy, Portal portal);
void teleportEBall(COORD &xy, COORD portalPos, Portal portalFlag);

void skipper(void);

#endif 