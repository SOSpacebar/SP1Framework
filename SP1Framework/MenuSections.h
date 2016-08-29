#ifndef _MENUSECTIONS_H
#define _MENUSECTIONS_H

#include "Framework\console.h"
#include "game.h"
#include "DialogBox.h"
#include "gameObject.h"
#include "enemyProperties.h"
#include "playerStats.h"
#include "inventory.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern Console g_Console;
//using namespace std;

void renderMainMenu(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime);// Main Menu
void LevelSelect(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime);// Selecting Level
void SetAnimationSplashScreen(EGAMESTATES &g_eGameState); // Showing Animation
void DrawAnimationSplashScreen(EGAMESTATES &g_eGameState); // Draw the SplashScreen in
void GameOver(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime); // When Player got killed in the game
void Credits(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT]); // Crediting everyone who work for the game
void renderCombatScreen(EGAMESTATES &g_eGameState, double &g_dElapsedTime, bool g_abKeyPressed[K_COUNT], double &g_dBounceTime, PlayerStats &getPlayerStats, Inventory &inventory);

void setupLevel(short &Level, EGAMESTATES &g_eGameState, SGameChar &_sChar, DialogStruct boxArr[], int &maxBox, SGameKey &g_iKey, SGameKey &g_dDoor, objectStruct _object[], short &totalNumObject, bool &canPortalGun, enemyStruct _enemy[]);

void checkDialogEnd(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], int &boxIndex, Console &g_Console, bool dialogend, double &g_dBounceTime, double &g_dElapsedTime, bool &canPortalGun);

int generate_dmg();
int randomhp_dmg(int rand_dmg_timeOffset);

void GamePause(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime);

#endif