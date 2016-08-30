#ifndef _HANDLESTATSSCREEN_H
#define _HANDLESTATSSCREEN_H

#include "game.h"
#include "inventory.h"

void statsUserInterface(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dElapsedTime, double &g_dBounceTime, PlayerStats &getPlayerStats, Inventory &_inventory, SMouseEvent g_mouseEvent);

#endif