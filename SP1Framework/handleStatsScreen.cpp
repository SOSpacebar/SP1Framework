#include "handleStatsScreen.h"

void statsUserInterface(EGAMESTATES &g_eGameState, bool g_abKeyPressed[K_COUNT], double &g_dElapsedTime, double &g_dBounceTime)
{
	bool bSomethingHappened = false;

	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_STATS])
	{
		g_eGameState = S_GAME;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}