#include "ReadMap.h"

using namespace std;

extern SMapData g_mapData;

void draw_map_string(string resultMap)
{
	for (int row = 0; row < 150; row++)
	{
		resultMap = g_mapData.mapGrid[row];
	}
}