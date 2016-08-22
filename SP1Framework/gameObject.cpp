#include "gameObject.h"
#include "Framework\console.h"
#include <math.h>

extern double g_dElapsedTime;
extern double g_dDeltaTime;
extern Console g_Console;
extern SMapData g_mapData;

int offsetTime = g_dDeltaTime;

//============ Test ================
int counterTime = offsetTime;
//==================================

objectStruct _object[5];

//================ Check Level objects =====================

void init_object(short level) //Preload the data of the enemy into memory.
{
	if (level == 1)
	{
		short x[5] = { 2, 12, 20, 10, 7 };
		short y[5] = { 3, 9, 9, 19, 10 };
		string ID[5] = { ">", "<O>", "^Ov", "^Ov", "v" };
		string speed[5] = { "slow", "normal", "normal", "normal", "slow" };		//check speed level: Slow, Normal, Fast.  Crusher has fixed speed due to it having 2 diff speed for "load" and "crush"
		int distance[5] = { 10, 10, 7, 5, 5 };
		bool reset[5] = { false, false, false, false, false };
		int count[5] = { 0, 0, 0, 0, 0, };

		for (short i = 0; i < 5; i++)
		{
			COORD pos;
			pos.X = x[i];
			pos.Y = y[i];

			_object[i].o_location = pos;
			_object[i].o_start_location = pos;
			_object[i].o_ID = ID[i];
			_object[i].o_distance = distance[i];
			_object[i].o_reset = reset[i];
			_object[i].o_shift = count[i];

			if (speed[i] == "slow")
			{
				_object[i].o_speed.push_back(50);
			}
			else if (speed[i] == "normal")
			{
				_object[i].o_speed.push_back(40);
			}
			else if (speed[i] == "fast")
			{
				_object[i].o_speed.push_back(30);
			}
			else
			{
				_object[i].o_speed.push_back(1000);
			}
		}
	}
}

//================ Check game objects ======================

void update_GameObject(void)
{
	offsetTime += 5;
	counterTime += 1;

	if (counterTime > 6)
	{
		counterTime = 0;
	}

	for (short j = 0; j < 5; j++)
	{
		if (_object[j].o_ID == ">")					//check ID to send coord to specific "update" function for each obstacle
		{
			updateLR_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset, _object[j].o_shift);
		}
		else if (_object[j].o_ID == "<")
		{
			updateRL_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset, _object[j].o_shift);
		}
		else if (_object[j].o_ID == "v")
		{
			updateUD_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset, _object[j].o_shift);
		}
		else if (_object[j].o_ID == "^")
		{
			updateDU_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset, _object[j].o_shift);
		}
		else if (_object[j].o_ID == "<O>")
		{
			updateLR_EBall(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset, _object[j].o_shift);
		}
		else if (_object[j].o_ID == "^Ov")
		{
			updateUD_EBall(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset, _object[j].o_shift);
		}
	}
}

//========= Update each object and its location ============

char LR_PString = '>';

void updateLR_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count)
{
	if (reset == false && (offsetTime % speed[0] == 0))
	{
		xy.X++;
	}

	if (dist == xy.X - start_xy.X || g_mapData.mapGrid[xy.Y - 1][xy.X] == (char)219)
	{
		reset = true;
	}

	if (reset)
	{
		xy = start_xy;
		reset = false;
	}
	
	g_Console.writeToBuffer(xy, LR_PString, 0xF6);
}

char RL_PString = '<';

void updateRL_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.X--;
	}

	if (dist == xy.X + start_xy.X || g_mapData.mapGrid[xy.Y-1][xy.X] == (char)219)
	{
		reset = true;
	}

	if (reset)
	{
		xy = start_xy;
		reset = false;
	}

	g_Console.writeToBuffer(xy, RL_PString, 0xF6);
}

char UD_PString = 'v';

void updateUD_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.Y++;
	}

	if (dist == xy.Y - start_xy.Y || g_mapData.mapGrid[xy.Y - 1][xy.X] == (char)219)
	{
		reset = true;
	}

	if (reset)
	{
		xy = start_xy;
		reset = false;
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

char DU_PString = '^';

void updateDU_Projectile(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset, int &count)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.Y--;
	}

	if (dist == xy.Y + start_xy.Y || g_mapData.mapGrid[xy.Y - 2][xy.X] == (char)219)
	{
		reset = true;
	}

	if (reset)
	{
		xy = start_xy;
		reset = false;
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

string CrusherString = { (char)178 };

void updateLR_EBall(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reverse, int &count)
{
	if (count == 6 && counterTime <= 6)
	{
		count = 0;
		ID = "^Ov";
	}
	else
	{
		if (reverse == false && offsetTime % speed[0] == 0)
		{
			xy.X++;
			if (g_mapData.mapGrid[xy.Y - 1][xy.X] == (char)219)
			{
				reverse = true;
			}
		}

		if (reverse && offsetTime % speed[0] == 0)
		{
			xy.X--;
			if (g_mapData.mapGrid[xy.Y - 1][xy.X - 1] == (char)219)
			{
				reverse = false;
				count++;
			}
		}
	}
	g_Console.writeToBuffer(xy, CrusherString, 0xF6);
}

void updateUD_EBall(string &ID, COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reverse, int &count)
{
	if (count == 6 && counterTime <= 6)
	{
		count = 0;
		ID = "<O>";
	}
	else if (count == 6)
	{
		count = 0;
	}
	else
	{
		if (reverse == false && offsetTime % speed[0] == 0)
		{
			xy.Y++;
			if (g_mapData.mapGrid[xy.Y - 1][xy.X] == (char)219)
			{
				reverse = true;
			}
		}

		if (reverse && offsetTime % speed[0] == 0)
		{
			xy.Y--;
			if (g_mapData.mapGrid[xy.Y - 2][xy.X - 1] == (char)219)
			{
				reverse = false;
				count++;
			}
		}
	}
	g_Console.writeToBuffer(xy, CrusherString, 0xF6);
}

//======== Might not work ========//

string circleString = "()";
int offsetTime2 = 0;
float Pi = 3.1415926f;
double R = 10;
COORD z;
double t = 0;

void TryCircle(COORD xy) // might scrape
{
	offsetTime2++;

	if (offsetTime % 1 == 0)
	{
		t += 0.01;
		
		if (t >= 2 * Pi)
		{
			t = 0;
		}

		z.X = (R*cos(t) + 15) * 2;
		z.Y = (R*sin(t) + 15);
	}
	g_Console.writeToBuffer(z, circleString, 0xF6);

}