#ifndef _DIALOGBOX_H
#define _DIALOGBOX_H

#include "Framework\console.h"
#include "game.h"

struct DialogStruct
{
	bool isActive;
	COORD Location;
};

void dialogCollision(int boxIndex, Console &g_Console, int maxBox);
void checkDialogBox(DialogStruct boxArr[], SGameChar _sChar, int maxBox, int boxIndex, Console &g_Console);


#endif