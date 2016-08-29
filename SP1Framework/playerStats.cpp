#include "playerStats.h"

/*int PlayerStats::getPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con)
{
	level = player_level;
	exp = player_experience;
	health = player_health;
	maxHealth = player_maxHealth;
	attack = player_attack;
	str = player_strenght;
	con = player_constitution;

	return (level, exp, health, maxHealth, attack, str, con);
}*/

void PlayerStats::setPlayerStats(int level, int exp, int health, int maxHealth, int attack, int str, int con)
{
	player_level = level;
	player_experience = exp;
	player_health = health;
	player_maxHealth = maxHealth;
	player_attack = attack;
	player_strenght = str;
	player_constitution = con;
}

/*void PlayerStats::updatePlayerhealth(int health, int maxHealth)
{
	player_health = health;
	player_maxHealth = maxHealth;
}*/

void PlayerStats::updateExp(int exp)
{
	player_experience = exp;

	if (player_experience > (player_level * 100))
	{
		levelUp();
	}
}

void PlayerStats::updateStr(int str)
{
	player_strenght += str;
}
void PlayerStats::updateCon(int con)
{
	player_constitution += con;
}

void PlayerStats::levelUp()
{
	player_level++;
}