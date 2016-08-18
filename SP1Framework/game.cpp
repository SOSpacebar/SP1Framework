// This is the main file for the game logic and function
//
//
#include "game.h"
#include "AnimationManager.h"
#include "Framework\console.h"
#include "collisionManager.h"
#include "enemyProperties.h"
#include "ReadMap.h"
#include <iostream>
#include <sstream>
#include <iomanip>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

int abc = 0;

int MenuSelect = 0; // A interger to keep the of Start Game there 
int SetLevel = 0;

// Game specific variables here
extern SMapData g_mapData;
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(120, 40, "INSERT GAME NAME HERE");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

	readAnimation();

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

	g_sChar.m_cLocation.X = 5;// g_Console.getConsoleSize().X / 2;
	g_sChar.m_cLocation.Y = 5;// g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

	init_enemy(1);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_MainMenu : renderMainMenu();
			break;
		case S_LevelSelect: LevelSelect();
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
		case S_MainMenu: renderMainMenu();
			break;
		case S_LevelSelect: LevelSelect();
			break;
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 1.0) // wait for 1 seconds to switch to game mode, else do nothing
        g_eGameState = S_MainMenu;
}

void renderMainMenu()
{
	bool bSomethingHappened = false;
	string Menu[2] = { "Start Game", "Exit" };//Array of Start Game and Exit

	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 5;
	g_Console.writeToBuffer(c, "Main Menu", 0x02);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;
	//From Pressing Up will make the user go to the Start Game
	if (g_abKeyPressed[K_UP])
	{
		bSomethingHappened = true;
		MenuSelect = 0;
	}
	//From Pressing Down Player will go to the Exit Menu
	else if (g_abKeyPressed[K_DOWN])
	{
		bSomethingHappened = true;
		MenuSelect = 1;
	}
	switch (MenuSelect)
	{
	case 0:
		g_Console.writeToBuffer(c, Menu[0], 0x04);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x03);
		if (g_dBounceTime > g_dElapsedTime)
			return;
		//Press Space in Start Menu will go to start game
		if (g_abKeyPressed[K_ENTER])
		{
			g_eGameState = S_LevelSelect;
			bSomethingHappened = true;
			MenuSelect = 1;
		}
		break;
	case 1:
		g_Console.writeToBuffer(c, Menu[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x04);
		if (g_dBounceTime > g_dElapsedTime)
			return;
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

	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MainMenu;
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
			g_eGameState = S_GAME;
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
			g_eGameState = S_GAME;
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
			g_eGameState = S_GAME;
		}
		break;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
   // sound can be played here too.

}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		if (checkCollision(g_sChar, g_mapData, K_UP) == true)
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		if (checkCollision(g_sChar, g_mapData, K_LEFT) == true)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (checkCollision(g_sChar, g_mapData, K_DOWN) == true)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (checkCollision(g_sChar, g_mapData, K_RIGHT) == true)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}

	}
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in a seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
	readMap(1);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	//updateProjectile();

	if (abc <= 5)
	{
		drawAnimation(0);
	}
	else if (abc > 5)
	{
		drawAnimation(1);
	}
	if (abc >= 10)
	{
		abc = 0;
	}

	abc++;

	updateProjectile();
	SpikeBall();

	updateProjectile(); 
	WALKLA();

	updateProjectile();
	SpikeBall();
}

void renderMap()
{

    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
	std::string MapDataString;

    for (int i = 0; i < 150; ++i)
    {
		c.X = 0;
        c.Y = i + 1;
		MapDataString = g_mapData.mapGrid[i];

		if (MapDataString.size() == 0)
		{
			break;
		}
		if (MapDataString[i] != '\0')
		{
			g_Console.writeToBuffer(c, MapDataString, colors[3]);
		}
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderCombatScreen()
{
	COORD x;

}
