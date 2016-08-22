#include "ReadMap.h"
#include "game.h"
using namespace std;

SMapData g_mapData;

extern SGameChar g_sChar;

/*
TODO: REFERNECE TO SGMAECHAR
*/
void readMap(int mapLevel)
{

	ifstream levelData;
	string levelInfo;
	string loopedString;

	string mapArray[5];

	mapArray[0] = "MapData/map.txt";
	mapArray[1] = "MapData/map1a.txt";
	mapArray[2] = "MapData/map1b.txt";
	mapArray[3] = "MapData/map1c.txt";
	mapArray[4] = "MapData/map2.txt";

	levelData.open(mapArray[mapLevel]);

	for (int row = 0 ; row < 150; row++)
	{
		if (levelData.eof()) 
			break;

		getline(levelData, loopedString);

		for (int col = 0 ; col < 150; col++)
		{
			if (loopedString[col] == '\0')
			{
				break;
			}
			if (loopedString.at(col) == '#')
			{
				g_mapData.mapGrid[row][col] = (char)219;
			}
			else if (loopedString.at(col) == 'S')
			{
				g_sChar.m_cLocation.X = col;
				g_sChar.m_cLocation.Y = row+1;
				g_mapData.mapGrid[row][col] = loopedString.at(col);
			}
			else if (loopedString.at(col) == '^')
			{
				g_mapData.mapGrid[row][col] = (char)187;
			}
			else if (loopedString.at(col) == '%')
			{
				g_mapData.mapGrid[row][col] = (char)188;
			}
			else if (loopedString.at(col) == '(')
			{
				g_mapData.mapGrid[row][col] = (char)200;
			}
			else if (loopedString.at(col) == '$')
			{
				g_mapData.mapGrid[row][col] = (char)201;
			}
			else if (loopedString.at(col) == 'K')
			{
				g_mapData.mapGrid[row][col] = (char)237;
			}
			else if (loopedString.at(col) == 'D')
			{
				g_mapData.mapGrid[row][col] = (char)178;
			}
			else
			{
				g_mapData.mapGrid[row][col] = loopedString.at(col);
			}
		}
	}
	loopedString.clear();
	levelData.close();
}