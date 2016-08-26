#include "fieldOfView.h"

COORD c;

void renderFogOfWarAndMap(SMapData &g_mapData, SGameChar player, Console &g_Console, char fogMap[150][150], Bullet &_bullet, Portal &_portal)
{
	//Coord Variables
	c.X = 0;
	c.Y = 1;
	int tempValue = c.X;

	char fogMap2[150][150];

	//View Range Variables
	short viewRange = 6;
	short portalViewRange = 3;
	short bulletViewRange = 2;


	memset(fogMap2, '\0', sizeof(fogMap2[0][0]) * 150 * 150);
	
	//Check player position for rendering
	for (short x = player.m_cLocation.X - viewRange - 1; x < player.m_cLocation.X + viewRange + 1; x++)
	{
		for (short y = player.m_cLocation.Y - viewRange; y < player.m_cLocation.Y + viewRange - 2; y++)
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

	//Check portal 1 position for rendering
	if (_portal.p_isActive[0])
	{
		for (short p_x = _portal.p_pos[0].X - portalViewRange - 1; p_x < _portal.p_pos[0].X + portalViewRange + 1; p_x++)
		{
			for (short p_y = _portal.p_pos[0].Y - portalViewRange; p_y < _portal.p_pos[0].Y + portalViewRange - 2; p_y++)
			{
				if (p_x < 0)
				{
					continue;
				}
				if (p_y < 0)
				{
					continue;
				}

				fogMap[p_y][p_x] = g_mapData.mapGrid[p_y][p_x];
				fogMap2[p_y][p_x] = fogMap[p_y][p_x];
			}
		}
	}

	//Check portal 2 position for rendering
	if (_portal.p_isActive[1])
	{
		for (short p_x = _portal.p_pos[1].X - portalViewRange - 1; p_x < _portal.p_pos[1].X + portalViewRange + 1; p_x++)
		{
			for (short p_y = _portal.p_pos[1].Y - portalViewRange; p_y < _portal.p_pos[1].Y + portalViewRange - 2; p_y++)
			{
				if (p_x < 0)
				{
					continue;
				}
				if (p_y < 0)
				{
					continue;
				}

				fogMap[p_y][p_x] = g_mapData.mapGrid[p_y][p_x];
				fogMap2[p_y][p_x] = fogMap[p_y][p_x];
			}
		}
	}

	//Check bullet position for rendering
	if (_bullet.b_isActive)
	{
		for (short b_x = _bullet.b_pos.X - bulletViewRange - 1; b_x < _bullet.b_pos.X + bulletViewRange + 1; b_x++)
		{
			for (short b_y = _bullet.b_pos.Y - bulletViewRange; b_y < _bullet.b_pos.Y + bulletViewRange; b_y++)
			{
				if (b_x < 0)
				{
					continue;
				}
				if (b_y < 0)
				{
					continue;
				}

				fogMap[b_y][b_x] = g_mapData.mapGrid[b_y][b_x];
				fogMap2[b_y][b_x] = fogMap[b_y][b_x];
			}
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

			g_Console.writeToBuffer(c, fogMap[row][col], 0x08);

			if (fogMap2[row][col] != '\0')
			{
				g_Console.writeToBuffer(c, fogMap2[row][col], 0x0d);
			}


			c.X++;
		}

		c.X = tempValue;
		c.Y++;
	}
}