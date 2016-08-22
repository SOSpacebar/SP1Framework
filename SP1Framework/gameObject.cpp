#include "gameObject.h"
#include "Framework\console.h"
#include <math.h>
#include <time.h>
#include <vector>

extern Console g_Console;
extern SMapData g_mapData;

int offsetTime = 0;



//================ Check Level objects =====================

vector<short> x;
vector<short> y;
vector<string> ID;
vector<string> speed;
vector<bool> reset;

objectStruct _object[10];

void createObjectString()
{
	string OID[8] = { ">", "<O>", "<", "^Ov", "v", "^", "<O>", "^Ov" };
	string Ospeed[3] = { "slow", "normal", "fast" };

	ID.push_back(OID[randomArr(8)]);
	speed.push_back(Ospeed[randomArr(3)]);
	reset.push_back(false);
}

void init_object(short level) //Preload the data of the enemy into memory.
{
	if (level == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			createObjectString();
			COORD pos;
			pos.X = x[i];
			pos.Y = y[i];

			_object[i].o_location = pos;
			_object[i].o_ID = ID[i];
			_object[i].o_reset = reset[i];
		}
	}

	for (int i = 0; i < ID.size(); i++)
	{
		if (speed[i] == "slow")
		{
			_object[i].o_speed = 50;
		}
		else if (speed[i] == "normal")
		{
			_object[i].o_speed = 40;
		}
		else if (speed[i] == "fast")
		{
			_object[i].o_speed = 30;
		}
		else
		{
			_object[i].o_speed = 1000;
		}
	}
}


//================ Check game objects ======================

void update_GameObject(void)
{
	offsetTime += 5;

	for (short j = 0; j < 5; j++)
	{
		if (_object[j].o_ID == ">")					//check ID to send coord to specific "update" function for each obstacle
		{
			updateLR_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "<")
		{
			updateRL_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "v")
		{
			updateUD_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "^")
		{
			updateDU_Projectile(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "<O>")
		{
			updateLR_EBall(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_speed, _object[j].o_reset);
		}
		else if (_object[j].o_ID == "^Ov")
		{
			updateUD_EBall(_object[j].o_ID, _object[j].o_start_location, _object[j].o_location, _object[j].o_speed, _object[j].o_reset);
		}
	}
} 

//========= Update each object and its location ============

char LR_PString = '>';
void updateLR_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && (offsetTime % speed == 0))
	{
		xy.X++;
	}

	if (g_mapData.mapGrid[xy.Y][xy.X + 1] == (char)219)
	{
		ID = "<";
	}
	
	g_Console.writeToBuffer(xy, LR_PString, 0xF6);
}

char RL_PString = '<';
void updateRL_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && offsetTime % speed == 0)
	{
		xy.X--;
	}

	if (g_mapData.mapGrid[xy.Y + 1][xy.X -1] == (char)219)
	{
		ID = ">";
	}


	g_Console.writeToBuffer(xy, RL_PString, 0xF6);
}

char UD_PString = 'v';
void updateUD_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && offsetTime % speed == 0)
	{
		xy.Y++;
	}

	if (g_mapData.mapGrid[xy.Y][xy.X] == (char)219)
	{
		ID = "^";
	}

	g_Console.writeToBuffer(xy, UD_PString, 0xF6);
}

char DU_PString = '^';
void updateDU_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && offsetTime % speed == 0)
	{
		xy.Y--;
	}

	if (g_mapData.mapGrid[xy.Y - 2][xy.X] == (char)219)
	{
		ID = "v";
	}

	g_Console.writeToBuffer(xy, DU_PString, 0xF6);
}

string CrusherString = { (char)254 };
void updateLR_EBall(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reverse)
{
	if (reverse == false && offsetTime % speed == 0)
	{
		xy.X++;
		if (g_mapData.mapGrid[xy.Y - 1][xy.X] == (char)219)
		{
			reverse = true;
		}
	}
	if (reverse && offsetTime % speed == 0)
	{
		xy.X--;
		if (g_mapData.mapGrid[xy.Y - 1][xy.X - 1] == (char)219)
		{
			reverse = false;
		}
	}	
	g_Console.writeToBuffer(xy, CrusherString, 0xC3);
}

void updateUD_EBall(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reverse)
{
	if (reverse == false && offsetTime % speed == 0)
	{
		xy.Y++;
		if (g_mapData.mapGrid[xy.Y - 1][xy.X] == (char)219)
		{
			reverse = true;
		}
	}
	if (reverse && offsetTime % speed == 0)
	{
		xy.Y--;
		if (g_mapData.mapGrid[xy.Y - 2][xy.X - 1] == (char)219)
		{
			reverse = false;
		}
	}	
	g_Console.writeToBuffer(xy, CrusherString, 0xC3);
}

void findCoordStart(int newX, int newY)
{
	x.push_back(newX);
	y.push_back(newY);
}

int randomArr(int rand_vec_size)
{
	rand_vec_size = std::rand() % rand_vec_size;
	return rand_vec_size;
}