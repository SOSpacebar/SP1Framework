#include "collisionManager.h"
#include "game.h"
#include "Framework/console.h"

extern int g_currLevel;
extern EGAMESTATES g_eGameState;

SGameKey g_iKey;
SGameKey g_dDoor;
extern EGAMESTATES g_eGameState;

extern Console g_Console;


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

	if (player.m_cLocation.Y == g_iKey.m_cLocation.Y && player.m_cLocation.X == g_iKey.m_cLocation.X && g_iKey.m_bActive) //Check Player touches the Key
	{
		g_iKey.m_bActive = false;
		return true;
	}

	if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == false)// DAH DOOR
	{
		return true;
	}

	if (direction == K_UP && player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 2 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// DAH DOOR
	{
		return false;
	}
	if (direction == K_DOWN && player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// DAH DOOR
	{
		return false;
	}
	if (direction == K_RIGHT && player.m_cLocation.X + 1 == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 1 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// DAH DOOR
	{
		return false;
	}
	if (direction == K_LEFT && player.m_cLocation.X - 1 == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 1 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// DAH DOOR
	{
		return false;
	}

	return true;
}

void RenderKey()
{
	g_iKey.m_cLocation.X = 10;
	g_iKey.m_cLocation.Y = 10;
	if (g_iKey.m_bActive == true){
		g_Console.writeToBuffer(g_iKey.m_cLocation, (char)237);
	}
}

void LockedDoor()
{
	g_dDoor.m_cLocation.X = 20;
	g_dDoor.m_cLocation.Y = 10;
	if (g_dDoor.m_bActive)
	{
		g_Console.writeToBuffer(g_dDoor.m_cLocation, (char)178);
	}
}

