#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Framework\timer.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

struct objectStruct
{
	COORD o_location;
	string o_ID;
	int o_speed;
	bool o_reset;
};

void init_object(short level);				//GameObject initialiser
void update_GameObject(void);				//GameObject Indivisual function call

void updateLR_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Left to Right Projectile
void updateRL_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Right to Left Projectile
void updateUD_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Up to Down Projectile
void updateDU_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Down to Up Projectile

void updateLR_EBall(string &ID, COORD &xy, int &speed, bool &reverse, SMapData g_mapData, SGameChar g_sChar, Portal _portal);						//Right Left Crushing Block
void updateUD_EBall(string &ID, COORD &xy, int &speed, bool &reverse, SMapData g_mapData, SGameChar g_sChar, Portal _portal);
void findCoordStart(int x, int y);
int randomArr(int rand_vec_size);

#endif