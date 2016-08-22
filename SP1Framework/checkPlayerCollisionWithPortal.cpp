#include "portalGun.h"

void checkPlayerCollisionWithPortal(SGameChar &player, Portal portal)
{
	if (player.m_cLocation.X == portal.p_pos[0].X && player.m_cLocation.Y == portal.p_pos[0].Y) //Check is anything above the player.
	{
		teleportPlayer(player, portal.p_pos[1], portal);
	}
	else if (player.m_cLocation.X == portal.p_pos[1].X && player.m_cLocation.Y == portal.p_pos[1].Y) //Check is anything above the player.
	{
		teleportPlayer(player, portal.p_pos[0], portal);
	}
}

void teleportPlayer(SGameChar &playerPos, COORD portalPos, Portal portalFlag)
{
	if (portalFlag.p_isActive[0] == true && portalFlag.p_isActive[1] == true)
	{
		playerPos.m_cLocation = portalPos;
	}
}
