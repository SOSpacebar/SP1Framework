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
#include "MenuSections.h"
#include "lockandUnlock.h"
#include "MapGenerator.h"
#include "fieldOfView.h"
#include "DialogBox.h"
//Mk 2
#include "playerStats.h"
#include "renderPlayerStatsScreen.h"
#include "handleStatsScreen.h"
#include "playerDetailsManager.h"
//Original framework stuff
#include <iostream>
#include <sstream>
#include <iomanip>


double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

extern int playerHealth;

//Shooting Variables
bool bulletType = 0;
Bullet _bullet;
EKEYS lastDirection = K_RIGHT;

//Key and Door calling 
SGameKey g_iKey;
SGameKey g_dDoor;

//Portal Variables
Portal _portal;

//dialog box
DialogStruct boxArr[20];
int maxBox = 0;
int boxIndex = 0;

//Monster Variables
enemyStruct _enemy[20];

bool dialogend = true;
bool canPortalGun = false;

// Game specific variables here
extern SMapData g_mapData;
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
char fogMap[150][150];

extern int i;

short totalNumObject = 0;
short g_currLevel = 0;

// Console object
Console g_Console(120, 49, "- UNDEFINED -");

extern objectStruct _object[25];

//MK 2
PlayerStats _playerStats;

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
	

	g_sChar.m_cLocation.X = 5;
	g_sChar.m_cLocation.Y = 5;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Arial");

	// reset portal back to inActive
	memset(fogMap, ' ', sizeof(fogMap[0][0]) * 150 * 150);

	//Load Player Stats
	loadFile(_playerStats);
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
	g_abKeyPressed[K_STATS] = isKeyPressed(0x41);
	g_abKeyPressed[K_Z] = isKeyPressed(0x5A);
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
		case S_MAINMENU: renderMainMenu(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
		case S_CREDITS: Credits(g_eGameState, g_abKeyPressed);
			break;
		case S_LEVELSELECT: LevelSelect(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
		case S_GAMEOVER: GameOver(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
		case S_PAUSE: GamePause(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_STATSSCREEN: statsUserInterface(g_eGameState, g_abKeyPressed, g_dElapsedTime, g_dBounceTime);
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
		case S_MAINMENU: resetVariables();
			renderMainMenu(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
		case S_CREDITS: Credits(g_eGameState, g_abKeyPressed);
			break;
		case S_LEVELSELECT: LevelSelect(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
		case S_COMBATSCREEN: renderCombatScreen(g_eGameState, g_dElapsedTime, g_abKeyPressed, g_dBounceTime);
			break;
		case S_GAMEOVER: GameOver(g_eGameState ,g_abKeyPressed ,g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			boxIndex = 0;
			resetVariables();
			break;
        case S_GAME: renderGame();
            break;
		case S_LOADLEVEL: resetVariables(); 
			setupLevel(g_currLevel, g_eGameState, g_sChar, boxArr, maxBox, g_iKey, g_dDoor, _object, totalNumObject, canPortalGun, _enemy);
			break;
		case S_PAUSE: GamePause(g_eGameState, g_abKeyPressed, g_dDeltaTime, g_dElapsedTime, g_dBounceTime);
			break;
		case S_TRANSITION: DrawAnimationSplashScreen(g_eGameState);
			break;
		case S_STATSSCREEN: renderPlayerStatsScreen(g_Console, _playerStats);
			break;
		case S_DIALOG: 
			if (g_currLevel > 3)
			{
				g_eGameState = S_GAME;
			}
			else
			{
				checkDialogEnd(g_eGameState, g_abKeyPressed, boxIndex, g_Console, dialogend, g_dBounceTime, g_dElapsedTime, canPortalGun);

			}
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	initalizeSound(g_eGameState);
}

void splashScreenWait()    // waits for time to pass in splash screen
{

	if (g_dElapsedTime > 1.5) // wait for 1 seconds to switch to game mode, else do nothing
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

	checkDoorCollision(g_sChar, g_mapData, g_iKey, g_dDoor);

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		if (!g_abKeyPressed[K_Z])
		{
			if (checkPlayerCollision(g_sChar, g_mapData, K_UP, g_eGameState, g_currLevel, g_iKey, g_dDoor, i, _enemy) == true)
			{
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				checkPlayerCollisionWithPortal(g_sChar, _portal);
			}
		}
		lastDirection = K_UP;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		if (!g_abKeyPressed[K_Z])
		{
			if (checkPlayerCollision(g_sChar, g_mapData, K_LEFT, g_eGameState, g_currLevel, g_iKey, g_dDoor, i, _enemy) == true)
			{
				//Beep(1440, 30);
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				checkPlayerCollisionWithPortal(g_sChar, _portal);
			}
		}
		lastDirection = K_LEFT;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (!g_abKeyPressed[K_Z])
		{
			if (checkPlayerCollision(g_sChar, g_mapData, K_DOWN, g_eGameState, g_currLevel, g_iKey, g_dDoor, i, _enemy) == true)
			{
				//Beep(1440, 30);
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				checkPlayerCollisionWithPortal(g_sChar, _portal);
			}
		}
		bSomethingHappened = true;
		lastDirection = K_DOWN;
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (!g_abKeyPressed[K_Z])
		{
			if (checkPlayerCollision(g_sChar, g_mapData, K_RIGHT, g_eGameState, g_currLevel, g_iKey, g_dDoor, i, _enemy) == true)
			{
				//Beep(1440, 30);
				g_sChar.m_cLocation.X++;
				checkPlayerCollisionWithPortal(g_sChar, _portal);
			}
		}
		bSomethingHappened = true;
		lastDirection = K_RIGHT;
	}

    if ((g_abKeyPressed[K_SPACE]) && (canPortalGun))
    {
		if (g_dBounceTime > g_dElapsedTime)
			return;
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
		bSomethingHappened = true;

		if (g_sChar.m_bActive == 0)
		{
			_playerStats.setPlayerStats(5, 100, 120, 120, 10, 10, 10);
			g_sChar.m_bActive = 1;
			bulletType = 0;
		}
		else
		{
			g_sChar.m_bActive = 0;
			bulletType = 1;
		}
	}


	if (g_abKeyPressed[K_STATS])
	{
		bSomethingHappened = true;

		g_eGameState = S_STATSSCREEN;
	}

	if (g_eGameState == S_GAME && g_abKeyPressed[K_ENTER])
	{
		bSomethingHappened = true;
		g_eGameState = S_PAUSE;
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
	{
		saveFile(_playerStats);
		g_bQuitGame = true;
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c;
	c.X = 5;
	c.Y = 12;
	drawAnimation(8, c, g_Console);

}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
	RenderKey(g_iKey, _portal, g_sChar);
	LockedDoor(g_dDoor, g_iKey, _portal, g_sChar);
	renderPortal(_portal, g_Console); //renders portal.
    renderCharacter();  // renders the character into the buffer

	checkDialogBox(boxArr, g_sChar, maxBox, boxIndex, g_Console, g_eGameState); //render dialog

	if (_bullet.b_isActive == true)
		handleBulletProjectile(_bullet, g_dElapsedTime, g_Console, g_mapData, _portal); //renders the bullet.

	if (dialogend)
	{
		enemyMovememt(_enemy, g_Console, g_dElapsedTime, g_sChar, g_mapData, g_eGameState, _portal);
		update_GameObject(g_mapData, g_sChar, _enemy, _portal, g_eGameState, totalNumObject);
	}

	drawUI(g_Console);
	drawEXP(g_Console);
	drawHP(g_Console);
	drawTextUI(g_Console);
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

	renderFogOfWarAndMap(g_mapData, g_sChar, g_Console, fogMap, _bullet, _portal);
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

void resetVariables()
{
	COORD C;
	C.X = 0;
	C.Y = 0;
	_portal.p_pos[0] = C;
	_portal.p_pos[1] = C;
	_portal.p_isActive[0] = false;
	_portal.p_isActive[1] = false;
	memset(fogMap, ' ', sizeof(fogMap[0][0]) * 150 * 150);
	g_iKey.m_bActive = true;
	totalNumObject = 0;
	i = 0;
	playerHealth = 98;
}

