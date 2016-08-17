#include "gameObject.h"
#include "Framework\console.h"

extern double g_dElapsedTime;
extern Console g_Console;

double currTime;
COORD x;
string ObstacleString = ">";

bool reversing = false;
int offsetTime = 0;

void updateProjectile(void)
{
	
	currTime = g_dElapsedTime;

	bool bSomethingHappened = false;
	
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character

	x.Y = 5;
	offsetTime++;

	if (currTime == g_dElapsedTime && reversing == false && offsetTime == 20)
	{
		ObstacleString = ">";
		//bSomethingHappened = true;
		x.X++;
		x.Y = 5;
		offsetTime = 0;
		g_Console.writeToBuffer(x, ObstacleString, 0xF6);
	}

	if (x.X >= 10)
	{
		reversing = true;
	}

	if (reversing && offsetTime == 20)
	{
		ObstacleString = "<";
		x.X--;
		x.Y = 5;
		offsetTime = 0;
		g_Console.writeToBuffer(x, ObstacleString, 0xF6);
		if (x.X == 1)
		{
			reversing = false;
		}
	}
	g_Console.writeToBuffer(x, ObstacleString, 0xF6);
}