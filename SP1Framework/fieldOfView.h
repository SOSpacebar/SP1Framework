#ifndef _FIELDOFVIEW_H
#define _FIELDOFVIEW_H

#include "game.h"
#include "ReadMap.h"
#include "Framework\console.h"
#include "portalGun.h"

void renderFogOfWarAndMap(SMapData &g_mapData, SGameChar player, Console &g_Console, char fogMap[150][150], Bullet &_bullet, Portal &_portal);

#endif