#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Framework\timer.h"
#include "game.h"
#include <iostream>
#include <string>

using namespace std;

struct objectStruct
{
	COORD o_location;
	string o_ID;
	short o_distance;
	bool reverse = false;
};

void init_object(short level);				//GameObject initialiser
void update_GameObject(void);

void updateLR_Projectile(COORD &xy, short &dist);					//Left to Right Projectile
void updateRL_Projectile(COORD &xy, short &dist);					//Right to Left Projectile
void updateUD_Projectile(COORD &xy, short &dist);					//Up to Down Projectile
void updateDU_Projectile(COORD &xy, short &dist);					//Down to Up Projectile
void updateDiagonal_LR_UD_Projectile(COORD &xy, short &dist);		//Diagonal Left to Right, from up to down Projectile
void updateDiagonal_LR_DU_Projectile(COORD &xy, short &dist);		//Diagonal Left to Right, from down to up Projectile
void updateDiagonal_RL_UD_Projectile(COORD &xy, short &dist);		//Diagonal Right to Left, from up to down Projectile
void updateDiagonal_RL_DU_Projectile(COORD &xy, short &dist);		//Diagonal Right to Left, from down to up Projectile

void updateCrusher(COORD &xy, short &dist);						//Right Left Crushing Block
//void TryCircle(void);											//"Circular" motion Projectile

#endif