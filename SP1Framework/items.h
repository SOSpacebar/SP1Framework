#ifndef _ITEMS_H
#define _ITEMS_H

#include "game.h"


class Items
{
public:
	Items();
	~Items();

	inline string getName() const { return item_name; };
	inline string getType() const { return item_type; };
	inline int getReqLevel() const { return item_reqLevel; };
	inline int getReqStr() const { return item_reqStr; };
	inline int getReqCon() const { return item_reqCon; };
	inline int getAttackValue() const { return item_attackValue; };
	inline int getHealthValue() const { return item_healthValue; };

	void setItemDetails(string name, string type, int level, int str, int con, int attackV, int healthV); 
	void setName(string name);

private:
	string item_name;
	string item_type;
	int item_reqLevel;
	int item_reqStr;
	int item_reqCon;
	int item_attackValue;
	int item_healthValue;

	void RNGitem();
};


#endif