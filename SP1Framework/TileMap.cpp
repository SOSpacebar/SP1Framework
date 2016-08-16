#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "game.h"

using namespace std;

extern SMapData g_mapData;

void draw_map_string(string resultMap)
{
	int TilesHeight = 50;
	int TilesWide = 50;

	for (int row = 0; row < TilesHeight; row++)
	{
		char loopedString[50][50];

		for (int col = 0; col < TilesWide; col++)
		{

			loopedString[row][col] = g_mapData.mapGrid[row][col];

			resultMap = g_mapData.mapGrid[row];
		}
	}
}