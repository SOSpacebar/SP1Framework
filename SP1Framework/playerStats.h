#ifndef _PLAYERSTATS_H
#define _PLAYERSTATS_H

#include "game.h"
#include "inventory.h"

class PlayerStats
{
public:
	//int getPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con);
	inline const int getPlayerLevel() const { return player_level; };
	inline const int getPlayerExp() const { return player_experience; };
	inline const int getPlayerHealth() const { return player_health; };
	inline const int getPlayerMaxHealth() const { return player_maxHealth; };
	inline const int getPlayerAttack() const { return player_attack; };
	inline const int getPlayerStr() const { return player_strenght; };
	inline const int getPlayerCon() const { return player_constitution; };
	inline const int getExp() const { return player_experience; };


	int updatePlayerhealth(int health, int maxHealth);
	void setPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con);
	void updateExp(int exp);
	void updateStr(int str);
	void updateCon(int con);
	void levelUp();

private:
	int player_level;
	int player_experience;
	int player_health;
	int player_maxHealth;
	int player_attack;
	int player_strenght;
	int player_constitution;
};







#endif 