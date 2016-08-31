#include "Equipment.h"

extern SMouseEvent g_mouseEvent;
extern double  g_dBounceTime;
extern double  g_dElapsedTime;

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

void Equipment::getEquippedStats(Items &items, PlayerStats &playerStats, Inventory &inventory, int itemArrayIndex)
{
	playerStats.updateStrEquip((inventory.getItemStr(itemArrayIndex)));
	playerStats.updateConEquip((inventory.getItemCon(itemArrayIndex)));
	playerStats.updateIntEquip((inventory.getItemInt(itemArrayIndex)));
	playerStats.updatePlayerAttack((inventory.getAttack(itemArrayIndex)));
	playerStats.updatePlayerHealth((inventory.getHealth(itemArrayIndex)));
	playerStats.updatePlayerHealthMaxHealth((inventory.getHealth(itemArrayIndex)));
}

void Equipment::removeEquipments(Items &items, PlayerStats &playerStats, Inventory &inventory, int prevEquipIndex)
{
	playerStats.updateStrEquip(-(inventory.getItemStr(prevEquipIndex)));
	playerStats.updateConEquip(-(inventory.getItemCon(prevEquipIndex)));
	playerStats.updateIntEquip(-(inventory.getItemInt(prevEquipIndex)));
	playerStats.updatePlayerAttack(-(inventory.getAttack(prevEquipIndex)));
	playerStats.updatePlayerHealth(-(inventory.getHealth(prevEquipIndex)));
	playerStats.updatePlayerHealthMaxHealth(-(inventory.getHealth(prevEquipIndex)));
}

void Equipment::wearEquipment(Items &items, PlayerStats &playerStats, Inventory &inventory)
{
	int itemArrayIndex = 30;
	bool mouseRelease = true;
	bool bSomethingHappened = false;

	if (mouseRelease)
	{
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 18 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 0;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 19 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 1;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 20 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 2;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 21 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 3;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 22 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 4;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 23 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 5;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 24 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 6;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 25 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 7;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 26 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 8;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 27 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 9;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 28 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 10;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 29 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 11;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 30 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 12;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 31 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 13;
		}
		else if (g_mouseEvent.mousePosition.X == 16 && g_mouseEvent.mousePosition.Y == 32 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			itemArrayIndex = 14;
		}
		bSomethingHappened = true;
	}
	if (inventory.getSize() >= itemArrayIndex)
	{
		if (checkWeaponEquip == false && ((inventory.getItemArrayWeaponSlot(itemArrayIndex)) == true ))
		{
			equipped_indexWeapon = itemArrayIndex;
			getEquippedStats(items, playerStats, inventory, itemArrayIndex);
			checkWeaponEquip = true;
		}

		else if (checkArmorEquip == false && ((inventory.getItemArrayArmorSlot(itemArrayIndex)) == true))
		{
			equipped_indexArmor = itemArrayIndex;
			getEquippedStats(items, playerStats, inventory, itemArrayIndex);
			checkArmorEquip = true;
		}

		else if (checkAccEquip == false && ((inventory.getItemArrayAccSlot(itemArrayIndex)) == true))
		{
			equipped_indexAcc = itemArrayIndex;
			getEquippedStats(items, playerStats, inventory, itemArrayIndex);
			checkAccEquip = true;
		}
		else if (checkWeaponEquip == true && ((inventory.getItemArrayWeaponSlot(itemArrayIndex)) == true))
		{
			removeEquipments(items, playerStats, inventory, equipped_indexWeapon);
			equipped_indexWeapon = 30;
			//getEquippedStats(items, playerStats, inventory, itemArrayIndex);
			checkWeaponEquip = false;
		}

		else if (checkArmorEquip == true && ((inventory.getItemArrayArmorSlot(itemArrayIndex)) == true))
		{
			removeEquipments(items, playerStats, inventory, equipped_indexArmor);
			equipped_indexArmor = 30;
			//getEquippedStats(items, playerStats, inventory, itemArrayIndex);
			checkArmorEquip = false;
		}

		else if (checkAccEquip == true && ((inventory.getItemArrayAccSlot(itemArrayIndex)) == true))
		{
			removeEquipments(items, playerStats, inventory, equipped_indexAcc);
			equipped_indexAcc = 30;
			//getEquippedStats(items, playerStats, inventory, itemArrayIndex);
			checkAccEquip = false;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}

}

void Equipment::resetDefault()
{
	equipped_indexAcc = 30;
	equipped_indexArmor = 30;
	equipped_indexWeapon = 30;
	checkAccEquip = false;
	checkArmorEquip = false;
	checkWeaponEquip = false;
}
void Equipment::setItemAtt(int Att)
{
	item_attackValue = Att;
}

void Equipment::setItemCon(int con)
{
	item_con_add = con;
}
void Equipment::setItemHP(int hp)
{
	item_healthValue = hp;
}
void Equipment::setItemInt(int Int)
{
	item_int_add = Int;
}
void Equipment::setItemStr(int str)
{
	item_str_add = str;
}

//below should add draw function for Equipped and Unequip