#include "AnimationManager.h"
#include "game.h"
#include "Framework\console.h"

FrameData frameData;

int enemyHp = 98;
int playerCurrHP = 98;
short combatIndex = 0;

char AnimationArray[31][150][150];
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
	chooseFrameToLoad[9] = "animation/Title.txt";
	chooseFrameToLoad[10] = "animation/GameOver.txt";
	chooseFrameToLoad[11] = "dialogs/dialog1.txt";
	chooseFrameToLoad[12] = "dialogs/dialog2.txt";
	chooseFrameToLoad[13] = "dialogs/dialog3.txt";
	chooseFrameToLoad[14] = "dialogs/dialog4.txt";
	chooseFrameToLoad[15] = "dialogs/dialog5.txt";
	chooseFrameToLoad[16] = "dialogs/dialog6.txt";
	chooseFrameToLoad[17] = "dialogs/dialog7.txt";
	chooseFrameToLoad[18] = "dialogs/dialog8.txt";
	chooseFrameToLoad[19] = "dialogs/dialog9.txt";
	chooseFrameToLoad[20] = "animation/hpui.txt";
	chooseFrameToLoad[21] = "animation/expui.txt";
	chooseFrameToLoad[22] = "animation/uibox.txt";
	chooseFrameToLoad[23] = "animation/manaui.txt";
	chooseFrameToLoad[24] = "animation/MushroomH1.txt";
	chooseFrameToLoad[25] = "animation/MushroomH2.txt";
	chooseFrameToLoad[26] = "animation/MushroomH3.txt";
	chooseFrameToLoad[27] = "animation/Slime.txt";
	chooseFrameToLoad[28] = "animation/Slime2.txt";
	chooseFrameToLoad[29] = "animation/Slime3.txt";
	chooseFrameToLoad[30] = "animation/Title_static_1.txt";
	chooseFrameToLoad[31] = "animation/Title_static_2.txt";

	for (int d = 0; d < 31; d++)
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

