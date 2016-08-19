#include "portalGun.h"

void renderPortal(Portal &_portal, Console &g_Console)
{
	if (_portal.p_isActive[0] == true)
	{
		g_Console.writeToBuffer(_portal.p_pos[0], 'P', 0x6D);
	}

	if (_portal.p_isActive[1] == true)
	{
		g_Console.writeToBuffer(_portal.p_pos[1], 'E', 0x6D);
	}
}