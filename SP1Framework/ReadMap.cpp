#include "MapGenerator.h"
#include "DialogBox.h"
#include "ReadMap.h"
#include <fstream>

SMapData g_mapData;

void readMap(int mapLevel, SGameChar &_sChar, DialogStruct boxArr[], int &maxBox, SGameKey &g_iKey, SGameKey &g_dDoor, objectStruct _object[], short &totalNumObject, enemyStruct _enemy[])
{
	ifstream levelData;
	string levelInfo;
	string loopedString;
	COORD x;

	string mapArray[4];

	mapArray[0] = "MapData/Level1A.txt";
	mapArray[1] = "MapData/Level1B.txt";
	mapArray[2] = "MapData/Level1C.txt";
	mapArray[3] = "MapData/map3.txt";

	if (mapLevel > 3)
	{
		returnMap(totalNumObject, _object);
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
				else if (loopedString.at(col) == '<')
				{
					x.X = col;
					x.Y = row + 1;
					_object[totalNumObject].o_location = x;
					_object[totalNumObject].o_ID = "<";
					_object[totalNumObject].o_speed = 50;
					g_mapData.mapGrid[row][col] = ' ';
					totalNumObject++;
				}
				else if (loopedString.at(col) == 'o')
				{
					x.X = col;
					x.Y = row + 1;
					_object[totalNumObject].o_location = x;
					_object[totalNumObject].o_ID = "<O>";
					_object[totalNumObject].o_speed = 60;
					g_mapData.mapGrid[row][col] = ' ';
					totalNumObject++;
				}
				else if (loopedString.at(col) == 'O')
				{
					x.X = col;
					x.Y = row + 1;
					_object[totalNumObject].o_location = x;
					_object[totalNumObject].o_ID = "^Ov";
					_object[totalNumObject].o_speed = 60;
					g_mapData.mapGrid[row][col] = ' ';
					totalNumObject++;
				}
				else if (loopedString.at(col) == 'Q')
				{
					g_iKey.m_cLocation.X = col;
					g_iKey.m_cLocation.Y = row + 1;
					g_mapData.mapGrid[row][col] = ' ';
				}
				else if (loopedString.at(col) == '!')
				{
					boxArr[maxBox].Location.X = col;
					boxArr[maxBox].Location.Y = row + 1;
					g_mapData.mapGrid[row][col] = ' ';
					maxBox++;
				}
				else if (loopedString.at(col) == 'm')
				{
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