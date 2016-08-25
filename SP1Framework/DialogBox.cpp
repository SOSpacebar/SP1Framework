#include "DialogBox.h"
#include "AnimationManager.h"

void checkDialogBox(DialogStruct boxArr[], SGameChar _sChar, int &maxBox, int &boxIndex, Console &g_Console, EGAMESTATES &g_eGameState)
{
	for (int x = 0; x < maxBox; x++)
	{
		if ((boxArr[x].Location.X == _sChar.m_cLocation.X) && (boxArr[x].Location.Y == _sChar.m_cLocation.Y))
		{
			boxArr[x].Location.X = 0;
			boxArr[x].Location.Y = 0;
			dialogCollision(boxIndex, g_Console, maxBox, g_eGameState);
		}
	}
}

void dialogCollision(int &boxIndex, Console &g_Console, int &maxBox, EGAMESTATES &g_eGameState)
{
	boxIndex++;
	g_eGameState = S_DIALOG;
}