#ifndef _READMAP_H
#define _READMAP_H

#include "HeaderIncludes.h"
#include "DialogBox.h"

void readMap(int mapLevel, SGameChar &g_sChar, DialogStruct boxArr[], int &maxBox, SGameKey &g_iKey, SGameKey &g_dDoor, struct objectStruct(*_object)[20], short &totalNumObject); // draw map


#endif // _GAME_H