#include "items.h"
#include <random>

Items::Items()
{
	RNGitem();
}

Items::~Items()
{
}

void Items::setItemDetails(string name, string type, int level, int str, int con, int attackV, int healthV, bool equipSlotWeapon, bool equipSlotArmor, bool equipSlotAcc)
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
	std::uniform_int_distribution<> nameRand(0, 9);

	int rngNum = num(twist);
	int rngAttack = statsRand(twist);
	int rngHealth = statsRand(twist);
	int rngStr = statsRand(twist);
	int rngCon = statsRand(twist);
	int rngInt = statsRand(twist);
	int rngLevel = statsRand(twist);
	string WeaponArr[10] = {"Arde Dagger", "Catacombs Club", "Brandish Spear", "Duris Demon Pike", "Gravity Greatsword", "Valia", "Magas Rapier", "Cheminis Rod", "Audra Staff", "Slaake Zweihander"};
	string ArmorArr[10] = {"BeetleBack", "Lolopather Shield", "Didel Tower Shield", "Ferret Marauder Shield", "Aias", "Banshee Veil", "Bone Armor", "Crimson Leather Armor", "Dio Chainmail", "Allerno Robe"};
	string AccArr[10] = {"Petamion", "Animus", "Electus", "Guardian", "Bearkaras Bracelet", "Archmage Bangle", "Elements Dance", "Red Armband", "Maven Necklace", "Lightna Chain"};

	switch(rngNum)
	{
		case 1:
			item_name = WeaponArr[nameRand(twist)];
			item_type = "Weapon";
			item_reqLevel = rngLevel;
			item_str = rngStr;
			item_con = rngCon;
			item_int = rngInt;
			item_attackValue = rngAttack;
			item_healthValue = 0;
			item_equipSlotWeapon = true;
			item_equipSlotArmor = false;
			item_equipSlotAcc = false;
			break;
		case 2:
			item_name = ArmorArr[nameRand(twist)];
			item_type = "Armor";
			item_reqLevel = rngLevel;
			item_str = rngStr;
			item_con = rngCon;
			item_int = rngInt;
			item_attackValue = 0;
			item_healthValue = rngHealth;
			item_equipSlotWeapon = false;
			item_equipSlotArmor = true;
			item_equipSlotAcc = false;
			break;
		case 3:
			item_name = AccArr[nameRand(twist)];
			item_type = "Others";
			item_reqLevel = rngLevel;
			item_str = rngStr;
			item_con = rngCon;
			item_int = rngInt;
			item_attackValue = rngAttack;
			item_healthValue = rngHealth;
			item_equipSlotWeapon = false;
			item_equipSlotArmor = false;
			item_equipSlotAcc = true;
			break;
	}
}