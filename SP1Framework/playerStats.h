#ifndef _PLAYERSTATS_H
#define _PLAYERSTATS_H

#include "game.h"

class PlayerStats
{
public:
	//int getPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con);
	inline int getPlayerLevel(){ return player_level; };
	inline int getPlayerExp(){ return player_experience; };
	inline int getPlayerHealth(){ return player_health; };
	inline int getPlayerMaxHealth(){ return player_maxHealth; };
	inline int getPlayerAttack(){ return player_attack; };
	inline int getPlayerStr(){ return player_strenght; };
	inline int getPlayerCon(){ return player_constitution; };


	int updatePlayerhealth(int health, int maxHealth);
	void setPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con);
	inline int getExp(){ return player_experience; };
	void updateExp(int exp);
	void updateStr(int str);
	void updateCon(int con);

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