#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "HeaderIncludes.h"
#include "portalGun.h"
using namespace std;

void init_object(short level);				//GameObject initialiser
void update_GameObject(SMapData g_mapData, SGameChar g_sChar, Portal _portal);				//GameObject Indivisual function call

void updateLR_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Left to Right Projectile
void updateRL_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Right to Left Projectile
void updateUD_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Up to Down Projectile
void updateDU_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData g_mapData, SGameChar g_sChar, Portal _portal);					//Down to Up Projectile

void updateLR_EBall(string &ID, COORD &xy, int &speed, bool &reverse, SMapData g_mapData, SGameChar g_sChar, Portal _portal);						//Right Left Crushing Block
void updateUD_EBall(string &ID, COORD &xy, int &speed, bool &reverse, SMapData g_mapData, SGameChar g_sChar, Portal _portal);
void findCoordStart(int x, int y);
int randomArr(int rand_vec_size);

#endif