#include "MenuSections.h"
#include "ReadMap.h"
#include "AnimationManager.h"
#include "gameObject.h"
#include "enemyProperties.h"


int SplashCol = 0;
string AnimationString;

COORD l; 

int hp = 98;
int playerHealth = 98;

int timeOffset = 0;
bool dmg_taken = false;
double mushroomBounceTime;
bool keyReleased = false;

int AnimationOffset = 0;
int AnimationOffset2 = 0;

int MenuSelect; // A interger to keep the of Start Game there 
int SetLevel;

extern short    g_currLevel;
extern SMapData g_mapData;
extern int i;
extern enemyStruct _enemy[20];

void renderMainMenu(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dDeltaTime, double &g_dElapsedTime, double &g_dBounceTime)
{
	bool bSomethingHappened = false;

	g_currLevel = 0;
	string Menu[3] = { "Start Game", "Credits", "Exit" };//Array of Start Game and Exit

	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 5;
	g_Console.writeToBuffer(c, "Main Menu", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;

	switch (MenuSelect)//Main Menu Selections
	{
	case 0:
		g_Console.writeToBuffer(c, Menu[0], 0x04);
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
			g_eGameState = S_LEVELSELECT;
			bSomethingHappened = true;
			MenuSelect = 1;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Menu[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x04);
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
			bSomethingHappened = true;
			g_eGameState = S_CREDITS;
		}
		break;
	case 2:
		g_Console.writeToBuffer(c, Menu[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[2], 0x04);
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
	bool bSomethingHappened = false;
	string Level[3] {"Level_1", "Level_2", "Level_3"};//creating a simple level selection.

	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 5;
	g_Console.writeToBuffer(c, "Level Selection", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;

	//By Pressing Escaped will Return back to main menu
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MAINMENU;
	}
	//Switching case of Level 1,2,3
	switch (SetLevel)
	{
	case 0:
		g_Console.writeToBuffer(c, Level[0], 0x04);
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
			bSomethingHappened = true;
			g_currLevel = 0;
			g_eGameState = S_LOADLEVEL;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Level[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[1], 0x04);
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
			bSomethingHappened = true;			
			g_currLevel = 6;
			g_eGameState = S_LOADLEVEL;

		}
		break;
	case 2:
		g_Console.writeToBuffer(c, Level[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Level[2], 0x04);
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
			bSomethingHappened = true;
			//g_currLevel = 2;
			g_eGameState = S_COMBATSCREEN;
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
	c.X = c.X / 2 - 5;
	g_Console.writeToBuffer(c, "ESC to Return", 0x02);
	c.Y += 4;
	g_Console.writeToBuffer(c, "Done By,", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Ng JingJie <>", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Lim Zhi Sheng <>", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Lim Pei Sheng", 0x02);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Lim Yi Chun <UI>", 0x02);
	c.Y += 1;

	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MAINMENU;
	}
}

void GameOver()
{

}

void SetAnimationSplashScreen(EGAMESTATES &g_eGameState)
{
	if (SplashCol < 388)
	{
		for (int i = 0; i < 10; i++)
			AnimationString.push_back((char)219);
	}
	if (SplashCol > 388)
	{
		g_eGameState = S_COMBATSCREEN;
	}
}

void DrawAnimationSplashScreen(EGAMESTATES &g_eGameState)
{
	SetAnimationSplashScreen(g_eGameState);
	g_Console.writeToBuffer(l, AnimationString, 0x4B);
	SplashCol++;
}

void renderCombatScreen(EGAMESTATES &g_eGameState, double &g_dElapsedTime, bool g_abKeyPressed[K_COUNT])
{
	timeOffset++;


	processUserInput();
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

	if (AnimationOffset <= 20 && AnimationOffset2 == 0)
	{
		drawAnimation(0, x);
	}
	else if (AnimationOffset > 20 && AnimationOffset2 == 0)
	{
		drawAnimation(1, x);
	}

	if (AnimationOffset >= 40)
	{
		AnimationOffset = 0;
	}

	AnimationOffset++;

	x.X = 10;
	x.Y = 25;

	drawAnimation(3, x);

	x.X = 10;
	x.Y = 32;
	drawAnimation(6, x);
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		keyReleased = false;
	}
	else
	{
		keyReleased = true;
	}

	if (g_abKeyPressed[K_SPACE] && keyReleased)
	{
		hp -= 2;
		AnimationOffset2 = 30;
		if (hp <= 16)
		{
			playerHealth += 20;
			g_eGameState = S_LOADLEVEL;
		}
	}
	
	if (((randomhp_dmg(21) > 65 && randomhp_dmg(21) < 70) && generate_dmg() == 1) && g_dElapsedTime > mushroomBounceTime)
	{
		if (hp != 98)
		{
			mushroomBounceTime = g_dElapsedTime + 0.125;
			playerHealth--;
		}
	}

	x.X = 46;
	x.Y = 4;

	if (AnimationOffset2 <= 45 && AnimationOffset2 >= 30)
	{
		drawAnimation(2, x);
		damagePopUp(5, x);
		AnimationOffset2++;
	}
	else if (AnimationOffset2 > 45)
	{
		AnimationOffset2 = 0;
	}
	x.X = 10;
	x.Y = 25;
	drawHpCurr(3, x);

	x.X = 10;
	x.Y = 32;
	drawPlayerHP(6, x);
}
void setupLevel(short Level, EGAMESTATES &g_eGameState, SGameChar &_sChar)
{
	clearScreen();
	memset(g_mapData.mapGrid, '\0', sizeof(g_mapData.mapGrid[0][0]) * 150 * 150);
	readMap(Level, _sChar);
	init_object(1);
	init_enemy(6, _enemy, i);
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
