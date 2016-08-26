#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "items.h"

class Inventory
{
	public:
		Inventory();
		~Inventory();

		void addItem(const Items &item);
		void removeItem(int index);

	private:
		int inventorySize;
		int numberOfItems;
		Items **itemsArray;
};


#endif

