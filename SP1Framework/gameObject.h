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
	vector <int> o_speed;
	int o_distance;
	bool o_reset;
	int o_shift;
};

void init_object(short level);				//GameObject initialiser
void update_GameObject(void);

void updateLR_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count);					//Left to Right Projectile
void updateRL_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count);					//Right to Left Projectile
void updateUD_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count);					//Up to Down Projectile
void updateDU_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count);					//Down to Up Projectile

void updateLR_EBall(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reverse, int &count);						//Right Left Crushing Block
void updateUD_EBall(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reverse, int &count);

//void TryCircle(void);											//"Circular" motion Projectile

#endif