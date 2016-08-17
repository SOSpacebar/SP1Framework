#include "collisionManager.h"

bool checkCollision(SGameChar player, SMapData map, EKEYS direction)
{
	if (direction == K_UP && map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == ' ') //up
	{
		return true;
	}
	
	if (direction == K_DOWN && map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == ' ') //down
	{
		return true;
	}
	
	
	if (direction == K_RIGHT && map.mapGrid[player.m_cLocation.Y-1][player.m_cLocation.X + 1] == ' ') //right
	{
		return true;
	}
	
	
	if (direction == K_LEFT && map.mapGrid[player.m_cLocation.Y-1][player.m_cLocation.X - 1] == ' ') //left
	{
		return true;
	}

	return false;
}
