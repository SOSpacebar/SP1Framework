#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "game.h"

using namespace std;

SMapData g_mapData;


void readMap(int mapLevel)
{
	ifstream levelData;

	switch (mapLevel)
	{
	case 1:
		//blah levelData.open("Map#.txt");
		levelData.open("Map.txt");
		if (!levelData.is_open()){
			std::cout << "Doesn't work" << std::endl;
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

	

	string levelInfo;
	int TilesHeight = 50 ;
	int TilesWide = 50 ;

	for (int row = 0 ; row < TilesHeight; row++)
	{
		if (levelData.eof()) 
			break;

		string loopedString;
		getline(levelData, loopedString);

		for (int col = 0 ; col < TilesWide; col++)
		{
			if (loopedString[col] == '\0')
			{
				break;
			}
			g_mapData.mapGrid[row][col] = loopedString.at(col);

		}
	}
}