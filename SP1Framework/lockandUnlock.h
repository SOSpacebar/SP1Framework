#include "game.h"
#include "ReadMap.h"

bool checkDoorCollision(SGameChar player, SMapData map, SGameKey &g_iKey, SGameKey g_dDoor);
void RenderKey(SGameKey &g_iKey); // Rendering Key 
void LockedDoor(SGameKey &g_dDoor); // The Door Is lock If Player didnt get the Key
