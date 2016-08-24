#include "ReadMap.h"
#include "game.h"
#include "MapGenerator.h"
#include "gameObject.h"

using namespace std;

SMapData g_mapData;
extern SGameKey g_iKey;
extern SGameKey g_dDoor;
extern objectStruct _object[20];
extern short totalNumObject;

void readMap(int mapLevel, SGameChar &_sChar)
{
	int IndexObject = 0;
	ifstream levelData;
	string levelInfo;
	string loopedString;
	COORD x;

	string mapArray[5];

	mapArray[0] = "MapData/map.txt";
	mapArray[1] = "MapData/Level1A.txt";
	mapArray[2] = "MapData/Level1B.txt";
	mapArray[3] = "MapData/Level1C.txt";
	mapArray[4] = "MapData/map2.txt";

	if (mapLevel > 4)
	{
		returnMap();
		return;
	}
	else
	{
		levelData.open(mapArray[mapLevel]);

		for (int row = 0; row < 150; row++)
		{
			if (levelData.eof())
				break;

			getline(levelData, loopedString);

			for (int col = 0; col < 150; col++)
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
					_sChar.m_cLocation.X = col;
					_sChar.m_cLocation.Y = row + 1;
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
				else if (loopedString.at(col) == 'E')
				{
					g_dDoor.m_cLocation.X = col;
					g_dDoor.m_cLocation.Y = row + 1;
					g_mapData.mapGrid[row][col] = (char)254;
				}
				else if (loopedString.at(col) == '*')
				{
					x.X = col;
					x.Y = row + 1;
					//_object[IndexObject].o_location.X = col;
					//_object[IndexObject].o_location.Y = row + 1;

					_object[IndexObject].o_location = x;
					g_mapData.mapGrid[row][col] = ' ';
					IndexObject++;
					totalNumObject++;
				}
				//else if (loopedString.at(col) == '<')
				//{
				//	_object[IndexObject].o_location.X = col;
				//	_object[IndexObject].o_location.Y = row + 1;
				//	g_mapData.mapGrid[row][col] = ' ';
				//	IndexObject++;
				//	totalNumObject++;
				//}
				else if (loopedString.at(col) == 'Q')
				{
					g_iKey.m_cLocation.X = col;
					g_iKey.m_cLocation.Y = row + 1;
					g_mapData.mapGrid[row][col] = ' ';
				}
				else
				{
					g_mapData.mapGrid[row][col] = loopedString.at(col);
				}
			}
		}
	}
	loopedString.clear();
	levelData.close();

}