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

		inline void debugPrint() const
		{
			COORD c = g_Console.getConsoleSize();;
			c.X = c.X / 2 - 9;
			c.Y = c.Y / 3 + 9;

			for (size_t i = 0; i < numberOfItems; i++)
			{
				g_Console.writeToBuffer(c,  itemsArray[i] -> debugPrint() , 0x03);
				c.Y++;
			}
		}

	private:
		int inventorySize;
		int numberOfItems;
		Items **itemsArray;
};


#endif

