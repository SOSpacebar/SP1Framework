#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "HeaderIncludes.h"
#include "portalGun.h"
using namespace std;

void createObjectString(short &totalNumObject);
void init_object(short level, short &totalNumObject);				//GameObject initialiser
void update_GameObject(SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState, short &totalNumObject);				//GameObject Indivisual function call

void updateLR_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState);					//Left to Right Projectile
void updateRL_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState);					//Right to Left Projectile
void updateUD_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState);					//Up to Down Projectile
void updateDU_Projectile(string &ID, COORD &xy, int &speed, bool &reset, SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState);					//Down to Up Projectile

void updateLR_EBall(string &ID, COORD &xy, int &speed, bool &reverse, SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState);						//Right Left Crushing Block
void updateUD_EBall(string &ID, COORD &xy, int &speed, bool &reverse, SMapData &g_mapData, SGameChar &g_sChar, Portal &_portal, EGAMESTATES &g_eGameState);
void findCoordStart(int x, int y, short &totalNumObject);
int randomArr(int rand_vec_size);

#endif