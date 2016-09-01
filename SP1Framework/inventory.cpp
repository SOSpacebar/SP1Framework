#include "inventory.h"
#include "game.h"

class Items;

extern Items itemsArray[15]; 

Inventory::Inventory()
{
	//inventorySize = 15;
	//numberOfItems = 0;
	//itemsArray = new Items*[inventorySize];
}


Inventory::~Inventory()
{
	//for (int i = 0; i < numberOfItems; i++)
	//{
	//	delete itemsArray[i];
	//}

	//delete itemsArray;
}

bool Inventory::getItemArrayWeaponSlot(int arrayIndex)
{
	return itemsArray[arrayIndex].getEquipSlotWeapon();
}

bool Inventory::getItemArrayArmorSlot(int arrayIndex)
{
	return itemsArray[arrayIndex].getEquipSlotArmor();
}

bool Inventory::getItemArrayAccSlot(int arrayIndex)
{
	return itemsArray[arrayIndex].getEquipSlotAcc();
}

int Inventory::getItemStr(int arrayIndex)
{
	return itemsArray[arrayIndex].getStr();
}

int Inventory::getItemCon(int arrayIndex)
{
	return itemsArray[arrayIndex].getCon();
}
int Inventory::getItemInt(int arrayIndex)
{
	return itemsArray[arrayIndex].getInt();
}
int Inventory::getAttack(int arrayIndex)
{
	return itemsArray[arrayIndex].getAttackValue();
}
int Inventory::getHealth(int arrayIndex)
{
	return itemsArray[arrayIndex].getHealthValue();
}

void Inventory::addItem(const Items &item)
{
	itemsArray[numberOfItems++] = Items(item);
}

void Inventory::removeItem(int index)
{
	//if (index < inventorySize)
	//delete itemsArray[index];
}

void Inventory::setNumberOfItems(int num)
{
	numberOfItems = num;
}

