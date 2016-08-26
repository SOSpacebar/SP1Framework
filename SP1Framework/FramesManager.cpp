#include "AnimationManager.h"
#include "game.h"
#include "Framework\console.h"

FrameData frameData;

int enemyHp = 98;
int playerCurrHP = 98;

char AnimationArray[21][150][150];
char indexChar;

void readAnimation(void)
{
	char StringToLoad;

	int row = 0;
	int col = 0;

	string chooseFrameToLoad[50];

	chooseFrameToLoad[0] = "animation/mushroom.txt";
	chooseFrameToLoad[1] = "animation/mushroom1.txt";
	chooseFrameToLoad[2] = "animation/mushroomhit.txt";
	chooseFrameToLoad[3] = "animation/mobhp.txt";
	chooseFrameToLoad[4] = "animation/dialog1.txt";
	chooseFrameToLoad[5] = "animation/Damage.txt";
	chooseFrameToLoad[6] = "animation/playerHP.txt";
	chooseFrameToLoad[7] = "animation/Warning.txt";
	chooseFrameToLoad[8] = "animation/Loading.txt";
	chooseFrameToLoad[9] = "dialogs/dialog1.txt";
	chooseFrameToLoad[10] = "dialogs/dialog2.txt";
	chooseFrameToLoad[11] = "dialogs/dialog3.txt";
	chooseFrameToLoad[12] = "dialogs/dialog4.txt";
	chooseFrameToLoad[13] = "dialogs/dialog5.txt";
	chooseFrameToLoad[14] = "dialogs/dialog6.txt";
	chooseFrameToLoad[15] = "dialogs/dialog7.txt";
	chooseFrameToLoad[16] = "animation/MushroomH1.txt";
	chooseFrameToLoad[17] = "animation/MushroomH2.txt";
	chooseFrameToLoad[18] = "animation/MushroomH3.txt";
	chooseFrameToLoad[19] = "animation/Slime.txt";
	chooseFrameToLoad[20] = "animation/Slime2.txt";
	chooseFrameToLoad[21] = "animation/Slime3.txt";

	for (int d = 0; d < 22; d++)
	{
		fstream fin(chooseFrameToLoad[d], fstream::in);

		while (fin >> noskipws >> StringToLoad)
		{
			indexChar = StringToLoad;
			if ((d ==  3 || d == 4 || d == 6) && indexChar == '#')
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

void drawAnimation(int keyFrame, COORD animationCoord, Console &g_Console)
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
			if (AnimationArray[keyFrame][animationCoord2.Y][animationCoord2.X] == '&' && (keyFrame == 3 || keyFrame == 6))
			{

				g_Console.writeToBuffer(animationCoord, (char)219, 0x04);

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

void drawHpCurr(int keyFrame, COORD currCoord, int &hp, Console &g_Console)
{
	enemyHp = (hp % 98);
	COORD currCoord2;
	int tempValue = currCoord.X;

	if (hp != 98)
	{
		for (currCoord2.Y = 0; currCoord2.Y < 150; currCoord2.Y++)
		{
			for (currCoord2.X = 0; currCoord2.X < enemyHp - 4; currCoord2.X++)
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
				if (hp <= 16)
				{
					hp = 0;
				}
				currCoord.X++;
			}
			currCoord.X = tempValue;
			currCoord.Y++;
		}
	}
	else if (hp == 98)
	{
		for (currCoord2.Y = 0; currCoord2.Y < 150; currCoord2.Y++)
		{
			for (currCoord2.X = 0; currCoord2.X < 150; currCoord2.X++)
			{
				if ((AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\0') || (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\n'))
				{
					break;
				}
				if (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '&' && (keyFrame == 3 || keyFrame == 6))
				{
					if (hp == 98)
					{
						g_Console.writeToBuffer(currCoord, (char)219, 0x4A);
					}
					else
					{
						g_Console.writeToBuffer(currCoord, (char)219, 0x04);
					}

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

void drawDialogBox(int keyFrame, COORD boxCoord, Console &g_Console)
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

void damagePopUp(int keyFrame, COORD Pop, Console &g_Console)
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
			g_Console.writeToBuffer(Pop, AnimationArray[keyFrame][PopCoord2.Y][PopCoord2.X], 0x0D);
			Pop.X++;

		}
		Pop.X = tempValue;
		Pop.Y++;
	}
}

//Already Set a Different Value appart from the origin... but the image still called from the same one
void drawPlayerHP(int keyFrame, COORD playerCoord, int &playerHealth, Console &g_Console)
{
	playerCurrHP = (playerHealth % 98);

	COORD playerCoord2;
	int tempValue = playerCoord.X;

	if (playerHealth != 98)
	{
		for (playerCoord2.Y = 0; playerCoord2.Y < 150; playerCoord2.Y++)
		{
			for (playerCoord2.X = 0; playerCoord2.X < playerCurrHP; playerCoord2.X++)
			{
				if ((AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X] == '\0') || (AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X] == '\n'))
				{
					break;
				}
				if (AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X] == '&' && keyFrame == 6)
				{
					g_Console.writeToBuffer(playerCoord, (char)219, 0x4A);
				}
				else
				{
					g_Console.writeToBuffer(playerCoord, AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X], 0x0D);
				}
				playerCoord.X++;
			}
			playerCoord.X = tempValue;
			playerCoord.Y++;
		}
	}
	else if (playerHealth = 98)
	{
 		for (playerCoord2.Y = 0; playerCoord2.Y < 150; playerCoord2.Y++)
		{
			for (playerCoord2.X = 0; playerCoord2.X < 150; playerCoord2.X++)
			{
				if ((AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X] == '\0') || (AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X] == '\n'))
				{
					break;
				}
				if (AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X] == '&' && (keyFrame == 3 || keyFrame == 6))
				{
					if (playerHealth == 98)
					{
						g_Console.writeToBuffer(playerCoord, (char)219, 0x4A);
					}
					else
					{
						g_Console.writeToBuffer(playerCoord, (char)219, 0x04);
					}

				}
				else
				{
					g_Console.writeToBuffer(playerCoord, AnimationArray[keyFrame][playerCoord2.Y][playerCoord2.X], 0x0D);
				}

				playerCoord.X++;

			}
			playerCoord.X = tempValue;
			playerCoord.Y++;
		}
	}
}
