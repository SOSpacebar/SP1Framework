#ifndef _READMAP_H
#define _READMAP_H

#include <string>
#include <fstream>
#include "game.h"


struct SMapData
{
	char mapGrid[150][150];
};

void readMap(int mapLevel, SGameChar &_sChar); // draw map
void draw_map_string(std::string resultMap); // draw map

#endif // _GAME_H