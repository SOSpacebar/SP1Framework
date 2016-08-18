#include "AnimationManager.h"
#include "game.h"
#include "Framework\console.h"

using namespace std;
FrameData frameData;

extern int hp;

extern Console g_Console;

char AnimationArray[5][150][150];
char indexChar;

int temphp = 98;
int currhp;

void readAnimation(void)
{
	char StringToLoad;

	int row = 0;
	int col = 0;

	string chooseFrameToLoad[50];

	chooseFrameToLoad[0] = "animation/mushroom.txt";
	chooseFrameToLoad[1] = "animation/mushroom1.txt";
	chooseFrameToLoad[2] = "animation/shroom2.txt";
	chooseFrameToLoad[3] = "animation/hp.txt";

	for (int d = 0; d < 4; d++)
	{
		fstream fin(chooseFrameToLoad[d], fstream::in);

		while (fin >> noskipws >> StringToLoad)
		{
			indexChar = StringToLoad;
			if (d == 3 && indexChar == '#')
			{
				AnimationArray[d][row][col] = (char)219;
				//AnimationArray[4][row][col] = (char)219;
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

//damagetaken:
//	if (hp <= 9)
//	{
//		temphp = (hp / temphp)*10;
//
//		for (animationCoord2.Y = 0; animationCoord2.Y < 150; animationCoord2.Y++)
//		{
//			for (animationCoord2.X = 0; animationCoord2.X < temphp; animationCoord2.X++)
//			{
//				if ((AnimationArray[3][animationCoord2.Y][animationCoord2.X] == '\0') || (AnimationArray[3][animationCoord2.Y][animationCoord2.X] == '\n'))
//				{
//					break;
//				}
//				else
//				{
//					g_Console.writeToBuffer(animationCoord, AnimationArray[3][animationCoord2.Y][animationCoord2.X], 0x4A);
//				}
//
//				animationCoord.X++;
//
//			}
//			animationCoord.X = tempValue;
//			animationCoord.Y++;
//		}
//	}
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