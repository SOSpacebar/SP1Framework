#include "DialogBox.h"
#include "AnimationManager.h"

extern bool statsOpened;


void checkDialogBox(DialogStruct boxArr[], SGameChar &_sChar, int &maxBox, int &boxIndex, Console &g_Console, EGAMESTATES &g_eGameState)
{
	bool warning = false;
	for (int x = 0; x < maxBox; x++)
	{
		if ((boxArr[x].Location.X == _sChar.m_cLocation.X) && (boxArr[x].Location.Y == _sChar.m_cLocation.Y))
		{
			if ((boxIndex == 4) && (statsOpened == false) && (warning == false))
			{
				warning = true;
				_sChar.m_cLocation.X = 14;
				_sChar.m_cLocation.Y = 13;
				g_eGameState = S_DIALOG;
				break;
			}
 			boxArr[x].Location.X = 0;
			boxArr[x].Location.Y = 0;
			dialogCollision(boxIndex, g_Console, maxBox, g_eGameState);
		}
	}
}

void dialogCollision(int &boxIndex, Console &g_Console, int &maxBox, EGAMESTATES &g_eGameState)
{
	if ((boxIndex == 4) && (statsOpened == false))
	{
		g_eGameState = S_DIALOG;
		return;
	}
 	boxIndex++;
	g_eGameState = S_DIALOG;
}