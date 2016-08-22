#include "collisionManager.h"
#include "Framework/console.h"

extern int g_currLevel;
extern EGAMESTATES g_eGameState;
extern SGameKey g_iKey;
extern SGameKey g_dDoor;
bool checkPlayerCollision(SGameChar player, SMapData map, EKEYS direction)
{
	if (direction == K_UP) 	 //Check is anything above the player.
	{
		if (map.mapGrid[player.m_cLocation.Y - 2][player.m_cLocation.X] == (char)219)
		return false;
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 1 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)
		return false;
	}

	if (direction == K_DOWN) //Check is anything below the player.
	{
		if (map.mapGrid[player.m_cLocation.Y][player.m_cLocation.X] == (char)219)
		return false;
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y == g_dDoor.m_cLocation.Y - 1 && g_iKey.m_bActive == true)
		return false;
	}

	if (direction == K_RIGHT) //Check is anything to the right player.
	{
		if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)219)
		return false;
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X - 1 && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)
		return false;
	}

	if (direction == K_LEFT) //Check is anything to the left player.
	{
		if (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X - 1] == (char)219)
		return false;
		if (player.m_cLocation.X == g_dDoor.m_cLocation.X + 1 && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)
		return false;
	}

	if ((map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)187) || (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)188) || (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)200) || (map.mapGrid[player.m_cLocation.Y - 1][player.m_cLocation.X + 1] == (char)201))
	{
		g_currLevel = 4;
		g_eGameState = S_LOADLEVEL;
	}
	return true;
<<<<<<< HEAD
}
=======
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

>>>>>>> 0b0075faeb3c3a34245b063d443d35b5d9f41922
