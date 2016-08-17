#include "gameObject.h"
#include "Framework\console.h"

extern double g_dElapsedTime;
extern Console g_Console;

double currTime;
COORD x;
char ProjectileString = 175;

bool reset = false;
int offsetTime = 0;

void updateProjectile(void)
{
	currTime = g_dElapsedTime;

	x.Y = 5;
	offsetTime++;

	if (currTime == g_dElapsedTime && reset == false && offsetTime % 3 == 0)
	{
		x.X++;
		x.Y = 5;
		g_Console.writeToBuffer(x, ProjectileString, 0xF6);
	}

	if (x.X >= 40)
	{
		reset = true;
	}

	if (reset)
	{
		x.X = 2;
		reset = false;
	}

	g_Console.writeToBuffer(x, ProjectileString, 0xF6);
}


double currTime2;
COORD z;
string SpikeBallString = { (char)178 };

bool reversing = false;
int offsetTime2 = 0;

void SpikeBall(void)
{
	currTime2 = g_dElapsedTime;

	bool bSomethingHappened = false;

	z.Y = 11;
	offsetTime2++;

	if (currTime2 == g_dElapsedTime && reversing == false && offsetTime2 % 15 == 0)
	{
		z.X++;
		g_Console.writeToBuffer(z, SpikeBallString, 0xF6);
	}

	if (z.X >= 7)
	{
		reversing = true;
	}

	if (reversing && offsetTime2 % 1 == 0)
	{
		z.X--;
		g_Console.writeToBuffer(z, SpikeBallString, 0xF6);

		if (z.X == 2)
		{
			reversing = false;
		}
	}
	g_Console.writeToBuffer(z, SpikeBallString, 0xF6);
}