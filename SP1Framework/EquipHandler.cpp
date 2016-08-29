#include "EquipHandler.h"

Equipment::Equipment()
{
	//nothign is created
}

Equipment::~Equipment()
{
	//used for destructing values
	//please add removal of equipments and reseting every equipment to 0 here.
	//run removeEquipment function here?
}

void Equipment::getEquippedStats(Items items, PlayerStats playerStats)
{
	//take items stats and add to player stats.
	//mark items getting equiped and check if goes to collect slot.
}

void Equipment::removeEquipments(Items items, PlayerStats playerStats)
{
	//when unequip weapons, run this functions to remove the stats that was added.
	//clear the slot too
}

//below should add draw function for Equipped and Unequip