#include "items.h"
#include <random>

Items::Items()
{
	RNGitem();
}

Items::~Items()
{
}

void Items::setItemDetails(string name, string type, int level, int str, int con, int attackV, int healthV)
{

}

void Items::setName(string name)
{
	item_name = name;
}

void Items::RNGitem()
{
	std::random_device rand;
	std::mt19937 twist(rand());

	std::uniform_int_distribution<> num(1, 3);
	std::uniform_int_distribution<> statsRand(1, 10);

	int rngNum = num(twist);
	int rngAttack = statsRand(twist);
	int rngHealth = statsRand(twist);
	int rngStr = statsRand(twist);
	int rngCon = statsRand(twist);
	int rngInt = statsRand(twist);
	int rngLevel = statsRand(twist);

	switch(rngNum)
	{
		case 1:
			item_name = "g_Sword";
			item_type = "Weapon";
			item_reqLevel = rngLevel;
			item_str = rngStr;
			item_con = rngCon;
			item_int = rngInt;
			item_attackValue = rngAttack;
			item_healthValue = 0;
			break;
		case 2:
			item_name = "g_Armor";
			item_type = "Armor";
			item_reqLevel = rngLevel;
			item_str = rngStr;
			item_con = rngCon;
			item_int = rngInt;
			item_attackValue = 0;
			item_healthValue = rngHealth;
			break;
		case 3:
			item_name = "g_Ring";
			item_type = "Others";
			item_reqLevel = rngLevel;
			item_str = rngStr;
			item_con = rngCon;
			item_int = rngInt;
			item_attackValue = rngAttack;
			item_healthValue = rngHealth;
			break;
	}
}