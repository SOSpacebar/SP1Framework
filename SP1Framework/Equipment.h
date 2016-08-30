#ifndef _EQUIPMENT_H
#define _EQUIPMENT_H

#include "inventory.h"

class Inventory;

class Equipment
{
public:
	Equipment();
	~Equipment();

	inline string getEquipName()  const { return equip_name; };
	inline int    getEquipStr()   const { return equip_str_add; };
	inline int    getEquipCon()   const { return equip_con_add; };
	inline int    getEquipInt()   const { return equip_int_add; };
	inline int    getEquipAttV()  const { return equip_attackValue; };
	inline int    getEquipHpV()   const { return equip_healthValue; };
	inline bool   getWeaponSlot() const { return checkWeaponEquip; };
	inline bool   getArmorSlot()  const { return checkArmorEquip; };
	inline bool   getAccSlot()    const { return checkAccEquip; };
	inline int    getEquippedWeap() const { return equipped_indexWeapon; };
	inline int    getEquippedArmor() const { return equipped_indexArmor; };
	inline int    getEquippedAcc() const { return equipped_indexAcc; };

	void getEquippedStats(Items &items, PlayerStats &playerStats, Inventory &inventory, int itemArrayIndex);
	void removeEquipments(Items &items, PlayerStats &playerStats, Inventory &inventory, int itemArrayIndex, int prevEquipIndex);
	void wearEquipment(Items &items, PlayerStats &playerStats, Inventory &inventory);
	void setItemStr(int str);
	void setItemCon(int con);
	void setItemInt(int Int);
	void setItemAtt(int Att);
	void setItemHP(int Hp);


private:
	string equip_name;
	int equip_str_add;
	int equip_con_add;
	int equip_int_add;
	int equip_attackValue;
	int equip_healthValue;
	int item_str_add;
	int item_con_add;
	int item_int_add;
	int item_attackValue;
	int item_healthValue;

	int equipped_indexWeapon = 30;
	int equipped_indexArmor = 30;
	int equipped_indexAcc = 30;

	bool checkWeaponEquip;
	bool checkArmorEquip;
	bool checkAccEquip;
};

#endif