#include "portalGun.h"

void renderPortal(Portal &_portal, Console &g_Console)
{
	if (_portal.p_isActive[0] == true)
	{
		g_Console.writeToBuffer(_portal.p_pos[0], '@', 0x0A);
	}

	if (_portal.p_isActive[1] == true)
	{
  		g_Console.writeToBuffer(_portal.p_pos[1], '@', 0x0C);
	}
}