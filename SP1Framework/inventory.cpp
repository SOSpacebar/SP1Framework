#include "inventory.h"


Inventory::Inventory()
{
	inventorySize = 5;
	numberOfItems = 0;
	itemsArray = new Items*[inventorySize];
}


Inventory::~Inventory()
{
	for (size_t i = 0; i < numberOfItems; i++)
	{
		delete itemsArray[i];
	}

	delete itemsArray;
}


void Inventory::addItem(const Items &item)
{
	itemsArray[numberOfItems++] = new Items(item);
}

void Inventory::removeItem(int index)
{

}
