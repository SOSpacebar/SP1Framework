#include "collisionManager.h"
#include "Framework/console.h"
#include "enemyProperties.h"

//extern Console g_Console;


bool checkPlayerCollision(SGameChar player, SMapData map, EKEYS direction, EGAMESTATES &g_eGameState, short &g_currLevel, SGameKey &g_iKey, SGameKey &g_dDoor, int indexEnemy, enemyStruct _enemy[])
{
	if (direction == K_UP) 	 //Check is anything above the player.
	{
		if (map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == (char)219)
			return false;
		if (map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == '-')
		{
			return false;
		}
			
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 1 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)
			return false;
	}

	if (direction == K_DOWN) //Check is anything below the player.
	{
		if (map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == (char)219)
			return false;
		if (map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == '-')
		{
			return false;
		}
			
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y == g_dDoor.m_cLocation.Y - 1 && g_iKey.m_bActive == true)
			return false;
	}

	if (direction == K_RIGHT) //Check is anything to the right player.
	{
		if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)219)
			return false;
		if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == '-')
		{
			return false;

		}
			
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X - 1 && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)
			return false;
	}

	if (direction == K_LEFT) //Check is anything to the left player.
	{
		if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == (char)219)
			return false;
		if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == '-')
		{
			return false;
		}
			
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X + 1 && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)
			return false;
	}	

	if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X] == (char)254)
	{
		g_currLevel++;
		g_eGameState = S_LOADLEVEL;
	}
	return true;
}

