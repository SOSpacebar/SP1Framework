#include "ReadMap.h"

using namespace std;

SMapData g_mapData;



void readMap(int mapLevel)
{

	ifstream levelData;
	string levelInfo;
	string loopedString;

	switch (mapLevel)
	{
	case 1:
		//blah levelData.open("Map#.txt");
		levelData.open("Map.txt");
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
			else
			{
				g_mapData.mapGrid[row][col] = loopedString.at(col);
			}
		}
	}
	levelData.close();
}