void Inventory::debugPrint(Equipment &equip, Inventory &_inventory)
{
	equip.wearEquipment(*itemsArray, _playerStats, _inventory);

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 15;

	g_Console.writeToBuffer(c, "=======================================================Inventory========================================================", 0x03);
	c.Y += 2;
	c.X = 19;
	g_Console.writeToBuffer(c, "|Name|===============|Type|==|Level|==|Attack|==|Health|==|Str|==|Con|==|Int|", 0x03);
	c.Y++;
	for (int i = 0; i < numberOfItems; i++)
	{
		c.X = 16;
		if ((equip.getEquippedWeap() == i) || (equip.getEquippedArmor() == i) || (equip.getEquippedAcc() == i))
		{
			g_Console.writeToBuffer(c, "U", 0x04);
		}
		else
		{
			g_Console.writeToBuffer(c, "E", 0x0A);
		}
		c.X = 18;
		g_Console.writeToBuffer(c, itemsArray[i].getName(), 0x03);		
		c.X += 23;
		g_Console.writeToBuffer(c, itemsArray[i].getType(), 0x03);
		c.X += 10;
		g_Console.writeToBuffer(c, std::to_string(itemsArray[i].getReqLevel()), 0x03);
		c.X += 10;
		g_Console.writeToBuffer(c, std::to_string(itemsArray[i].getAttackValue()), 0x03);
		c.X += 10;
		g_Console.writeToBuffer(c, std::to_string(itemsArray[i].getHealthValue()), 0x03);
		c.X += 7;
		g_Console.writeToBuffer(c, std::to_string(itemsArray[i].getStr()), 0x03);
		c.X += 7;
		g_Console.writeToBuffer(c, std::to_string(itemsArray[i].getCon()), 0x03);
		c.X += 7;
		g_Console.writeToBuffer(c, std::to_string(itemsArray[i].getInt()), 0x03);
		c.Y++;
	}

	if ((equip.getWeaponSlot() == true))
	{
		c.X = 18;
		if (equip.getEquippedWeap() == 0)
		{
			c.Y = 18;
		}
		else if (equip.getEquippedWeap() == 1)
		{
			c.Y = 19;
		}
		else if (equip.getEquippedWeap() == 2)
		{
			c.Y = 20;
		}
		else if (equip.getEquippedWeap() == 3)
		{
			c.Y = 21;
		}
		else if (equip.getEquippedWeap() == 4)
		{
			c.Y = 22;
		}
		else if (equip.getEquippedWeap() == 5)
		{
			c.Y = 23;
		}
		else if (equip.getEquippedWeap() == 6)
		{
			c.Y = 24;
		}
		else if (equip.getEquippedWeap() == 7)
		{
			c.Y = 25;
		}
		else if (equip.getEquippedWeap() == 8)
		{
			c.Y = 26;
		}
		else if (equip.getEquippedWeap() == 9)
		{
			c.Y = 27;
		}
		else if (equip.getEquippedWeap() == 10)
		{
			c.Y = 28;
		}
		else if (equip.getEquippedWeap() == 11)
		{
			c.Y = 29;
		}
		else if (equip.getEquippedWeap() == 12)
		{
			c.Y = 30;
		}
		else if (equip.getEquippedWeap() == 13)
		{
			c.Y = 31;
		}
		else if (equip.getEquippedWeap() == 14)
		{
			c.Y = 32;
		}
		else if (equip.getEquippedWeap() == 15)
		{
			c.Y = 33;
		}
		g_Console.writeToBuffer(c, itemsArray[equip.getEquippedWeap()].getName(), 0xA3);
	}
	if ((equip.getArmorSlot() == true))
	{
		c.X = 18;
		if (equip.getEquippedArmor() == 0)
		{
			c.Y = 18;
		}
		else if (equip.getEquippedArmor() == 1)
		{
			c.Y = 19;
		}
		else if (equip.getEquippedArmor() == 2)
		{
			c.Y = 20;
		}
		else if (equip.getEquippedArmor() == 3)
		{
			c.Y = 21;
		}
		else if (equip.getEquippedArmor() == 4)
		{
			c.Y = 22;
		}
		else if (equip.getEquippedArmor() == 5)
		{
			c.Y = 23;
		}
		else if (equip.getEquippedArmor() == 6)
		{
			c.Y = 24;
		}
		else if (equip.getEquippedArmor() == 7)
		{
			c.Y = 25;
		}
		else if (equip.getEquippedArmor() == 8)
		{
			c.Y = 26;
		}
		else if (equip.getEquippedArmor() == 9)
		{
			c.Y = 27;
		}
		else if (equip.getEquippedArmor() == 10)
		{
			c.Y = 28;
		}
		else if (equip.getEquippedArmor() == 11)
		{
			c.Y = 29;
		}
		else if (equip.getEquippedArmor() == 12)
		{
			c.Y = 30;
		}
		else if (equip.getEquippedArmor() == 13)
		{
			c.Y = 31;
		}
		else if (equip.getEquippedArmor() == 14)
		{
			c.Y = 32;
		}
		else if (equip.getEquippedArmor() == 15)
		{
			c.Y = 33;
		}
		g_Console.writeToBuffer(c, itemsArray[equip.getEquippedArmor()].getName(), 0xA3);

	}
	if ((equip.getAccSlot() == true))
	{
		c.X = 18;
		if (equip.getEquippedAcc() == 0)
		{
			c.Y = 18;
		}
		else if (equip.getEquippedAcc() == 1)
		{
			c.Y = 19;
		}
		else if (equip.getEquippedAcc() == 2)
		{
			c.Y = 20;
		}
		else if (equip.getEquippedAcc() == 3)
		{
			c.Y = 21;
		}
		else if (equip.getEquippedAcc() == 4)
		{
			c.Y = 22;
		}
		else if (equip.getEquippedAcc() == 5)
		{
			c.Y = 23;
		}
		else if (equip.getEquippedAcc() == 6)
		{
			c.Y = 24;
		}
		else if (equip.getEquippedAcc() == 7)
		{
			c.Y = 25;
		}
		else if (equip.getEquippedAcc() == 8)
		{
			c.Y = 26;
		}
		else if (equip.getEquippedAcc() == 9)
		{
			c.Y = 27;
		}
		else if (equip.getEquippedAcc() == 10)
		{
			c.Y = 28;
		}
		else if (equip.getEquippedAcc() == 11)
		{
			c.Y = 29;
		}
		else if (equip.getEquippedAcc() == 12)
		{
			c.Y = 30;
		}
		else if (equip.getEquippedAcc() == 13)
		{
			c.Y = 31;
		}
		else if (equip.getEquippedAcc() == 14)
		{
			c.Y = 32;
		}
		else if (equip.getEquippedAcc() == 15)
		{
			c.Y = 33;
		}
		g_Console.writeToBuffer(c, itemsArray[equip.getEquippedAcc()].getName(), 0xA3);

	}
}
