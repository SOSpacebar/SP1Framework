#include "gameObject.h"
#include "Framework\console.h"
#include "portalGun.h"
#include <math.h>
#include <time.h>
#include <vector>

extern Console g_Console;
extern SMapData g_mapData;
extern SGameChar g_sChar;
extern Portal _portal;

int offsetTime = 0;

int objectIndex = 0;
short totalNumObject = 0;
//================ Check Level objects =====================

short x[20];
short y[20];
string ID[20];
string speed[20];
bool reset[20];

objectStruct _object[20];

void createObjectString()
{
	if (objectIndex > totalNumObject)
	{
		return;
	}

	string OID[8] = { ">", "<O>", "<", "^Ov", "v", "^", "<O>", "^Ov" };
	string Ospeed[3] = { "slow", "normal", "fast" };

	ID[objectIndex] = OID[randomArr(7)];
	speed[objectIndex] = Ospeed[randomArr(2)];
	reset[objectIndex] = false;

	objectIndex++;
}

void init_object(short level) //Preload the data of the enemy into memory.
{
	for (int i = 0; i < totalNumObject; i++)
	{
		createObjectString();
		COORD pos;
		pos.X = x[i];
		pos.Y = y[i];

		_object[i].o_location = pos;
		_object[i].o_ID = ID[i];
		_object[i].o_reset = reset[i];
	}

	for (int i = 0; i < totalNumObject; i++)
	{
		if (ID[i] == "<O>" || ID[i] == "^Ov")
		{
			_object[i].o_speed = 60;
		}
		else
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
}


//================ Check game objects ======================

void update_GameObject(void)
{
	offsetTime += 5;

	for (short j = 0; j < totalNumObject; j++)
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

	if (g_mapData.mapGrid[xy.Y][xy.X + 1] == (char)219 || g_mapData.mapGrid[xy.Y][xy.X + 1] == '+' || g_mapData.mapGrid[xy.Y][xy.X + 1] == '-')
	{
		ID = "<";
	}

	if ((sqrt((g_sChar.m_cLocation.X - xy.X)*(g_sChar.m_cLocation.X - xy.X) + ((g_sChar.m_cLocation.Y - xy.Y)*(g_sChar.m_cLocation.Y - xy.Y))) <= 8)||
		(sqrt((_portal.p_pos[0].X - xy.X)*(_portal.p_pos[0].X - xy.X) + ((_portal.p_pos[0].Y - xy.Y)*(_portal.p_pos[0].Y - xy.Y))) <= 3)			||
		(sqrt((_portal.p_pos[1].X - xy.X)*(_portal.p_pos[1].X - xy.X) + ((_portal.p_pos[1].Y - xy.Y)*(_portal.p_pos[1].Y - xy.Y))) <= 3)) 
	{
		g_Console.writeToBuffer(xy, LR_PString, 0x04);
	}
}

char RL_PString = '<';
void updateRL_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && offsetTime % speed == 0)
	{
		xy.X--;
	}

	if (g_mapData.mapGrid[xy.Y + 1][xy.X - 1] == (char)219 || g_mapData.mapGrid[xy.Y + 1][xy.X - 1] == '+' || g_mapData.mapGrid[xy.Y + 1][xy.X - 1] == '-')
	{
		ID = ">";
	}

	if ((sqrt((g_sChar.m_cLocation.X - xy.X)*(g_sChar.m_cLocation.X - xy.X) + ((g_sChar.m_cLocation.Y - xy.Y)*(g_sChar.m_cLocation.Y - xy.Y))) <= 8) ||
		(sqrt((_portal.p_pos[0].X - xy.X)*(_portal.p_pos[0].X - xy.X) + ((_portal.p_pos[0].Y - xy.Y)*(_portal.p_pos[0].Y - xy.Y))) <= 3) ||
		(sqrt((_portal.p_pos[1].X - xy.X)*(_portal.p_pos[1].X - xy.X) + ((_portal.p_pos[1].Y - xy.Y)*(_portal.p_pos[1].Y - xy.Y))) <= 3))
	{
		g_Console.writeToBuffer(xy, RL_PString, 0x04);
	}
}

char UD_PString = 'v';
void updateUD_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && offsetTime % speed == 0)
	{
		xy.Y++;
	}

	if (g_mapData.mapGrid[xy.Y][xy.X] == (char)219 || g_mapData.mapGrid[xy.Y][xy.X] == '+' || g_mapData.mapGrid[xy.Y][xy.X] == '-')
	{
		ID = "^";
	}

	if ((sqrt((g_sChar.m_cLocation.X - xy.X)*(g_sChar.m_cLocation.X - xy.X) + ((g_sChar.m_cLocation.Y - xy.Y)*(g_sChar.m_cLocation.Y - xy.Y))) <= 8) ||
		(sqrt((_portal.p_pos[0].X - xy.X)*(_portal.p_pos[0].X - xy.X) + ((_portal.p_pos[0].Y - xy.Y)*(_portal.p_pos[0].Y - xy.Y))) <= 3) ||
		(sqrt((_portal.p_pos[1].X - xy.X)*(_portal.p_pos[1].X - xy.X) + ((_portal.p_pos[1].Y - xy.Y)*(_portal.p_pos[1].Y - xy.Y))) <= 3))
	{
		g_Console.writeToBuffer(xy, UD_PString, 0x04);
	}
}

