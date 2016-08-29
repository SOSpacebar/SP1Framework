#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "items.h"
#include "Framework\console.h"


extern Console g_Console; //For testing

class Inventory
{
	public:
		Inventory();
		~Inventory();

		void addItem(const Items &item);
		void removeItem(int index);

		inline const void debugPrint() const
		{
			COORD c = g_Console.getConsoleSize();;
			c.X = c.X / 2 - 9;
			c.Y = c.Y / 3 + 12;

			for (int i = 0; i < numberOfItems; i++)
			{
				g_Console.writeToBuffer(c, "Name: " + itemsArray[i]-> getName(), 0x03);
				c.Y++;
				g_Console.writeToBuffer(c, "Type: " + itemsArray[i]->getType(), 0x03);
				c.Y++;
			}
		}

	private:
		int inventorySize;
		int numberOfItems;
		Items **itemsArray;
};


#endif

