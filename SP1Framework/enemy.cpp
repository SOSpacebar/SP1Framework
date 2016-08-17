#include "enemyProperties.h"

enemyStruct _enemy;

void enemy(COORD pos, short speed, short health, short attack, bool alive )
{
	_enemy.e_location = pos;
	_enemy.e_speed = speed;
	_enemy.e_health = health;
	_enemy.e_attack = attack;
	_enemy.e_alive = true;
}