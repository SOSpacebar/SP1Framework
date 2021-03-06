#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

#include <string>
#include <fstream>
#include "game.h"
#include "Framework\console.h"
#include "playerStats.h"

struct FrameData
{
	char frameToLoad[50][150][150];

	int height;

	int width;

	float frameTime;
};

void readAnimation(void);
void drawAnimation(int keyFrame, COORD animationCoord, Console &g_Console);
void drawHpCurr(int keyFrame, COORD currCoord, int &hp, Console &g_Console);
void drawDialogBox(int keyFrame, COORD boxCoord, Console &g_Console);
void damagePopUp(int keyFrame, COORD Pop, Console &g_Console);
void drawTitle(int keyFrame, COORD T_Coord, Console &g_Console);
void drawUI(Console &g_Console);
void drawEXP(Console &g_Console, PlayerStats getPlayerStats);
void drawHP(Console &g_Console, PlayerStats getPlayerStats);
void drawTextUI(Console &g_Console, PlayerStats playerStats);
void drawCombatMenu(Console &g_Console);
void drawQuickHelp(Console &g_Console, short g_currLevel);

#endif