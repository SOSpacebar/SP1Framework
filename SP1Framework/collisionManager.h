#include "game.h"
#include "ReadMap.h"

bool checkPlayerCollision(SGameChar player, SMapData map, EKEYS direction, EGAMESTATES &g_eGameState, short &g_currLevel, SGameKey g_iKey, SGameKey g_dDoor);