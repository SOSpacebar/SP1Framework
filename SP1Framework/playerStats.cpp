#include "playerStats.h"

void PlayerStats::setPlayerStats(string name, int level, int exp, int maxExp, int health, int maxHealth, int mana, int maxMana, int attack, int s_str, int s_con, int s_int, int statPoint)
{
	player_name = name;
	player_level = level;
	player_experience = exp;
	player_nextLvlExperience = maxExp;
	player_health = health;
	player_maxHealth = maxHealth;
	player_mana = mana;
	player_maxMana = maxMana;
	player_attack = attack;
	player_strenght = s_str;
	player_constitution = s_con;
	player_intelligence = s_int;
	player_statPoints = statPoint;
}

void PlayerStats::updatePlayerHealth(int health)
{
	player_health += health;
}

void PlayerStats::updatePlayerHealthMaxHealth(int health)
{
	player_maxHealth += health;
}

void PlayerStats::updatePlayerMana(int mana)
{
	player_mana += mana;
}

void PlayerStats::updatePlayerAttack(int attack)
{
	player_attack += attack;
}

void PlayerStats::updateExp(int exp)
{
	player_experience += exp;

	if (player_experience >= (player_nextLvlExperience))
	{
		levelUp();
	}
}

void PlayerStats::updateStrEquip(int value)
{
	player_strenght += value;
}

void PlayerStats::updateConEquip(int value)
{
	player_constitution += value;
}

void PlayerStats::updateIntEquip(int value)
{
	player_intelligence += value;
}

void PlayerStats::updateStr()
{
	player_strenght++;
	player_statPoints--; 
	player_attack += 2;
}
void PlayerStats::updateCon()
{
	player_constitution++;
	player_statPoints--;
	player_maxHealth += 5;
}
void PlayerStats::updateInt()
{
	player_intelligence++;
	player_statPoints--;
	player_maxMana += 5;
}

void PlayerStats::levelUp()
{
	player_level++;
	player_nextLvlExperience = player_level * 100;
	player_statPoints += 2;
	player_experience = 0;
	player_health = player_maxHealth;
	player_mana = player_maxMana;
}

void PlayerStats::resetStats()
{
	player_level = 1;
	player_experience = 0;
	player_nextLvlExperience = 100;
	player_health = 100;
	player_maxHealth = 100;
	player_mana = 100;
	player_maxMana = 100;
	player_attack = 10;
	player_strenght = 5;
	player_constitution = 5;
	player_intelligence = 5;
	player_statPoints = 2;
}