#include "AnimationManager.h"
#include "game.h"
#include "Framework\console.h"

using namespace std;
FrameData frameData;

extern Console g_Console;

char AnimationArray[5][150][150];
char indexChar;

void readAnimation(void)
{
	char StringToLoad;

	int row = 0;
	int col = 0;

	string chooseFrameToLoad[50];

	chooseFrameToLoad[0] = "animation/mushroom.txt";
	chooseFrameToLoad[1] = "animation/mushroom1.txt";
	chooseFrameToLoad[2] = "animation/shroom2.txt";

	for (int d = 0; d < 3; d++)
	{
		fstream fin(chooseFrameToLoad[d], fstream::in);

		while (fin >> noskipws >> StringToLoad)
		{
			AnimationArray[d][row][col] = StringToLoad;
			indexChar = StringToLoad;
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

void drawAnimation(int keyFrame)
{
	COORD animationCoord;

	for (animationCoord.Y = 5; animationCoord.Y < 150; animationCoord.Y++)
	{
		for (animationCoord.X = 5; animationCoord.X < 150; animationCoord.X++)
		{
			if ((AnimationArray[keyFrame][animationCoord.Y - 5][animationCoord.X - 5] == '\0') || (AnimationArray[keyFrame][animationCoord.Y - 5][animationCoord.X - 5] == '\n'))
			{
				break;
			}
			g_Console.writeToBuffer(animationCoord, AnimationArray[keyFrame][animationCoord.Y - 5][animationCoord.X - 5], 0x0D);

		}
	}
	animationCoord.Y = 5;
	animationCoord.X = 5;
}