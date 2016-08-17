#include "ReadMap.h"

using namespace std;

extern SMapData g_mapData;

void draw_map_string(string resultMap)
{
	int TilesHeight = 150;
	int TilesWide = 150;

	for (int row = 0; row < TilesHeight; row++)
	{
		//char loopedString[150][150];

		for (int col = 0; col < TilesWide; col++)
		{

			//loopedString[row][col] = g_mapData.mapGrid[row][col];
			//if (g_mapData.mapGrid[row][col] == '#')
			//{
			//	loopedString[row][col] = (char)219;
			//}

			resultMap = g_mapData.mapGrid[row];
		}
	}
}