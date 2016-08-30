#ifndef _PLAYERSTATS_H
#define _PLAYERSTATS_H

#include "game.h"

class PlayerStats
{
public:
	inline string getPlayerName() const { return player_name; };
	inline int getPlayerLevel() const { return player_level; };
	inline int getPlayerExp() const { return player_experience; };
	inline int getPlayerNextLvlExp() const { return player_nextLvlExperience; };
	inline int getPlayerHealth() const { return player_health; };
	inline int getPlayerMaxHealth() const { return player_maxHealth; };
	inline int getPlayerMana() const { return player_mana; };
	inline int getPlayerMaxMana() const { return player_maxMana; };
	inline int getPlayerAttack() const { return player_attack; };
	inline int getPlayerStr() const { return player_strenght; };
	inline int getPlayerCon() const { return player_constitution; };
	inline int getPlayerInt() const { return player_intelligence; }
	inline int getPlayerStatPoints() const { return player_statPoints; };

	void updatePlayerHealth(int health);
	void updatePlayerMana(int mana);
	void updatePlayerAttack(int attack);
	void setPlayerStats(string name, int level, int exp, int maxExp, int health, int maxHealth, int mana, int maxMana, int attack, int s_str, int s_con, int s_int, int statPoint);
	void updateExp(int exp);
	void updateStr();
	void updateInt();
	void updateCon();
	void levelUp();
	void updateStrEquip(int Str);
	void updateConEquip(int Con);
	void updateIntEquip(int Int);
private:
	string player_name;
	int player_level;
	int player_experience;
	int player_nextLvlExperience;
	int player_health;
	int player_maxHealth;
	int player_mana;
	int player_maxMana;
	int player_attack;
	int player_strenght;
	int player_constitution;
	int player_intelligence;
	int player_statPoints;
};
#endif 