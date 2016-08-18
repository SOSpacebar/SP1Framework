#include "game.h"
#include "ReadMap.h"

struct bullet
{
	COORD b_pos;
	short b_speed;
	EKEYS direction;
};


bool fireGun(SGameChar player, SMapData map, EKEYS key, EKEYS lastDirection);
void createBullet(short x, short y, EKEYS key);
void handleBulletProjectile();
bool checkBulletCollision();
