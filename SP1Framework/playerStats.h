#ifndef _PLAYERSTATS_H
#define _PLAYERSTATS_H

#include "game.h"

class PlayerStats
{
public:
	//int getPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con);
	int getPlayerLevel(){ return player_level; };
	int getPlayerExp(){ return player_experience; };
	int getPlayerHealth(){ return player_health; };
	int getPlayerMaxHealth(){ return player_maxHealth; };
	int getPlayerAttack(){ return player_attack; };
	int getPlayerStr(){ return player_strenght; };
	int getPlayerCon(){ return player_constitution; };


	int updatePlayerhealth(int health, int maxHealth);
	void setPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con);
	int getExp(){ return player_experience; };
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