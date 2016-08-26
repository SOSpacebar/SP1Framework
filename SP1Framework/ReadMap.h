#ifndef _READMAP_H
#define _READMAP_H

#include "HeaderIncludes.h"
#include "DialogBox.h"
#include "enemyProperties.h"

void readMap(int mapLevel, SGameChar &g_sChar, DialogStruct boxArr[], int &maxBox, SGameKey &g_iKey, SGameKey &g_dDoor, objectStruct _object[], short &totalNumObject, enemyStruct _enemy[]); // draw map

#endif // _GAME_H