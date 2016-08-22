#include "Framework\console.h"
#include "game.h"


extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern Console g_Console;
//using namespace std;

void renderMainMenu();// Main Menu
void LevelSelect();// Selecting Level
void SetAnimationSplashScreen(); // Showing Animation
void DrawAnimationSplashScreen(); // Draw the SplashScreen in
void GameOver(); // When Player got killed in the game
void Credits(); // Crediting everyone who work for the game
void renderCombatScreen();
void setupLevel(short Level);