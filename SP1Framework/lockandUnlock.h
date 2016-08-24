#include "game.h"
#include "ReadMap.h"
#include "portalGun.h"

bool checkDoorCollision(SGameChar player, SMapData map, SGameKey &g_iKey, SGameKey g_dDoor);
void RenderKey(SGameKey &g_iKey, Portal _portal, SGameChar _sChar); // Rendering Key 
void LockedDoor(SGameKey &g_dDoor, SGameKey &g_iKey, Portal _portal, SGameChar _sChar); // The Door Is lock If Player didnt get the Key
