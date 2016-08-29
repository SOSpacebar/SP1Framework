#include "items.h"
#include <ctime>

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
	std::srand(time(NULL));
	std::rand();

	int rngNum = rand() % 3 + 1;
	int rngAttack = rand() % 10 + 1;
	int rngHealth = rand() % 10 + 1;
	int rngStr = rand() % 10 + 1;
	int rngCon = rand() % 10 + 1;
	int rngLevel= rand() % 10 + 1;

	switch(rngNum)
	{
		case 1:
			item_name = "g_Sword";
			item_type = "Weapon";
			item_reqLevel = rngLevel;
			item_reqStr = rngStr;
			item_reqCon = rngCon;
			item_attackValue = rngAttack;
			item_healthValue = 0;
			break;
		case 2:
			item_name = "g_Armor";
			item_type = "Armor";
			item_reqLevel = rngLevel;
			item_reqStr = rngStr;
			item_reqCon = rngCon;
			item_attackValue = rngAttack;
			item_healthValue = 0;
			break;
		case 3:
			item_name = "g_Ring";
			item_type = "Others";
			item_reqLevel = rngLevel;
			item_reqStr = rngStr;
			item_reqCon = rngCon;
			item_attackValue = rngAttack;
			item_healthValue = 0;
			break;
	}
}