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
				c.X = 18;
				g_Console.writeToBuffer(c, itemsArray[i]-> getName(), 0x03);
				c.X += 23 ;
				g_Console.writeToBuffer(c, itemsArray[i]-> getType(), 0x03);
				c.X += 10;
				g_Console.writeToBuffer(c, std::to_string(itemsArray[i]->getReqLevel()), 0x03);
				c.X += 10;
				g_Console.writeToBuffer(c, std::to_string(itemsArray[i]->getAttackValue()), 0x03);
				c.X += 10;
				g_Console.writeToBuffer(c, std::to_string(itemsArray[i]->getHealthValue()), 0x03);
				c.X += 7;
				g_Console.writeToBuffer(c, std::to_string(itemsArray[i]->getStr()), 0x03);
				c.X += 7;
				g_Console.writeToBuffer(c, std::to_string(itemsArray[i]->getCon()), 0x03);
				c.X += 7;
				g_Console.writeToBuffer(c, std::to_string(itemsArray[i]->getInt()), 0x03);
				c.Y++;
			}
		}

	private:
		int inventorySize;
		int numberOfItems;
		Items **itemsArray;
};


#endif

