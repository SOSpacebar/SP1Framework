#include "ReadMap.h"
#include "game.h"
using namespace std;

SMapData g_mapData;

extern SGameChar g_sChar;

void readMap(int mapLevel)
{

	ifstream levelData;
	string levelInfo;
	string loopedString;

	switch (mapLevel)
	{
	case 1:
		//blah levelData.open("Map#.txt");
		levelData.open("MapData/Map.txt");
		if (!levelData.is_open()){
			return;
		}
		break;
	case 2:
		//blah levelData.open("Map2.txt");
		break;

	default:
		//done levelData.open("Map.txt");
		break;
	}

	int TilesHeight = 150 ;
	int TilesWide = 150 ;

	for (int row = 0 ; row < TilesHeight; row++)
	{
		if (levelData.eof()) 
			break;

		getline(levelData, loopedString);

		for (int col = 0 ; col < TilesWide; col++)
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
	levelData.close();
}