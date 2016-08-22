#include "AnimationManager.h"
#include "game.h"
#include "Framework\console.h"

using namespace std;
FrameData frameData;

 extern int hp;

extern Console g_Console;

char AnimationArray[6][150][150];
char indexChar;

int temphp = 98;
int currhp;

extern int playerHealth;
int playerHP = 98;
int playerCurrHP;

void readAnimation(void)
{
	char StringToLoad;

	int row = 0;
	int col = 0;

	string chooseFrameToLoad[50];

	chooseFrameToLoad[0] = "animation/mushroom.txt";
	chooseFrameToLoad[1] = "animation/mushroom1.txt";
	chooseFrameToLoad[2] = "animation/mushroomhit.txt";
	chooseFrameToLoad[3] = "animation/hp.txt";
	chooseFrameToLoad[4] = "animation/dialog1.txt";
	chooseFrameToLoad[5] = "animation/Damage.txt";

	for (int d = 0; d < 6; d++)
	{
		fstream fin(chooseFrameToLoad[d], fstream::in);

		while (fin >> noskipws >> StringToLoad)
		{
			indexChar = StringToLoad;
			if ((d ==  3 || d == 4) && indexChar == '#')
			{
				AnimationArray[d][row][col] = (char)219;
			}
			else
			{
				AnimationArray[d][row][col] = StringToLoad;
			}
			
			col++;

			if (indexChar == '\n')
			{
				col = 0;
				row++;
			}
		}

		fin.close();
		row = 0;
		col = 0;
	}
	
}

void drawAnimation(int keyFrame, COORD animationCoord)
{
	COORD animationCoord2;
	int tempValue = animationCoord.X;

	for (animationCoord2.Y = 0; animationCoord2.Y < 150; animationCoord2.Y++)
	{
		for (animationCoord2.X = 0; animationCoord2.X < 150; animationCoord2.X++)
		{
			if ((AnimationArray[keyFrame][animationCoord2.Y][animationCoord2.X] == '\0') || (AnimationArray[keyFrame][animationCoord2.Y][animationCoord2.X] == '\n'))
			{
				break;
			}
			if (AnimationArray[keyFrame][animationCoord2.Y][animationCoord2.X] == '&' && keyFrame == 3)
			{
				if (hp == 98)
				{
					g_Console.writeToBuffer(animationCoord, (char)219, 0x4A);
				}
				else
				{
					g_Console.writeToBuffer(animationCoord, (char)219, 0x04);
				}
				
			}
			else
			{
				g_Console.writeToBuffer(animationCoord, AnimationArray[keyFrame][animationCoord2.Y][animationCoord2.X], 0x0D);
			}
			
			animationCoord.X++;
			
		}
		animationCoord.X = tempValue;
		animationCoord.Y++;
	}
}

void drawHpCurr(int keyFrame, COORD currCoord)
{
	if (hp != 98)
	{
		temphp = (hp % 98);

		COORD currCoord2;
		int tempValue = currCoord.X;

		for (currCoord2.Y = 0; currCoord2.Y < 150; currCoord2.Y++)
		{
			for (currCoord2.X = 0; currCoord2.X < temphp; currCoord2.X++)
			{
				if ((AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\0') || (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\n'))
				{
					break;
				}
				if (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '&' && keyFrame == 3)
				{
					g_Console.writeToBuffer(currCoord, (char)219, 0x4A);
				}
				else
				{
					g_Console.writeToBuffer(currCoord, AnimationArray[keyFrame][currCoord2.Y][currCoord2.X], 0x0D);
				}
				currCoord.X++;
			}
			currCoord.X = tempValue;
			currCoord.Y++;
		}
	}
}

void drawDialogBox(int keyFrame, COORD boxCoord)
{
	COORD currCoord2;
	boxCoord.X = 0;
	boxCoord.Y = 25;
	int tempValue = boxCoord.X;

	for (currCoord2.Y = 0; currCoord2.Y < 150; currCoord2.Y++)
	{
		for (currCoord2.X = 0; currCoord2.X < 150; currCoord2.X++)
		{
			if ((AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\0') || (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\n'))
			{
				break;
			}

			g_Console.writeToBuffer(boxCoord, AnimationArray[keyFrame][currCoord2.Y][currCoord2.X], 0x0A);

			boxCoord.X++;
		}
		boxCoord.X = tempValue;
		boxCoord.Y++;
	}
}

void damagePopUp(int keyFrame, COORD Pop)
{
	COORD PopCoord2;
	Pop.X = 85; // Position of Popping up Damage Sign
	int tempValue = Pop.X;
	
	for (PopCoord2.Y = 0; PopCoord2.Y < 150; PopCoord2.Y++)
	{
		for (PopCoord2.X = 0; PopCoord2.X < 150; PopCoord2.X++)
		{
			if ((AnimationArray[keyFrame][PopCoord2.Y][PopCoord2.X] == '\0') || (AnimationArray[keyFrame][PopCoord2.Y][PopCoord2.X] == '\n'))
			{
				break;
			}
			if (AnimationArray[keyFrame][PopCoord2.Y][PopCoord2.X] == '&' && keyFrame == 3)
			{
				if (hp == 98)
				{
					g_Console.writeToBuffer(Pop, (char)219, 0x4A);
				}
				else
				{
					g_Console.writeToBuffer(Pop, (char)219, 0x04);
				}

			}
			else
			{
				g_Console.writeToBuffer(Pop, AnimationArray[keyFrame][PopCoord2.Y][PopCoord2.X], 0x0D);
			}

			Pop.X++;

		}
		Pop.X = tempValue;
		Pop.Y++;
	}
}

//Already Set a Different Value appart from the origin... but the image still called from the same one
void drawPlayerHP(int keyFrame, COORD playerCoord)
{
	if (playerHealth != 98)
	{
		playerHP = (playerHealth % 98);

		COORD currCoord2;
		int tempValue = playerCoord.X;

		for (currCoord2.Y = 0; currCoord2.Y < 150; currCoord2.Y++)
		{
			for (currCoord2.X = 0; currCoord2.X < playerHP; currCoord2.X++)
			{
				if ((AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\0') || (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\n'))
				{
					break;
				}
				if (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '&' && keyFrame == 3)
				{
					g_Console.writeToBuffer(playerCoord, (char)219, 0x4A);
				}
				else
				{
					g_Console.writeToBuffer(playerCoord, AnimationArray[keyFrame][currCoord2.Y][currCoord2.X], 0x0D);
				}
				playerCoord.X++;
			}
			playerCoord.X = tempValue;
			playerCoord.Y++;
		}
	}
}