#ifndef  _EQUIPHANDLER_H
#define _EQUIPHANDLER_H

#include "game.h"
#include "items.h"
#include "playerStats.h"
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

	void getEquippedStats(Items items, PlayerStats playerStats);
	void removeEquipments(Items items, PlayerStats playerStats);

private:
	string equip_name;
	int equip_str_add;
	int equip_con_add;
	int equip_int_add;
	int equip_attackValue;
	int equip_healthValue;
	bool checkWeaponEquip;
	bool checkArmorEquip;
	bool checkAccEquip;
};
#endif //  _EQUIPHANDLER_H;