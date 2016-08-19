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
};

void init_object(short level);				//GameObject initialiser
void update_GameObject(void);

void updateLR_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);					//Left to Right Projectile
void updateRL_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);					//Right to Left Projectile
void updateUD_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);					//Up to Down Projectile
void updateDU_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);					//Down to Up Projectile
void updateDiagonal_LR_UD_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);		//Diagonal Left to Right, from up to down Projectile
void updateDiagonal_LR_DU_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);		//Diagonal Left to Right, from down to up Projectile
void updateDiagonal_RL_UD_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);		//Diagonal Right to Left, from up to down Projectile
void updateDiagonal_RL_DU_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset);		//Diagonal Right to Left, from down to up Projectile

void updateCrusher(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reverse);						//Right Left Crushing Block

//void TryCircle(void);											//"Circular" motion Projectile

#endif