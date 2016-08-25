#include "Framework/console.h"
#include "lockandUnlock.h"
#include <math.h>
#include <stdio.h>


extern Console g_Console;

bool checkDoorCollision(SGameChar &player, SMapData &map, SGameKey &g_iKey, SGameKey &g_dDoor)
{
	if (player.m_cLocation.Y == g_iKey.m_cLocation.Y && player.m_cLocation.X == g_iKey.m_cLocation.X && g_iKey.m_bActive) //Checking the player gotten the key or not
	{
		g_iKey.m_bActive = false;
		return true;
	}

	if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == false) // if the key is taken the door will vanish
	{
		return true;
	}

	if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 2 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true) // if the key isn't taken player cannot go through
	{
		return false;
	}
	if (player.m_cLocation.X == g_dDoor.m_cLocation.X && player.m_cLocation.Y == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// if the key isn't taken player cannot go through
	{
		return false;
	}
	if (player.m_cLocation.X + 1 == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 1 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// if the key isn't taken player cannot go through
	{
		return false;
	}
	if (player.m_cLocation.X - 1 == g_dDoor.m_cLocation.X && player.m_cLocation.Y - 1 == g_dDoor.m_cLocation.Y && g_iKey.m_bActive == true)// if the key isn't taken player cannot go through
	{
		return false;
	}
	return true;
}

//Render the key position
void RenderKey(SGameKey &g_iKey, Portal &_portal, SGameChar &_sChar)
{
	if ((sqrt((_portal.p_pos[1].X - g_iKey.m_cLocation.X)   *
		(_portal.p_pos[1].X - g_iKey.m_cLocation.X)		   +
		((_portal.p_pos[1].Y - g_iKey.m_cLocation.Y)       *
		(_portal.p_pos[1].Y - g_iKey.m_cLocation.Y))) <= 3) ||
		(sqrt((_portal.p_pos[0].X - g_iKey.m_cLocation.X)   *
		(_portal.p_pos[0].X - g_iKey.m_cLocation.X) +
		((_portal.p_pos[0].Y - g_iKey.m_cLocation.Y)       *
		(_portal.p_pos[0].Y - g_iKey.m_cLocation.Y))) <= 3) ||
		(sqrt((_sChar.m_cLocation.X - g_iKey.m_cLocation.X) *
		(_sChar.m_cLocation.X - g_iKey.m_cLocation.X) +
		((_sChar.m_cLocation.Y - g_iKey.m_cLocation.Y)	 *
		(_sChar.m_cLocation.Y - g_iKey.m_cLocation.Y))) <= 8))
	{
		if (g_iKey.m_bActive == true)
		{
			g_Console.writeToBuffer(g_iKey.m_cLocation, (char)237);
		}
	}
	
}

//Render the door position
void LockedDoor(SGameKey &g_dDoor, SGameKey &g_iKey, Portal &_portal, SGameChar &_sChar)
{
	if ((sqrt((_portal.p_pos[1].X - g_dDoor.m_cLocation.X)   *
		(_portal.p_pos[1].X - g_dDoor.m_cLocation.X)	    +
		((_portal.p_pos[1].Y - g_dDoor.m_cLocation.Y)       *
		(_portal.p_pos[1].Y - g_dDoor.m_cLocation.Y))) <= 3) ||
		(sqrt((_portal.p_pos[0].X - g_dDoor.m_cLocation.X)   *
		(_portal.p_pos[0].X - g_dDoor.m_cLocation.X)		+
		((_portal.p_pos[0].Y - g_dDoor.m_cLocation.Y)       *
		(_portal.p_pos[0].Y - g_dDoor.m_cLocation.Y))) <= 3) ||
		(sqrt((_sChar.m_cLocation.X - g_dDoor.m_cLocation.X) *
		(_sChar.m_cLocation.X - g_dDoor.m_cLocation.X) +
		((_sChar.m_cLocation.Y - g_dDoor.m_cLocation.Y)	 *
		(_sChar.m_cLocation.Y - g_dDoor.m_cLocation.Y))) <= 8))
	{
		if (g_dDoor.m_bActive)
		{
			if (g_iKey.m_bActive)
			{
				g_Console.writeToBuffer(g_dDoor.m_cLocation, (char)254, 0x40);
			}
			else
			{
				g_Console.writeToBuffer(g_dDoor.m_cLocation, (char)254, 0xA0);
			}

		}
	}
}

