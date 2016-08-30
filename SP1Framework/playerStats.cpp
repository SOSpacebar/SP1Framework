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

void PlayerStats::updatePlayerhealth(int health)
{
	player_health += health;
}

void PlayerStats::updatePlayermana(int mana)
{
	player_mana += mana;
}

void PlayerStats::updatePlayerAttack(int attack)
{
	player_attack += attack;
}
void PlayerStats::updatePlayerHealth(int health)
{
	player_health += health;
}

void PlayerStats::updateExp(int exp)
{
	player_experience += exp;

	if (player_experience >= (player_nextLvlExperience))
	{
		levelUp();
	}
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