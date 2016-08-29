#include "handleStatsScreen.h"

void statsUserInterface(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dElapsedTime, double &g_dBounceTime, PlayerStats &getPlayerStats, Inventory &_inventory, SMouseEvent g_mouseEvent)
{
	bool bSomethingHappened = false;

	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_STATS])
	{
		g_eGameState = S_GAME;
		bSomethingHappened = true;
	}

	if (getPlayerStats.getPlayerStatPoints() > 0)
	{
		if (g_mouseEvent.mousePosition.X == 61 && g_mouseEvent.mousePosition.Y == 10 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			getPlayerStats.updateStr();
			bSomethingHappened = true;
		}
		if (g_mouseEvent.mousePosition.X == 65 && g_mouseEvent.mousePosition.Y == 11 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			getPlayerStats.updateCon();
			bSomethingHappened = true;
		}
		if (g_mouseEvent.mousePosition.X == 65 && g_mouseEvent.mousePosition.Y == 12 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			getPlayerStats.updateInt();
			bSomethingHappened = true;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}