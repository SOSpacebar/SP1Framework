#include "MenuSections.h"
#include "AnimationManager.h"
#include "enemyProperties.h"
#include <random>
#include <Windows.h>
#include "MMSystem.h"
#include "ReadMap.h"

int SplashCol = 0;
string AnimationString;

COORD l; 

int hp = 98;
int playerHealth = 98;

int timeOffset = 0;
int timeOffset_2 = 0;

bool dmg_taken = false;
double mushroomBounceTime;
bool keyReleased = true;
bool combatMenuReleased = true;

int AnimationOffset = 0;
int AnimationOffset2 = 0;

int MenuSelect; // A interger to keep the of Start Game there 
int SetLevel;

extern short    g_currLevel;
extern SMapData g_mapData;
extern int i;
extern enemyStruct _enemy[20];
extern short combatIndex;

int all_Monster;

void renderMainMenu(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime)
{
	int time = g_dElapsedTime;

	COORD title;
	title.X = 0;
	title.Y = 5;
//============================= Game Title ============================
	if (time % 4 == 0)							//function to be called multiple times in a second to create animated corrupting effect
	{
		if (randomTitle() == 1)
		{
			drawTitle(30, title, g_Console);
		}
		else
		{
			drawTitle(31, title, g_Console);
		}
	}
	else if (time % 5 == 0)
	{
		if (randomTitle() == 1)
		{
			drawTitle(32, title, g_Console);
		}
		else
		{
			drawTitle(33, title, g_Console);
		}
	}
	else
	{
		drawTitle(9, title, g_Console);
	}
//======================================================================
	bool bSomethingHappened = false;
	
	g_currLevel = 0;
	string Menu[3] = { "Start Game", "Credits", "Exit Game" };//Array of Start Game and Exit
	string Menu_selected[3] = { "> Start Game <", "> Credits <", "> Exit Game <" };

	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 5;
	c.Y += 4;
	c.X = g_Console.getConsoleSize().X / 2 - 8;

	switch (MenuSelect)//Main Menu Selections
	{
	case 0:
		g_Console.writeToBuffer(c, Menu_selected[0], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[2], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;

		if (g_abKeyPressed[K_UP])//Pressing up will not change anything in the main menu
		{
			bSomethingHappened = true;
			MenuSelect = 0;
		}
		//From Pressing Down Player will go to the Exit Menu
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			MenuSelect = 1;
		}

		if (g_abKeyPressed[K_ENTER])//By Pressing Enter will got to LevelSelection State
		{
			MenuSelect = 0;
			bSomethingHappened = true;
			g_eGameState = S_LEVELSELECT;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Menu[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu_selected[1], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[2], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			MenuSelect = 0;
		}
		//From Pressing Down Player will go to the Exit Menu
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			MenuSelect = 2;
		}
		if (g_abKeyPressed[K_ENTER])
		{
			PlaySound(TEXT("Sound/Prologue.wav"), NULL, SND_LOOP | SND_ASYNC);
			bSomethingHappened = true;
			MenuSelect = 0;
			g_eGameState = S_CREDITS;
		}
		break;
	case 2:
		g_Console.writeToBuffer(c, Menu[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu_selected[2], 0x04);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			MenuSelect = 1;
		}
		//From Pressing Down Player will go to the Exit Menu
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			MenuSelect = 2;
		}
		//Press Space in Exit Menu will quit the game
		if (g_abKeyPressed[K_ENTER])
		{
			bSomethingHappened = true;
			MenuSelect = 0;
			g_bQuitGame = true;
		}
		break;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void LevelSelect(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime)
{
	int time = g_dElapsedTime;

	COORD title;
	title.X = 0;
	title.Y = 5;
	//============================= Game Title ============================
	if (time % 4 == 0)							//function to be called multiple times in a second to create animated corrupting effect
	{
		if (randomTitle() == 1)
		{
			drawTitle(30, title, g_Console);
		}
		else
		{
			drawTitle(31, title, g_Console);
		}
	}
	else if (time % 5 == 0)
	{
		if (randomTitle() == 1)
		{
			drawTitle(32, title, g_Console);
		}
		else
		{
			drawTitle(33, title, g_Console);
		}
	}
	else
	{
		drawTitle(9, title, g_Console);
	}
	//======================================================================


	bool bSomethingHappened = false;
	string Level[3] {"Tutorial", "Challenge", "Random Generate"}; //creating a simple level selection.
	string Level_selected[3] {"> Tutorial <", "> Challenge <", "> Random Generate <"};

	COORD c = g_Console.getConsoleSize();
	c.Y = c.Y /2 - 3;
	c.X = c.X / 2 - 8;
	g_Console.writeToBuffer(c, "Level Selection", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;

	//By Pressing Escaped will Return back to main menu
	if (g_abKeyPressed[K_ESCAPE])
	{
		PlaySound(TEXT("Sound/Detective.wav"), NULL, SND_LOOP | SND_ASYNC);
		g_eGameState = S_MAINMENU;
	}
	//Switching case of Level 1,2,3
	switch (SetLevel)
	{
	case 0:
		g_Console.writeToBuffer(c, Level_selected[0], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[2], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		//Going up will not move change
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			SetLevel = 0;
		}
		//Pressing Down will move to 1st case
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			SetLevel = 1;
		}
		//Pressing ENTER will go into the game
		if (g_abKeyPressed[K_ENTER])
		{
			PlaySound(TEXT("Sound/Searching.wav"), NULL, SND_LOOP | SND_ASYNC);
			bSomethingHappened = true;
			SetLevel = 0;
			g_currLevel = 0;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Level[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level_selected[1], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[2], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		//Pressing up will move back to case 0
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			SetLevel = 0;
		}
		//Pressing Down will move to 2nd case
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			SetLevel = 2;
		}
		if (g_abKeyPressed[K_ENTER])
		{
			PlaySound(TEXT("Sound/Searching.wav"), NULL, SND_LOOP | SND_ASYNC);
			bSomethingHappened = true;
			SetLevel = 0;
			g_currLevel = 3;
			g_eGameState = S_LOADLEVEL;

		}
		break;
	case 2:
		g_Console.writeToBuffer(c, Level[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level_selected[2], 0x04);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		//Goes back to case 1
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			SetLevel = 1;
		}
		//Remain at case 2
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			SetLevel = 2;
		}
		if (g_abKeyPressed[K_ENTER])
		{
			PlaySound(TEXT("Sound/Searching.wav"), NULL, SND_LOOP | SND_ASYNC);
			bSomethingHappened = true;
			SetLevel = 0;
			g_currLevel = 4;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void Credits(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT])
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 8;
	g_Console.writeToBuffer(c, "ESC to Return", 0x04);
	c.Y += 3;
	c.X += 3;
	g_Console.writeToBuffer(c, "Done By,", 0x02);
	c.Y += 1;
	c.X -= 3;
	g_Console.writeToBuffer(c, "Ng JingJie", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Lim Zi Sheng", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Lim Pei Sheng", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Lim Yi Chun", 0x02);
	c.Y += 4;
	g_Console.writeToBuffer(c, "Special Thanks -", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Mr Sim <Framework>", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Mr Chris Hong", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Eric Skiff <Music>", 0x02);
	c.Y += 1;

	if (g_abKeyPressed[K_ESCAPE])
	{
		PlaySound(TEXT("Sound/Detective.wav"), NULL, SND_LOOP | SND_ASYNC);
		g_eGameState = S_MAINMENU;
	}
}

void GamePause(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime)
{
	bool bSomethingHappened = false;
	string MenuSelection[3] {"Resume","MainMenu","Exit Game"};//creating a simple level selection.
	string MenuSelection_selected[3] {"> Resume <", "> MainMenu <", "> Exit Game <"};

	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 5;
	g_Console.writeToBuffer(c, "PAUSE", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;

	switch (SetLevel)
	{
	case 0:
		g_Console.writeToBuffer(c, MenuSelection_selected[0], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, MenuSelection[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, MenuSelection[2], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			SetLevel = 0;
		}

		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			SetLevel = 1;
		}
		//Pressing ENTER will go into the game
		if (g_abKeyPressed[K_ENTER])
		{
			bSomethingHappened = true;
			SetLevel = 0;
			g_eGameState = S_GAME;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, MenuSelection[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, MenuSelection_selected[1], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, MenuSelection[2], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		//Pressing up will move back to case 0
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			SetLevel = 0;
		}
		//Pressing Down will move to 2nd case
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			SetLevel = 2;
		}
		if (g_abKeyPressed[K_ENTER])
		{
			PlaySound(TEXT("Sound/Detective.wav"), NULL, SND_LOOP | SND_ASYNC);
			bSomethingHappened = true;
			SetLevel = 0;
			g_eGameState = S_MAINMENU;
		}
		break;
	case 2:
		g_Console.writeToBuffer(c, MenuSelection[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, MenuSelection[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, MenuSelection_selected[2], 0x04);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (g_abKeyPressed[K_UP])
		{
			bSomethingHappened = true;
			SetLevel = 1;
		}
		//From Pressing Down Player will go to the Exit Menu
		if (g_abKeyPressed[K_DOWN])
		{
			bSomethingHappened = true;
			SetLevel = 2;
		}
		//Press Space in Exit Menu will quit the game
		if (g_abKeyPressed[K_ENTER])
		{
			bSomethingHappened = true;
			SetLevel = 0;
			g_bQuitGame = true;
		}
		break;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void GameOver(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime)
{
	int time = g_dElapsedTime;

	COORD G_over;
	G_over.X = 0;
	G_over.Y = 5;

	if (time % 4 == 0)
	{
		if (randomTitle() == 1)
		{
			drawTitle(34, G_over, g_Console);
		}
		else
		{
			drawTitle(35, G_over, g_Console);
		}
	}
	else
	{
		drawTitle(10, G_over, g_Console);
	}

	bool bSomethingHappened = false;
	string MenuSelection[1] {"> MainMenu <"};//creating a simple level selection.

	COORD c = g_Console.getConsoleSize();
	c.Y = c.Y/2 - 3;
	c.X = c.X / 2 - 8;
	g_Console.writeToBuffer(c, "GAMEOVER", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;

	switch (SetLevel)
	{
	case 0:
		g_Console.writeToBuffer(c, MenuSelection[0], 0x04);
		c.Y += 1;
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (g_abKeyPressed[K_ENTER])
		{
			PlaySound(TEXT("Sound/Detective.wav"), NULL, SND_LOOP | SND_ASYNC);
			bSomethingHappened = true;
			SetLevel = 0;
			g_eGameState = S_MAINMENU;
		}
		break;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void DrawAnimationSplashScreen(EGAMESTATES &g_eGameState)
{
	SetAnimationSplashScreen(g_eGameState);
	g_Console.writeToBuffer(l, AnimationString, 0x4B);
	SplashCol++;
}

void SetAnimationSplashScreen(EGAMESTATES &g_eGameState)
{
	//Randomize Enemy and decide who you will fight
	all_Monster = rand() % 3 + 1;
	//Printing Splash Coloring on the whole screen
	if (SplashCol < 196)
	{
		for (int i = 0; i < 30; i++)
			AnimationString.push_back((char)219);
	}
	if (SplashCol > 196)
	{
		PlaySound(TEXT("Sound/Defense.wav"), NULL, SND_LOOP | SND_ASYNC);
		SplashCol = 0;
		AnimationString = "";
		g_eGameState = S_COMBATSCREEN;
	}
}

void renderCombatScreen(EGAMESTATES &g_eGameState, double &g_dElapsedTime, bool g_abKeyPressed[K_COUNT], double &g_dBounceTime, PlayerStats &getPlayerStats, Inventory &inventory)
{
	timeOffset++;
	bool bSomethingHappened = false;
	//processUserInput();
	//set screen black
	string fillScreen;

	for (; fillScreen.size() < 4800;)
	{
		fillScreen.push_back(' ');
	}

	g_Console.writeToBuffer(0, 0, fillScreen, 0x0D);

	COORD x;
	x.X = 42;
	x.Y = 5;

	//types of enemy
	int orangeMush = 1;
	int hornMush = 2; 
	int Slime = 3;

	//add function to check which mushroom to spawn
	drawCombatMenu(g_Console);
	if (all_Monster == orangeMush){
		if (AnimationOffset <= 20 && AnimationOffset2 == 0)
		{
			drawAnimation(0, x, g_Console);
		}
		else if (AnimationOffset > 20 && AnimationOffset2 == 0)
		{
			drawAnimation(1, x, g_Console);
		}
	}
	//Appearance of HornMushroom
	else if (all_Monster == hornMush)
	{
		if (AnimationOffset <= 20 && AnimationOffset2 == 0)
		{
			drawAnimation(24, x, g_Console);
		}
		else if (AnimationOffset > 20 && AnimationOffset2 == 0)
		{
			drawAnimation(25, x, g_Console);
		}
	}
	//Appearance of Slime
	else if (all_Monster == Slime)
	{
		if (AnimationOffset <= 20 && AnimationOffset2 == 0)
		{
			drawAnimation(27, x, g_Console);
		}
		else if (AnimationOffset > 20 && AnimationOffset2 == 0)
		{
			drawAnimation(28, x, g_Console);
		}
	}

	if (GetAsyncKeyState(VK_DOWN) < 0)
	{
		if (combatMenuReleased)
		{
			if (combatIndex == 0)
			{
				combatIndex = 1;
			}
			else if (combatIndex == 2)
			{
				combatIndex = 3;
			}
			else if (combatIndex == 4)
			{
				combatIndex = 5;
			}
		}

		combatMenuReleased = false;
	}
	else
	{
		combatMenuReleased = true;
	}

	if (GetAsyncKeyState(VK_UP) < 0)
	{
		if (combatMenuReleased)
		{
			if (combatIndex == 1)
			{
				combatIndex = 0;
			}
			else if (combatIndex == 3)
			{
				combatIndex = 2;
			}
			else if (combatIndex == 5)
			{
				combatIndex = 4;
			}
		}
		combatMenuReleased = false;
	}
	else
	{
		combatMenuReleased = true;
	}

	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		if (g_dBounceTime < g_dElapsedTime)
		{
			if (combatMenuReleased)
			{
				combatMenuReleased = false;
				if (combatIndex == 0)
				{
					combatIndex = 2;
					keyReleased = false;
					bSomethingHappened = true;
				}
				else if (combatIndex == 1)
				{
					combatIndex = 4;
					keyReleased = false;
					bSomethingHappened = true;
				}
				if (keyReleased)
				{
					if (combatIndex == 2)
					{
						hp -= getPlayerStats.getPlayerAttack();
						AnimationOffset2 = 30;
						combatIndex = 0;
						bSomethingHappened = true;
					}
					else if (combatIndex == 3)
					{
						hp -= getPlayerStats.getPlayerAttack() + 5;
						AnimationOffset2 = 30;
						combatIndex = 0;
						bSomethingHappened = true;
					}
					else if (combatIndex == 4)
					{
						if ((getPlayerStats.getPlayerMana() - 20) >= 0)
						{
							hp -= 20 + (getPlayerStats.getPlayerInt() * (float)0.5);
							getPlayerStats.updatePlayermana(-20);
							AnimationOffset2 = 30;
						}
						combatIndex = 0;
						bSomethingHappened = true;
					}
					else if (combatIndex == 5)
					{
						if ((getPlayerStats.getPlayerMana() - 20) >= 0)
						{
							hp -= 20 + (getPlayerStats.getPlayerInt() * (float)0.5);
							getPlayerStats.updatePlayermana(-20);
							AnimationOffset2 = 30;
						}
						combatIndex = 0;
						bSomethingHappened = true;
					}
					if (hp <= 0)
					{
						inventory.addItem(Items());
						getPlayerStats.updateExp(10);
						PlaySound(TEXT("Sound/Searching.wav"), NULL, SND_LOOP | SND_ASYNC);
						hp = 98;
						g_eGameState = S_GAME;
						getPlayerStats.updatePlayerhealth(20);
						if (getPlayerStats.getPlayerHealth() > getPlayerStats.getPlayerMaxHealth())
						{
							getPlayerStats.updatePlayerhealth(-(getPlayerStats.getPlayerHealth() - getPlayerStats.getPlayerMaxHealth()));
						}
					}
				}
			}
		}
	}
	else
	{
		keyReleased = true;
		combatMenuReleased = true;
	}

	if (GetAsyncKeyState(VK_ESCAPE) < 0)
	{
		if (combatMenuReleased)
		{
			if (combatIndex == 2 || combatIndex == 3)
			{
				combatIndex = 0;
			}
			else if (combatIndex == 4 || combatIndex == 5)
			{
				combatIndex = 1;
			}
		}
		combatMenuReleased = false;
	}
	else
	{
		combatMenuReleased = true;
	}

	AnimationOffset++;

	x.X = 41;
	x.Y = 24;

	drawAnimation(3, x, g_Console);

	if (playerHealth <= 10)
	{
		PlaySound(TEXT("Sound/GameOver.wav"), NULL, SND_LOOP | SND_ASYNC);
		g_eGameState = S_GAMEOVER;
		playerHealth = 98;
		hp = 98;
	}
	x.X = 46;
	x.Y = 4;

	if (all_Monster == orangeMush)
	{
		if (AnimationOffset2 <= 45 && AnimationOffset2 >= 30)
		{
			drawAnimation(2, x, g_Console);
			damagePopUp(5, x, g_Console);
			AnimationOffset2++;
		}
		else if (AnimationOffset2 > 45)
		{
			AnimationOffset2 = 0;
		}
	}
	else if (all_Monster == hornMush)
	{
		if (AnimationOffset2 <= 45 && AnimationOffset2 >= 30)
		{
			drawAnimation(26, x, g_Console);
			damagePopUp(5, x, g_Console);
			AnimationOffset2++;
		}
		else if (AnimationOffset2 > 45)
		{
			AnimationOffset2 = 0;
		}
	}
	else if (all_Monster == Slime)
	{
		if (AnimationOffset2 <= 45 && AnimationOffset2 >= 30)
		{
			drawAnimation(29, x, g_Console);
			damagePopUp(5, x, g_Console);
			AnimationOffset2++;
		}	
		else if (AnimationOffset2 > 45)
		{
			AnimationOffset2 = 0;
		}
	}

	x.X = 41;
	x.Y = 24;
	drawHpCurr(3, x, hp, g_Console);
	g_Console.writeToBuffer(x.X = 41, x.Y = 23, "Monster HP -", 0x0D);

	drawUI(g_Console);
	drawHP(g_Console, getPlayerStats);
	drawEXP(g_Console, getPlayerStats);
	drawTextUI(g_Console, getPlayerStats);
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.325; // 125ms should be enough
	}
}

void setupLevel(short &Level, EGAMESTATES &g_eGameState, SGameChar &_sChar, DialogStruct boxArr[], int &maxBox, SGameKey &g_iKey, SGameKey &g_dDoor, objectStruct _object[], short &totalNumObject, bool &canPortalGun, enemyStruct _enemy[])

{
	
	clearScreen();
	memset(g_mapData.mapGrid, '\0', sizeof(g_mapData.mapGrid[0][0]) * 150 * 150);
	readMap(Level, _sChar, boxArr, maxBox, g_iKey, g_dDoor, _object, totalNumObject, _enemy);
	init_object(Level, totalNumObject);
	init_enemy(Level, _enemy, i);

	if (Level > 1)
	{
		canPortalGun = true;
	}
	g_eGameState = S_GAME;
}

int generate_dmg()
{
	std::random_device randtrue;
	std::mt19937 twistNew(randtrue());

	std::uniform_int_distribution<> dmgtaken(0, 2 - 1);
	return (dmgtaken(twistNew));
}

int randomhp_dmg(int rand_dmg_timeOffset)
{
	std::random_device randDMG;
	std::mt19937 twistNew(randDMG());

	std::uniform_int_distribution<> dmg(0, 21 - 1);
	return (dmg(twistNew)+50);
}

int randomTitle()
{
	std::random_device randtitle;
	std::mt19937 twistNew(randtitle());

	std::uniform_int_distribution<> title_style(0, 2 - 1);
	return (title_style(twistNew));
}

void checkDialogEnd(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], int &boxIndex, Console &g_Console, bool dialogend, double &g_dBounceTime, double &g_dElapsedTime, bool &canPortalGun)
{
	COORD boxStart;
	boxStart.X = 0;
	boxStart.Y = 15;

	renderGame();
	drawDialogBox((boxIndex + 10), boxStart, g_Console);
	dialogend = false;

	if (g_abKeyPressed[K_SPACE])
	{
		g_dBounceTime = g_dElapsedTime + 0.225;
		dialogend = true;
		if ((canPortalGun == false) && (boxIndex > 1))
		{
			canPortalGun = true;
		}
		g_eGameState = S_GAME;
	}
}