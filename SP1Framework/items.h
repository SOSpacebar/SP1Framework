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
	inline int getStr() const { return item_str; };
	inline int getCon() const { return item_con; };
	inline int getInt() const { return item_int; };
	inline int getAttackValue() const { return item_attackValue; };
	inline int getHealthValue() const { return item_healthValue; };

	void setItemDetails(string name, string type, int level, int str, int con, int attackV, int healthV); 
	void setName(string name);

private:
	string item_name;
	string item_type;
	int item_reqLevel;
	int item_str;
	int item_con;
	int item_int;
	int item_attackValue;
	int item_healthValue;

	void RNGitem();
};


#endif