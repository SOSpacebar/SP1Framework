#include "collisionManager.h"

bool checkCollision(SGameChar player, SMapData map, EKEYS direction)
{
	if (direction == K_UP && map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == (char)219) //up
	{
		return false;
	}
	
	if (direction == K_DOWN && map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == (char)219) //down
	{
		return false;
	}
	
	
	if (direction == K_RIGHT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)219) //right
	{
		return false;
	}
	
	
	if (direction == K_LEFT && map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == (char)219) //left
	{
		return false;
	}

	return true;
}
