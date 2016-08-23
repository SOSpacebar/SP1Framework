#include "fieldOfView.h"

COORD c;

void renderFogOfWarAndMap(SMapData &g_mapData, SGameChar player, Console &g_Console, char fogMap[150][150])
{
	c.X = 0;
	c.Y = 1;
	int tempValue = c.X;

	char fogMap2[150][150];

	short viewRange = 6;
	short x;
	short y;

	memset(fogMap2, '\0', sizeof(fogMap2[0][0]) * 150 * 150);
	

	for (x = player.m_cLocation.X - viewRange - 1; x < player.m_cLocation.X + viewRange + 1; x++)
	{
		for (y = player.m_cLocation.Y - viewRange; y < player.m_cLocation.Y + viewRange - 2; y++)
		{
			if (x < 0)
			{
				continue;
			}
			if (y < 0)
			{
				continue;
			}

			fogMap[y][x] = g_mapData.mapGrid[y][x];
			fogMap2[y][x] = fogMap[y][x];
		}
	}

	//Render Map
	for (int row = 0; row < 150; row++)
	{
		for (int col = 0; col < 150; col++)
		{
			if (fogMap[row][col] == '\0' || fogMap[row][col] == '\n')
			{
				break;
			}

			if ((fogMap[row][col] == (char)187) || (fogMap[row][col] == (char)188) || (fogMap[row][col] == (char)200) || (fogMap[row][col] == (char)201))
			{
				g_Console.writeToBuffer(c, fogMap[row][col], 0x0A);
			}
			
			else
			{
				g_Console.writeToBuffer(c, fogMap[row][col], 0x08);

				if (fogMap2[row][col] != '\0')
				{
					g_Console.writeToBuffer(c, fogMap2[row][col], 0x0d);
				}
			}

			c.X++;
		}

		c.X = tempValue;
		c.Y++;
	}
}