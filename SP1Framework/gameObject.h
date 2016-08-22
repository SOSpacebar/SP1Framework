#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Framework\timer.h"
#include "ReadMap.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct objectStruct
{
	COORD o_start_location;
	COORD o_location;
	string o_ID;
	int o_speed;
	int o_distance;
	bool o_reset;
};

void init_object(short level);				//GameObject initialiser
void update_GameObject(void);				//GameObject Indivisual function call

void updateLR_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, int &speed, bool &reset);					//Left to Right Projectile
void updateRL_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, int &speed, bool &reset);					//Right to Left Projectile
void updateUD_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, int &speed, bool &reset);					//Up to Down Projectile
void updateDU_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, int &speed, bool &reset);					//Down to Up Projectile

void updateLR_EBall(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reverse);						//Right Left Crushing Block
void updateUD_EBall(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reverse);
void findCoordStart(int x, int y);

#endif