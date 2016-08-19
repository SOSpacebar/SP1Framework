#include "portalGun.h"

void spawnPortal(Portal &_portal, COORD position, bool type)
{
	if (type == 0)
	{
		_portal.p_pos[0] = position;
		_portal.p_isActive[0] = true;
	}
	if (type == 1)
	{
		_portal.p_pos[1] = position;
		_portal.p_isActive[1] = true;
	}

	_portal.p_type = type;	
}

