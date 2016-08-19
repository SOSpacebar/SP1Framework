#include "collisionManager.h"
#include "game.h"

extern int g_currLevel;
extern EGAMESTATES g_eGameState;

bool checkPlayerCollision(SGameChar player, SMapData map, EKEYS direction)
{
	if (direction == K_UP && map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == (char)219) //Check is anything above the player.
	{
		return false;
	}
	
	if (direction == K_DOWN && map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == (char)219) //Check is anything below the player.
	{
		return false;
	}
	
	if (direction == K_RIGHT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)219) //Check is anything to the right player.
	{
		return false;
	}
	
	
	if (direction == K_LEFT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == (char)219) //Check is anything to the left player.
	{
		return false;
	}

	if ((map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)187) || (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)188) || (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)200) || (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)201))
	{
		g_currLevel = 4;
		g_eGameState = S_LOADLEVEL;
	}

	return true;
}
