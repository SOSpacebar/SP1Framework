#include "gameObject.h"
#include "Framework\console.h"
#include <math.h>

extern double g_dElapsedTime;
extern double g_dDeltaTime;
extern Console g_Console;
extern SMapData g_mapData;

int offsetTime = g_dDeltaTime;

objectStruct _object[5];

//================ Check Level objects ===================== Problem: it can only call 1 function at a time...

void init_object(short level) //Preload the data of the enemy into memory.
{
	if (level == 1)
	{
		short x_start[5]	= { 2, 15, 20, 10, 7};
		short y_start[5]	= { 3, 20, 9, 10, 10};
		short x[5]			= { 2, 15, 20, 10, 7};
		short y[5]			= { 3, 20, 9, 10, 10 };
		string ID[5]		= { "LR_P", "Crusher", "RL_P", "Crusher", "DU_P" };
		string speed[5]		= { "slow", "normal", "normal", "normal", "slow" };		//check speed level: Slow, Normal, Fast.  Crusher has fixed speed due to it having 2 diff speed for "load" and "crush"
		int distance[5]		= { 10, 7, 7, 5, 5 };
		bool reset[5]		= { false, false, false, false, false };

		for (short i = 0; i < 5; i++)
		{
			COORD pos;
			pos.X = x[i];
			pos.Y = y[i];

			COORD pos_start;
			pos_start.X = x_start[i];
			pos_start.Y = y_start[i];

			_object[i].o_location = pos;
			_object[i].o_start_location = pos_start;
			_object[i].o_ID = ID[i];
			_object[i].o_distance = distance[i];
			_object[i].o_reset = reset[i];

			/*

			for (int x = 0; x < 5; x++ )
			{
				
				objectArr[x][0] = _object.o_location;
				objectArr[x][1] = xxxxx;
				
			}



			*/
			
			if (speed[i] == "slow")
			{
				if (_object[i].o_ID == "Crusher")
				{
					_object[i].o_speed.push_back(50);
					_object[i].o_speed.push_back(3);
				}
				else
				{
					_object[i].o_speed.push_back(30);
				}
			}
			else if (speed[i] == "normal")
			{
				if (_object[i].o_ID == "Crusher")
				{
					_object[i].o_speed.push_back(40);
					_object[i].o_speed.push_back(2);
				}
				else
				{
					_object[i].o_speed.push_back(20);
				}
			}
			else if (speed[i] == "fast")
			{
				if (_object[i].o_ID == "Crusher")
				{
					_object[i].o_speed.push_back(30);
					_object[i].o_speed.push_back(1);
				}
				else
				{
					_object[i].o_speed.push_back(10);
				}
			}
			else
			{
				if (_object[i].o_ID == "Crusher")
				{
					_object[i].o_speed.push_back(100);
					_object[i].o_speed.push_back(1);
				}
				else
				{
					_object[i].o_speed.push_back(100);
				}
			}
		}
	}
}

//================ Check game objects =====================

void update_GameObject(void)
{
	for (short j = 0; j < 5; j++)
	{
		if (_object[j].o_ID == "LR_P")				//check ID to send coord to specific "update" function for each obstacle
		{
			updateLR_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "RL_P")			//check ID to send coord to specific "update" function for each obstacle
		{
			updateRL_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "UD_P")			//check ID to send coord to specific "update" function for each obstacle
		{
			/*
			
			if (arr[0][5] == 5 || arr[2][5] )
			{
				update(	arr[x][0],		
			}
			if (arr[1][5] == 10)
			{
				update(	arr[x][0],		
			}
			if (arr[2][5] == 5)
			{
			update(	arr[x][0],
			}
			
			
			*/
			updateUD_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "DU_P")			//check ID to send coord to specific "update" function for each obstacle
		{
			updateDU_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "LRUD_P")		//check ID to send coord to specific "update" function for each obstacle
		{
			updateDiagonal_LR_UD_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "LRDU_P")		//check ID to send coord to specific "update" function for each obstacle
		{
			updateDiagonal_LR_DU_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "RLUD_P")		//check ID to send coord to specific "update" function for each obstacle
		{
			updateDiagonal_RL_UD_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "RLDU_P")		//check ID to send coord to specific "update" function for each obstacle
		{
			updateDiagonal_RL_DU_Projectile(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "Crusher")
		{
			updateCrusher(_object[j].o_start_location, _object[j].o_location, _object[j].o_distance, _object[j].o_speed, _object[j].o_reset);
		}
	}
	offsetTime += 5;
}
	


//========= Update each object and its location ============


string LR_PString = ">>";

void updateLR_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
	{
		if (reset == false && (offsetTime % speed[0] == 0))
	{
		xy.X++;
	}

	if (dist == xy.X - start_xy.X)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X -= dist;
		reset = false;
	}
	
	g_Console.writeToBuffer(xy, LR_PString, 0xF6);
}

string RL_PString = "<<";

void updateRL_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.X--;
	}

	if (dist == xy.X + start_xy.X)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, RL_PString, 0xF6);
}

string UD_PString = "\/";

void updateUD_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.Y++;
	}

	if (dist == xy.Y - start_xy.Y)
	{
		reset = true;
	}

	if (reset)
	{
		xy.Y -= dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

string DU_PString = { (char)47, (char)92 };

void updateDU_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.Y--;
	}

	if (dist == xy.Y + start_xy.Y)
	{
		reset = true;
	}

	if (reset)
	{
		xy.Y += dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

char LRUD_PString = 92;

void updateDiagonal_LR_UD_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.X++;
		xy.Y++;
	}

	if (dist == xy.X - start_xy.X)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X -= dist;
		xy.Y -= dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, LRUD_PString, 0xF6);
}

char LRDU_PString = 92;

void updateDiagonal_LR_DU_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.X++;
		xy.Y--;
	}

	if (dist == xy.X - start_xy.X)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X -= dist;
		xy.Y += dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, LRDU_PString, 0xF6);
}

char RLUD_PString = 42;

void updateDiagonal_RL_UD_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.X--;
		xy.Y++;
	}

	if (dist == xy.X + start_xy.X)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += dist;
		xy.Y -= dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, RLUD_PString, 0xF6);
}

char RLDU_PString = 42;

void updateDiagonal_RL_DU_Projectile(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reset)
{
	if (reset == false && offsetTime % speed[0] == 0)
	{
		xy.X--;
		xy.Y--;
	}

	if (dist == xy.X + start_xy.X)
	{
		reset = true;
	}

	if (reset)
	{
		xy.X += dist;
		xy.Y += dist;
		reset = false;
	}

	g_Console.writeToBuffer(xy, RLDU_PString, 0xF6);
}

string CrusherString = { (char)178 };

void updateCrusher(COORD &start_xy, COORD &xy, int &dist, vector <int> &speed, bool &reverse)
{
	if (reverse == false && offsetTime % speed[0] == 0)
	{
		xy.X++;
	}

	if (dist == xy.X - start_xy.X)
	{
		reverse = true;
	}

	if (reverse && offsetTime % speed[1] == 0)
	{
		xy.X--;

		if (xy.X == start_xy.X)
		{
			reverse = false;
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