#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

#include <string>
#include <fstream>
#include "game.h"

struct FrameData
{
	char frameToLoad[50][150][150];

	int height;

	int width;

	float frameTime;
};

void readAnimation(void);
void drawAnimation(int keyFrame, COORD animationCoord);
void drawHpCurr(int keyFrame, COORD currCoord);
void drawDialogBox(int keyFrame, COORD boxCoord);
void damagePopUp(int keyFrame, COORD Pop);
void drawPlayerHP(int keyFrame, COORD playerCoord);

#endif