char DU_PString = '^';
void updateDU_Projectile(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reset)
{
	if (reset == false && offsetTime % speed == 0)
	{
		xy.Y--;
	}

	if (g_mapData.mapGrid[xy.Y - 2][xy.X] == (char)219 || g_mapData.mapGrid[xy.Y - 2][xy.X] == '+' || g_mapData.mapGrid[xy.Y - 2][xy.X] == '-')
	{
		ID = "v";
	}

	if ((sqrt((g_sChar.m_cLocation.X - xy.X)*(g_sChar.m_cLocation.X - xy.X) + ((g_sChar.m_cLocation.Y - xy.Y)*(g_sChar.m_cLocation.Y - xy.Y))) <= 8) ||
		(sqrt((_portal.p_pos[0].X - xy.X)*(_portal.p_pos[0].X - xy.X) + ((_portal.p_pos[0].Y - xy.Y)*(_portal.p_pos[0].Y - xy.Y))) <= 3) ||
		(sqrt((_portal.p_pos[1].X - xy.X)*(_portal.p_pos[1].X - xy.X) + ((_portal.p_pos[1].Y - xy.Y)*(_portal.p_pos[1].Y - xy.Y))) <= 3))
	{
		g_Console.writeToBuffer(xy, DU_PString, 0x04);
	}
}

string CrusherString = { (char)233 };
void updateLR_EBall(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reverse)
{
	if (reverse == false && offsetTime % speed == 0)
	{
		if (g_mapData.mapGrid[xy.Y - 1][xy.X + 1] == (char)219 || g_mapData.mapGrid[xy.Y - 1][xy.X + 1] == '-')
		{
			reverse = true;
			xy.X--;
		}
		xy.X++;
	}

	if (reverse && offsetTime % speed == 0)
	{
		if (g_mapData.mapGrid[xy.Y - 1][xy.X - 1] == (char)219 || g_mapData.mapGrid[xy.Y - 1][xy.X - 1] == '-')
		{
			reverse = false;
			xy.X++;
		}
		xy.X--;
	}

	if ((sqrt((g_sChar.m_cLocation.X - xy.X)*(g_sChar.m_cLocation.X - xy.X) + ((g_sChar.m_cLocation.Y - xy.Y)*(g_sChar.m_cLocation.Y - xy.Y))) <= 8) ||
		(sqrt((_portal.p_pos[0].X - xy.X)*(_portal.p_pos[0].X - xy.X) + ((_portal.p_pos[0].Y - xy.Y)*(_portal.p_pos[0].Y - xy.Y))) <= 3) ||
		(sqrt((_portal.p_pos[1].X - xy.X)*(_portal.p_pos[1].X - xy.X) + ((_portal.p_pos[1].Y - xy.Y)*(_portal.p_pos[1].Y - xy.Y))) <= 3))
	{
		g_Console.writeToBuffer(xy, CrusherString, 0xCF);
	}
	checkEBallCollsionWithPortal(xy, _portal);
}

void updateUD_EBall(string &ID, COORD &start_xy, COORD &xy, int &speed, bool &reverse)
{
	if (reverse == false && offsetTime % speed == 0)
	{
		if (g_mapData.mapGrid[xy.Y][xy.X] == (char)219 || g_mapData.mapGrid[xy.Y][xy.X] == '-')
		{
			reverse = true;
			xy.Y--;
		}
		xy.Y++;
	}

	if (reverse && offsetTime % speed == 0)
	{
		if (g_mapData.mapGrid[xy.Y - 2][xy.X] == (char)219 || g_mapData.mapGrid[xy.Y - 2][xy.X] == '-')
		{
			reverse = false;
			xy.Y++;
		}
		xy.Y--;
	}

	if ((sqrt((g_sChar.m_cLocation.X - xy.X)*(g_sChar.m_cLocation.X - xy.X) + ((g_sChar.m_cLocation.Y - xy.Y)*(g_sChar.m_cLocation.Y - xy.Y))) <= 8) ||
		(sqrt((_portal.p_pos[0].X - xy.X)*(_portal.p_pos[0].X - xy.X) + ((_portal.p_pos[0].Y - xy.Y)*(_portal.p_pos[0].Y - xy.Y))) <= 3) ||
		(sqrt((_portal.p_pos[1].X - xy.X)*(_portal.p_pos[1].X - xy.X) + ((_portal.p_pos[1].Y - xy.Y)*(_portal.p_pos[1].Y - xy.Y))) <= 3))
	{
		g_Console.writeToBuffer(xy, CrusherString, 0xCF);
	}
	checkEBallCollsionWithPortal(xy, _portal);
}

void findCoordStart(int newX, int newY)
{
	x[totalNumObject] = newX;
	y[totalNumObject] = newY;
}

int randomArr(int rand_vec_size)
{
		std::random_device randNew;
		std::mt19937 twistNew(randNew());

		std::uniform_int_distribution<> dist(0, rand_vec_size - 1);
		return dist(twistNew);
}