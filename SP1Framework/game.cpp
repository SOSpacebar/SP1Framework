// This is the main file for the game logic and function
//
//
#include "game.h"
#include "AnimationManager.h"
#include "Framework\console.h"
#include "collisionManager.h"
#include "enemyProperties.h"
#include "gameObject.h"
#include "portalGun.h"
#include "ReadMap.h"
#include "lockandUnlock.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "MenuSections.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];


//Shooting Variables
bool bulletType = 0;
Bullet _bullet;
EKEYS lastDirection = K_RIGHT;

//Key and Door calling 
extern SGameKey g_iKey;
extern SGameKey g_dDoor;

//Portal Variables
Portal _portal;

bool dialogend = false;

// Game specific variables here
extern SMapData g_mapData;
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

int g_currLevel = 0;

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

	g_iKey.m_bActive = true;
	g_dDoor.m_bActive = true;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

	g_sChar.m_cLocation.X = 5;// g_Console.getConsoleSize().X / 2;
	g_sChar.m_cLocation.Y = 5;// g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Arial");

	init_enemy(1);
	init_object(1);
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
	g_abKeyPressed[K_SWITCH] = isKeyPressed(0x53);
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
		case S_MAINMENU: renderMainMenu();
			break;
		case S_CREDITS: Credits();
			break;
		case S_LEVELSELECT: LevelSelect();
			break;
		case S_GAMEOVER: GameOver();
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
		case S_MAINMENU: renderMainMenu();
			break;
		case S_CREDITS: Credits();
			break;
		case S_LEVELSELECT: LevelSelect();
			break;
		case S_COMBATSCREEN: renderCombatScreen();
			break;
		case S_GAMEOVER: GameOver();
			break;
        case S_GAME: renderGame();
            break;
		case S_LOADLEVEL: setupLevel(g_currLevel);
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 1.0) // wait for 1 seconds to switch to game mode, else do nothing
		g_eGameState = S_MAINMENU;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit

	if (dialogend)
	{
		moveCharacter();    // moves the character, collision detection, physics, etc
	}
   
   // sound can be played here too.

}

void moveCharacter()
{
	bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

	checkDoorCollision(g_sChar, g_mapData);

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		if (checkPlayerCollision(g_sChar, g_mapData, K_UP) == true)
		{
			lastDirection = K_UP;
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
			checkPlayerCollisionWithPortal(g_sChar, _portal);
		}
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		if (checkPlayerCollision(g_sChar, g_mapData, K_LEFT) == true)
		{
			//Beep(1440, 30);
			lastDirection = K_LEFT;
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
			checkPlayerCollisionWithPortal(g_sChar, _portal);
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (checkPlayerCollision(g_sChar, g_mapData, K_DOWN) == true)
		{
			//Beep(1440, 30);
			lastDirection = K_DOWN;
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
			checkPlayerCollisionWithPortal(g_sChar, _portal);
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (checkPlayerCollision(g_sChar, g_mapData, K_RIGHT) == true)
		{
			//Beep(1440, 30);
			lastDirection = K_RIGHT;
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
			checkPlayerCollisionWithPortal(g_sChar, _portal);
		}
	}

    if (g_abKeyPressed[K_SPACE])
    {
		if (fireGun(g_sChar, g_mapData, K_SPACE, lastDirection, _bullet, bulletType) == true && _bullet.b_isActive == true)
		{
			bSomethingHappened = true;
		}
		if (g_sChar.m_bActive == 0)
		{
			g_sChar.m_bActive = 1;
			bulletType = 0;
		}
		else
		{
			g_sChar.m_bActive = 0;
			bulletType = 1;
		}
    }

	if (g_abKeyPressed[K_SWITCH])
	{
		//g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;

		if (g_sChar.m_bActive == 0)
		{
			g_sChar.m_bActive = 1;
			bulletType = 0;
		}
		else
		{
			g_sChar.m_bActive = 0;
			bulletType = 1;
		}
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
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
	RenderKey();
	LockedDoor();
	renderPortal(_portal, g_Console); //renders portal.
    renderCharacter();  // renders the character into the buffer
	
	if (_bullet.b_isActive == true)
		handleBulletProjectile(_bullet, g_dElapsedTime, g_Console, g_mapData, _portal); //renders the bullet.

	if (dialogend)
	{
		//WALKLA();

		//renderCombatScreen();
		//update_GameObject();
	}
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;

	c.X = 0;
	c.Y = 1;
	int tempValue = c.X;

    for (int row = 0; row < 150; row++)
    {
		for (int col = 0; col < 150; col++)
		{
			if ((g_mapData.mapGrid[row][col] == '\0') || (g_mapData.mapGrid[row][col] == '\n'))
			{
				break;
			}

			if ((g_mapData.mapGrid[row][col] == (char)187) || (g_mapData.mapGrid[row][col] == (char)188) || (g_mapData.mapGrid[row][col] == (char)200) || (g_mapData.mapGrid[row][col] == (char)201))
			{
				g_Console.writeToBuffer(c, g_mapData.mapGrid[row][col], 0x0A);
			}
			else
			{
				g_Console.writeToBuffer(c, g_mapData.mapGrid[row][col], 0x0D);
			}
			

			c.X++;
		}
		c.X = tempValue;
		c.Y ++;		
    }

	if (dialogend == false)
	{
		drawDialogBox(4, c);
		
		if (g_abKeyPressed[K_SPACE])
		{
			g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
			dialogend = true;
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

