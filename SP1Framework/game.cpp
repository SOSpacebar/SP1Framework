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
//SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

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

//inventory
Inventory _inventory;

//equip
Equipment equip;

//items
Items itemsArray[15];

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
	
	PlaySound(TEXT("Sound/Detective.wav"), NULL, SND_LOOP | SND_ASYNC);

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

    // remember to set your keyboard handler, so that your functions can be notified of input events
   // g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

	//Load Player Stats
	loadFile(_playerStats);
	_inventory.addItem(Items());
	_inventory.addItem(Items());
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
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
//void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
//{    
//    switch (g_eGameState)
//    {
//    case S_SPLASHSCREEN: // don't handle anything for the splash screen
//        break;
//    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
//        break;
//    }
//}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
	case S_STATSSCREEN: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
		break;
    }
}

void getInput(void)
{

	g_Console.readConsoleInput();
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_SWITCH] = isKeyPressed(0x53);
	g_abKeyPressed[K_STATS] = isKeyPressed(0x41);
	g_abKeyPressed[K_Z] = isKeyPressed(0x5A);
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
//void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
//{
//    // here, we map the key to our enums
//    EKEYS key = K_COUNT;
//    switch (keyboardEvent.wVirtualKeyCode)
//    {
//    case VK_UP: key = K_UP; break;
//    case VK_DOWN: key = K_DOWN; break;
//    case VK_LEFT: key = K_LEFT; break; 
//    case VK_RIGHT: key = K_RIGHT; break; 
//    case VK_SPACE: key = K_SPACE; break;
//    case VK_ESCAPE: key = K_ESCAPE; break; 
//    }
//    // a key pressed event would be one with bKeyDown == true
//    // a key released event would be one with bKeyDown == false
//    // if no key is pressed, no event would be fired.
//    // so we are tracking if a key is either pressed, or released
//    if (key != K_COUNT)
//    {
//        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
//        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
//    }    
//}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
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
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
		case S_STATSSCREEN: statsUserInterface(g_eGameState, g_abKeyPressed, g_dElapsedTime, g_dBounceTime, _playerStats, _inventory, g_mouseEvent);
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
		case S_COMBATSCREEN: renderCombatScreen(g_eGameState, g_dElapsedTime, g_abKeyPressed, g_dBounceTime, _playerStats, _inventory);
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
		case S_STATSSCREEN: renderPlayerStatsScreen(g_Console, _playerStats, _inventory, equip);
			//renderInputEvents();
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
}

void splashScreenWait()    // waits for time to pass in splash screen
{

	if (g_dElapsedTime > 1.5) // wait for 1 seconds to switch to game mode, else do nothing
		g_eGameState = S_MAINMENU;
}

void updateGame()       // gameplay logic
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
    //if (g_skKeyEvent[K_ESCAPE].keyReleased)
    //    g_bQuitGame = true;    
	//if (g_abKeyPressed[K_ESCAPE])
	//{
	//	saveFile(_playerStats);
	//	g_bQuitGame = true;
	//}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
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
	drawEXP(g_Console, _playerStats);
	drawHP(g_Console, _playerStats);
	drawTextUI(g_Console, _playerStats);
//	renderInputEvents();
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

 //this is an example of how you would use the input events
void renderInputEvents()
{
    std::ostringstream ss;

    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;        
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:        
        break;
    }
    
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
	maxBox = 0;
	boxIndex = 0;
}
