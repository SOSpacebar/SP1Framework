#include "gameObject.h"
#include "Framework\console.h"
#include <math.h>

extern double g_dElapsedTime;
extern Console g_Console;
extern SMapData g_mapData;

objectStruct _object[3];

//================ Check Level objects =====================

void init_object(short level) //Preload the data of the enemy into memory.
{
	if (level == 1)
	{
		short x[3] = { 2, 2, 15 };
		short y[3] = { 3, 10, 15 };
		short distance[3] = { 38, 7, 10 };
		string ID[3] = { "LR_P", "Crusher", "Circular" };

		for (short i = 0; i < 3; i++)
		{
			COORD pos;
			pos.X = x[i];
			pos.Y = y[i];

			_object[i].o_location = pos;
			_object[i].o_ID = ID[i];
			_object[i].o_distance = distance[i];


		}
	}
}

//================ Check game objects =====================

void update_GameObject(void)
{
	for (short j = 0; j < 3; j++)
	{
		for (short p = 0; p < 3; p++)
		{
			if (_object[j].o_ID == "LR_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateLR_Projectile(_object[j].o_location, _object[j].o_distance, g_mapData);
			}
			else if (_object[j].o_ID == "RL_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateRL_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "UD_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateUD_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "DU_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateDU_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "LRUD_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateDiagonal_LR_UD_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "LRDU_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateDiagonal_LR_DU_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "RLUD_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateDiagonal_RL_UD_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "RLDU_P")		//check ID to send coord to specific "update" function for each obstacle
			{
				updateDiagonal_RL_DU_Projectile(_object[j].o_location, _object[j].o_distance);
			}
			else if (_object[j].o_ID == "Crusher")
			{
				updateCrusher(_object[j].o_location, _object[j].o_distance);
			}
		}
	}
	
}

//========= Update each object and its location ============

bool reset = false;
int offsetTime = 0;


string LR_PString = ">>";
int counter_1 = 0;

void updateLR_Projectile(COORD &xy, short &dist, SMapData &map)
	{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.X++;
		counter_1++;
	}

	if (map.mapGrid[xy.X][xy.Y] == (char)219)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X -= counter_1;
		reset = false;
		counter_1 = 0;
	}

	g_Console.writeToBuffer(xy, LR_PString, 0xF6);
}

string RL_PString = "<<";
int counter_2 = 0;

void updateRL_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.X--;
		counter_2++;
	}

	if (xy.X == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += counter_2;
		reset = false;
		counter_2 = 0;
	}

	g_Console.writeToBuffer(xy, RL_PString, 0xF6);
}

string UD_PString = "\/";
int counter_3 = 0;

void updateUD_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.Y--;
		counter_3++;
	}

	if (xy.Y == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.Y += counter_3;
		reset = false;
		counter_3 = 0;
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

string DU_PString = { (char)47, (char)92 };
int counter_4 = 0;

void updateDU_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.Y++;
		counter_4++;
	}

	if (xy.Y == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.Y -= counter_4;
		reset = false;
		counter_4 = 0;
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

char LRUD_PString = 92;
int counter_5 = 0;

void updateDiagonal_LR_UD_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.X++;
		xy.Y--;
		counter_5++;
	}

	if (xy.X == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X -= counter_5;
		xy.Y += counter_5;
		reset = false;
		counter_5 = 0;
	}

	g_Console.writeToBuffer(xy, LRUD_PString, 0xF6);
}

char LRDU_PString = 92;
int counter_6 = 0;

void updateDiagonal_LR_DU_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.X--;
		counter_6++;
		xy.Y++;
	}

	if (xy.X == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += counter_6;
		xy.Y -= counter_6;
		reset = false;
		counter_6 = 0;
	}

	g_Console.writeToBuffer(xy, LRDU_PString, 0xF6);
}

char RLUD_PString = 42;
int counter_7 = 0;

void updateDiagonal_RL_UD_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.X--;
		xy.Y--;
		counter_7++;
	}

	if (xy.X == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += counter_7;
		xy.Y += counter_7;
		reset = false;
		counter_7 = 0;
	}

	g_Console.writeToBuffer(xy, RLUD_PString, 0xF6);
}

char RLDU_PString = 42;
int counter_8 = 0;

void updateDiagonal_RL_DU_Projectile(COORD &xy, short &dist)
{
	offsetTime++;

	if (reset == false && offsetTime % 10 == 0)
	{
		xy.X--;
		xy.Y++;
		counter_8++;
	}

	if (xy.X == dist)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += counter_8;
		xy.Y -= counter_8;
		reset = false;
		counter_8 = 0;
	}

	g_Console.writeToBuffer(xy, RLDU_PString, 0xF6);
}

string CrusherString = { (char)178 };
bool reversing = false;
int offsetTime_2 = 0;
int counter_9 = 0;

void updateCrusher(COORD &xy, short &dist)
{
	offsetTime_2++;

	if (reversing == false && offsetTime_2 % 40 == 0)
	{
		xy.X++;
		counter_9++;
	}

	if (xy.X >= 7)
	{
		reversing = true;
	}

	if (reversing && offsetTime_2 % 1 == 0)
	{
		xy.X--;
		counter_9--;
		if (counter_9 == 0)
		{
			reversing = false;
		}
	}
	g_Console.writeToBuffer(xy, CrusherString, 0xF6);
}

string circleString = "()";
int offsetTime2 = 0;
float Pi = 3.1415926f;
double R = 10;
COORD z;
double t = 0;

void TryCircle(COORD xy)
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