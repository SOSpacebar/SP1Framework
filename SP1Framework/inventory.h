#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "items.h"
#include "Framework\console.h"
#include "playerStats.h"
#include "Equipment.h"

extern Console g_Console; //For testing
extern PlayerStats _playerStats;

class Equipment;

class Inventory
{
	public:
		Inventory();
		~Inventory();

		inline int getSize() const { return numberOfItems; };

		void addItem(const Items &item);
		void removeItem(int index);

		bool getItemArrayWeaponSlot(int arrayIndex);
		bool getItemArrayArmorSlot(int arrayIndex);
		bool getItemArrayAccSlot(int arrayIndex);
		int getItemStr(int arrayIndex);
		int getItemCon(int arrayIndex);
		int getItemInt(int arrayIndex);
		int getAttack(int arrayIndex);
		int getHealth(int arrayIndex);

		void setNumberOfItems(int num);

		void debugPrint(Equipment &equip, Inventory &_inventory);

	private:
		int inventorySize;
		int numberOfItems;
	//	Items **itemsArray;
};

#endif