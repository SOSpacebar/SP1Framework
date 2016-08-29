#include "playerStats.h"

void PlayerStats::setPlayerStats(string name, int level, int exp, int maxExp, int health, int maxHealth, int attack, int s_str, int s_con, int s_int, int statPoint)
{
	player_name = name;
	player_level = level;
	player_experience = exp;
	player_nextLvlExperience = maxExp;
	player_health = health;
	player_maxHealth = maxHealth;
	player_attack = attack;
	player_strenght = s_str;
	player_constitution = s_con;
	player_intelligence = s_int;
	player_statPoints = statPoint;
}

void PlayerStats::updatePlayerhealth(int health, int maxHealth)
{
	player_health += health;
	player_maxHealth = maxHealth;
}

void PlayerStats::updateExp(int exp)
{
	player_experience += exp;

	if (player_experience > (player_level * 100))
	{
		levelUp();
	}
}

void PlayerStats::updateStr(int s_str)
{
	player_strenght += s_str;
}
void PlayerStats::updateCon(int s_con)
{
	player_constitution += s_con;
}
void PlayerStats::updateInt(int s_int)
{
	player_intelligence += s_int;
}

void PlayerStats::levelUp()
{
	player_level++;
	player_nextLvlExperience = player_level * 100;
	player_statPoints += 2;
}