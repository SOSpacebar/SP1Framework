#include "Framework\console.h"
#include "game.h"


extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern Console g_Console;
//using namespace std;

void renderMainMenu(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime);// Main Menu
void LevelSelect(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime);// Selecting Level
void SetAnimationSplashScreen(EGAMESTATES &g_eGameState); // Showing Animation
void DrawAnimationSplashScreen(EGAMESTATES &g_eGameState); // Draw the SplashScreen in
void GameOver(); // When Player got killed in the game

void Credits(); // Crediting everyone who work for the game
void renderCombatScreen();
void setupLevel(short Level);
int generate_dmg();
int randomhp_dmg(int rand_dmg_timeOffset);

void Credits(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT]); // Crediting everyone who work for the game
void renderCombatScreen(EGAMESTATES &g_eGameState, double &g_dElapsedTime, bool g_abKeyPressed[K_COUNT]);
void setupLevel(short Level, EGAMESTATES &g_eGameState);

int generate_dmg();
int randomhp_dmg(int rand_dmg_timeOffset);

