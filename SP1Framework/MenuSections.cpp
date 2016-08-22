#include "MenuSections.h"
#include "ReadMap.h"
#include "AnimationManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int SplashCol = 0;
string AnimationString;
COORD l;
int hp = 98;
bool keyReleased = false;

int AnimationOffset = 0;
int AnimationOffset2 = 0;

int MenuSelect; // A interger to keep the of Start Game there 
int SetLevel;
extern double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

extern double  g_dElapsedTime;
extern double  g_dDeltaTime;
extern bool    g_abKeyPressed[K_COUNT];
extern int     g_currLevel;
extern SMapData g_mapData;
extern EGAMESTATES g_eGameState;


void renderMainMenu()
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

void LevelSelect()
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

void Credits()
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

void SetAnimationSplashScreen()
{
	if (SplashCol < 388)
	{
		for (int i = 0; i < 10; i++)
			AnimationString.push_back((char)219);
	}
	if (SplashCol > 388)
	{
		g_eGameState = S_MAINMENU;
	}
}

void DrawAnimationSplashScreen()
{
	SetAnimationSplashScreen();
	g_Console.writeToBuffer(l, AnimationString, 0x4B);
	SplashCol++;
}

void renderCombatScreen()
{
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
	}

	x.X = 46;
	x.Y = 4;

	if (AnimationOffset2 <= 45 && AnimationOffset2 >= 30)
	{
		drawAnimation(2, x);
		AnimationOffset2++;
	}
	else if (AnimationOffset2 > 45)
	{
		AnimationOffset2 = 0;
	}
	x.X = 10;
	x.Y = 25;
	drawHpCurr(3, x);
}

void setupLevel(int Level)
{
	clearScreen();
	memset(g_mapData.mapGrid, '\0', sizeof(g_mapData.mapGrid[0][0]) * 150 * 150);
	readMap(Level);
	g_eGameState = S_GAME;
}