void drawTitle(int keyFrame, COORD T_Coord, Console &g_Console)
{
	COORD currCoord2;
	T_Coord.X;
	T_Coord.Y;

	int tempValue = T_Coord.X;

	for (currCoord2.Y = 0; currCoord2.Y < 8; currCoord2.Y++)
	{
		for (currCoord2.X = 0; currCoord2.X < 120; currCoord2.X++)
		{
			if ((AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\0') || (AnimationArray[keyFrame][currCoord2.Y][currCoord2.X] == '\n'))
			{
				break;
			}

			g_Console.writeToBuffer(T_Coord, AnimationArray[keyFrame][currCoord2.Y][currCoord2.X], 0x0A);

			T_Coord.X++;
		}
		T_Coord.X = tempValue;
		T_Coord.Y++;
	}
}

void drawUI(Console &g_Console)
{
	COORD UiLocationStart;
	COORD UiLocationIndex;

	UiLocationStart.X = 0;
	UiLocationStart.Y = 36;

	int tempValue = UiLocationStart.X;

	for (UiLocationIndex.Y = 0; UiLocationIndex.Y < 50; UiLocationIndex.Y++)
	{
		for (UiLocationIndex.X = 0; UiLocationIndex.X < 150; UiLocationIndex.X++)
		{
			if ((AnimationArray[22][UiLocationIndex.Y][UiLocationIndex.X] == '\0') || (AnimationArray[22][UiLocationIndex.Y][UiLocationIndex.X] == '\n'))
			{
				break;
			}

			g_Console.writeToBuffer(UiLocationStart, AnimationArray[22][UiLocationIndex.Y][UiLocationIndex.X], 0x0B);

			UiLocationStart.X++;
		}
		UiLocationStart.X = tempValue;
		UiLocationStart.Y++;
	}
}

void drawEXP(Console &g_Console)
{
	COORD UiLocationStart;
	COORD UiLocationIndex;

	UiLocationStart.X = 4;
	UiLocationStart.Y = 47;

	int tempValue = UiLocationStart.X;

	for (UiLocationIndex.Y = 0; UiLocationIndex.Y < 50; UiLocationIndex.Y++)
	{
		for (UiLocationIndex.X = 0; UiLocationIndex.X < 150; UiLocationIndex.X++)
		{
			if ((AnimationArray[21][UiLocationIndex.Y][UiLocationIndex.X] == '\0') || (AnimationArray[21][UiLocationIndex.Y][UiLocationIndex.X] == '\n'))
			{
				break;
			}
			
			if (AnimationArray[21][UiLocationIndex.Y][UiLocationIndex.X] == '$')
			{
				g_Console.writeToBuffer(UiLocationStart, (char)178, 0x0E);
			}
			else
			{
				g_Console.writeToBuffer(UiLocationStart, AnimationArray[21][UiLocationIndex.Y][UiLocationIndex.X], 0x0E);
			}

			UiLocationStart.X++;
		}
		UiLocationStart.X = tempValue;
		UiLocationStart.Y++;
	}

}

void drawHP(Console &g_Console)
{
	COORD UiLocationStart;
	COORD UiLocationIndex;

	UiLocationStart.X = 4;
	UiLocationStart.Y = 43;

	int tempValue = UiLocationStart.X;

	for (UiLocationIndex.Y = 0; UiLocationIndex.Y < 50; UiLocationIndex.Y++)
	{
		for (UiLocationIndex.X = 0; UiLocationIndex.X < 150; UiLocationIndex.X++)
		{
			if ((AnimationArray[20][UiLocationIndex.Y][UiLocationIndex.X] == '\0') || (AnimationArray[20][UiLocationIndex.Y][UiLocationIndex.X] == '\n'))
			{
				break;
			}

			if (AnimationArray[20][UiLocationIndex.Y][UiLocationIndex.X] == '*')
			{
				g_Console.writeToBuffer(UiLocationStart, (char)178, 0x04);
			}
			else
			{
				g_Console.writeToBuffer(UiLocationStart, AnimationArray[20][UiLocationIndex.Y][UiLocationIndex.X], 0x04);
			}
			UiLocationStart.X++;
		}
		UiLocationStart.X = tempValue;
	}

	UiLocationStart.X = 61;
	tempValue = UiLocationStart.X;
	for (UiLocationIndex.Y = 0; UiLocationIndex.Y < 50; UiLocationIndex.Y++)
	{
		for (UiLocationIndex.X = 0; UiLocationIndex.X < 150; UiLocationIndex.X++)
		{
			if ((AnimationArray[23][UiLocationIndex.Y][UiLocationIndex.X] == '\0') || (AnimationArray[23][UiLocationIndex.Y][UiLocationIndex.X] == '\n'))
			{
				break;
			}

			if (AnimationArray[23][UiLocationIndex.Y][UiLocationIndex.X] == '*')
			{
				g_Console.writeToBuffer(UiLocationStart, (char)178, 0x01);
			}
			else
			{
				g_Console.writeToBuffer(UiLocationStart, AnimationArray[23][UiLocationIndex.Y][UiLocationIndex.X], 0x0E);
			}

			UiLocationStart.X++;
		}
		UiLocationStart.X = tempValue;
	}
}

void drawTextUI(Console &g_Console)
{
	COORD UiLocationStart;
	COORD UiLocationIndex;

	//Name Text
	UiLocationStart.X = 3;
	UiLocationStart.Y = 38;
	g_Console.writeToBuffer(UiLocationStart,"Name:", 0x0F);
	UiLocationStart.X = 6;
	UiLocationStart.Y = 39;
	g_Console.writeToBuffer(UiLocationStart, "John", 0x0F);

	////Player Level
	//UiLocationStart.X = 3;
	//UiLocationStart.Y = 41;
	//g_Console.writeToBuffer(UiLocationStart, "Level:", 0x0F);

	//Player Health
	UiLocationStart.X = 3;
	UiLocationStart.Y = 42;
	g_Console.writeToBuffer(UiLocationStart, "Health:", 0x0F);
	UiLocationStart.X = 11;
	g_Console.writeToBuffer(UiLocationStart, "100 / 100", 0x0F);

	//Player Mana
	UiLocationStart.X = 60;
	UiLocationStart.Y = 42;
	g_Console.writeToBuffer(UiLocationStart, "Energy:", 0x0F);
	UiLocationStart.X = 68;
	g_Console.writeToBuffer(UiLocationStart, "100 / 100", 0x0F);

	//Maze Level
	UiLocationStart.X = 3;
	UiLocationStart.Y = 45;
	g_Console.writeToBuffer(UiLocationStart, "Level:", 0x0F);
	UiLocationStart.X = 10;
	UiLocationStart.Y = 45;
	g_Console.writeToBuffer(UiLocationStart, "01", 0x0F);

	//EXP text
	UiLocationStart.X = 3;
	UiLocationStart.Y = 46;
	g_Console.writeToBuffer(UiLocationStart, "Experience:", 0x0F);
}

void drawCombatMenu(Console &g_Console)
{
	COORD UiLocationStart;
	COORD UiLocationIndex;
	

	//draw combat menu box
	UiLocationStart.X = 95;
	UiLocationStart.Y = 29;
	int tempValue = UiLocationStart.X;

	for (int y = 0; y < 7; y++) 
	{
		for (int x = 0; x < 25; x++)
		{
			if ((x != 0) && (x != 24))
			{
				if ((y >= 1) && (y < 6))
				{

				}
				else
				{
					g_Console.writeToBuffer(UiLocationStart, (char)219, 0x0D);
					UiLocationStart.X++;
				}
			}
			else
			{
				g_Console.writeToBuffer(UiLocationStart, (char)219, 0x0D);
				UiLocationStart.X++;
			}
			
		}
		UiLocationStart.X = tempValue;
		UiLocationStart.Y++;
	}

	if (combatIndex == 0)
	{
		UiLocationStart.X = 102;
		UiLocationStart.Y = 31;
		g_Console.writeToBuffer(UiLocationStart, " > FIGHT < ", 0x0D);
		UiLocationStart.X = 104;
		UiLocationStart.Y = 33;
		g_Console.writeToBuffer(UiLocationStart, " MAGIC ", 0x0D);
	}
	else if (combatIndex == 1)
	{
		UiLocationStart.X = 104;
		UiLocationStart.Y = 31;
		g_Console.writeToBuffer(UiLocationStart, " FIGHT ", 0x0D);
		UiLocationStart.X = 102;
		UiLocationStart.Y = 33;
		g_Console.writeToBuffer(UiLocationStart, " > MAGIC < ", 0x0D);
	}

	else if (combatIndex == 2)
	{
		UiLocationStart.X = 102;
		UiLocationStart.Y = 31;
		g_Console.writeToBuffer(UiLocationStart, " > SLASH < ", 0x0D);
		UiLocationStart.X = 104;
		UiLocationStart.Y = 33;
		g_Console.writeToBuffer(UiLocationStart, " SMASH ", 0x0D);
	}
	
	else if (combatIndex == 3)
	{
		UiLocationStart.X = 104;
		UiLocationStart.Y = 31;
		g_Console.writeToBuffer(UiLocationStart, " SLASH ", 0x0D);
		UiLocationStart.X = 102;
		UiLocationStart.Y = 33;
		g_Console.writeToBuffer(UiLocationStart, " > SMASH < ", 0x0D);
	}

	else if (combatIndex == 4)
	{
		UiLocationStart.X = 102;
		UiLocationStart.Y = 31;
		g_Console.writeToBuffer(UiLocationStart, " > FLARE < ", 0x0D);
		UiLocationStart.X = 104;
		UiLocationStart.Y = 33;
		g_Console.writeToBuffer(UiLocationStart, " BURST ", 0x0D);
	}

	else if (combatIndex == 5)
	{
		UiLocationStart.X = 104;
		UiLocationStart.Y = 31;
		g_Console.writeToBuffer(UiLocationStart, " FLARE ", 0x0D);
		UiLocationStart.X = 102;
		UiLocationStart.Y = 33;
		g_Console.writeToBuffer(UiLocationStart, " > BURST < ", 0x0D);
	}
}