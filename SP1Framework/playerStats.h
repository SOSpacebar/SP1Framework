#ifndef _PLAYERSTATS_H
#define _PLAYERSTATS_H

#include "game.h"
#include "inventory.h"

class PlayerStats
{
public:
	inline const string getPlayerName() const { return player_name; };
	inline const int getPlayerLevel() const { return player_level; };
	inline const int getPlayerExp() const { return player_experience; };
	inline const int getPlayerNextLvlExp() const { return player_nextLvlExperience; };
	inline const int getPlayerHealth() const { return player_health; };
	inline const int getPlayerMaxHealth() const { return player_maxHealth; };
	inline const int getPlayerAttack() const { return player_attack; };
	inline const int getPlayerStr() const { return player_strenght; };
	inline const int getPlayerCon() const { return player_constitution; };
	inline const int getPlayerInt() const { return player_intelligence; }
	inline const int getPlayerStatPoints() const { return player_experience; };


	int updatePlayerhealth(int health, int maxHealth);
	void setPlayerStats(string name, int level, int exp, int maxExp, int health, int maxHealth, int attack, int s_str, int s_con, int s_int, int statPoint);
	void updateExp(int exp);
	void updateStr(int s_str);
	void updateInt(int s_int);
	void updateCon(int s_con);
	void levelUp();

private:
	string player_name;
	int player_level;
	int player_experience;
	int player_nextLvlExperience;
	int player_health;
	int player_maxHealth;
	int player_attack;
	int player_strenght;
	int player_constitution;
	int player_intelligence;
	int player_statPoints;
};







#endif 