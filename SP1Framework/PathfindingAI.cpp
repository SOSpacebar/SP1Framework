#include "PathfindingAI.h"

extern Console g_Console;

Sectors CheckSector;
string CheckIndex;

double Check1;
double Check2;
double Check3;
short CheckWithinRadius = 15;

COORD DirectionArray[8];

void scanSectorForPlayer(SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy)
{
	float MagitudeDist;

	short charX;
	short charY;
	short enemyX;
	short enemyY;

	charX = _sChar.m_cLocation.X;
	charY = _sChar.m_cLocation.Y;
	enemyX = _enemy[indexEnemy].e_location.X;
	enemyY = _enemy[indexEnemy].e_location.Y;

	MagitudeDist = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)));

	if (MagitudeDist <= CheckWithinRadius)
	{
		if ((charX == enemyX) && (charY < enemyY))
		{
			CheckSector = Up;
		}
		if ((charX > enemyX) && (charY < enemyY))
		{
			CheckSector = UpRight;
		}
		if ((charX > enemyX) && (charY == enemyY))
		{
			CheckSector = Right;
		}
		if ((charX > enemyX) && (charY > enemyY))
		{
			CheckSector = BtmRight;
		}
		if ((charX == enemyX) && (charY > enemyY))
		{
			CheckSector = Down;
		}
		if ((charX < enemyX) && (charY > enemyY))
		{
			CheckSector = BtmLeft;
		}
		if ((charX < enemyX) && (charY == enemyY))
		{
			CheckSector = Left;
		}
		if ((charX < enemyX) && (charY < enemyY))
		{
			CheckSector = UpLeft;
		}		
	}
}

void scanTiles(SMapData mapData, SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy)
{
	char MapGridData = mapData.mapGrid[_enemy[indexEnemy].e_location.X][_enemy[indexEnemy].e_location.Y - 2];

	if (sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y))) <= CheckWithinRadius)
	{
		if (CheckSector == UpperLeft)
		{
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X - 1][_enemy[indexEnemy].e_location.Y - 2] != (char)219 && CheckIndex == "Check1")
			{
				//move or update location
				_enemy[indexEnemy].e_location.X--;
				_enemy[indexEnemy].e_location.Y--;
			}
			if ((MapGridData != -37) && (CheckIndex == "Check2") )
			{
				//move  or update location
				_enemy[indexEnemy].e_location.Y--;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X - 1][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check3")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.X--;
			}
		}

		else if (CheckSector == UpperRight)
		{
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X + 1][_enemy[indexEnemy].e_location.Y - 2] != (char)219 && CheckIndex == "Check1")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.X++;
				_enemy[indexEnemy].e_location.Y--;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X][_enemy[indexEnemy].e_location.Y - 2] != (char)219 && CheckIndex == "Check2")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.Y--;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X + 1][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check3")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.X++;
			}
		}

		else if (CheckSector == BtmRight)
		{
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X + 1][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check1")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.X++;
				_enemy[indexEnemy].e_location.Y++;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check2")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.Y++;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X + 1][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check3")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.X++;
			}
		}

		else if (CheckSector == BtmLeft)
		{
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X - 1][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check1")
			{
				//move or update location
				_enemy[indexEnemy].e_location.X--;
				_enemy[indexEnemy].e_location.Y++;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check2")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.Y++;
			}
			if (mapData.mapGrid[_enemy[indexEnemy].e_location.X - 1][_enemy[indexEnemy].e_location.Y] != (char)219 && CheckIndex == "Check3")
			{
				//move  or update location
				_enemy[indexEnemy].e_location.X--;
			}
		}
	}
}

void compareTiles(SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy)
{
	if (CheckSector == Up)
	{

	}
	/*if (CheckSector == Up)
	{

	}
	if (CheckSector == UpperLeft)
	{
		Check1 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)));
		Check2 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)));
		Check3 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)));

		if (Check1 <= Check2)
		{
			if (Check3 >= Check2)
			{
				CheckIndex = "Check1";
			}
			else if (Check3 <= Check1)
			{
				CheckIndex = "Check3";
			}
		}
		else
		{
			if (Check2 <= Check3)
			{
				CheckIndex = "Check2";
			}
			else
			{
				CheckIndex = "Check3";
			}
		}
	}
	else if (CheckSector == UpperRight)
	{
		Check1 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)));
		Check2 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y - 1)));
		Check3 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)));

		if (Check1 <= Check2)
		{
			if (Check3 >= Check2)
			{
				CheckIndex = "Check1";
			}
			else if (Check3 <= Check1)
			{
				CheckIndex = "Check3";
			}
		}
		else
		{
			if (Check2 <= Check3)
			{
				CheckIndex = "Check2";
			}
			else
			{
				CheckIndex = "Check3";
			}
		}
	}
	else if (CheckSector == BtmRight)
	{
		Check1 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)));
		Check2 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)));
		Check3 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X + 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)));

		if (Check1 <= Check2)
		{
			if (Check3 >= Check2)
			{
				CheckIndex = "Check1";
			}
			else if (Check3 <= Check1)
			{
				CheckIndex = "Check3";
			}
		}
		else
		{
			if (Check2 <= Check3)
			{
				CheckIndex = "Check2";
			}
			else
			{
				CheckIndex = "Check3";
			}
		}
	}
	else if (CheckSector == BtmLeft)
	{
		Check1 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)));
		Check2 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y + 1)));
		Check3 = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X - 1)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)));

		if (Check1 <= Check2)
		{
			if (Check3 >= Check2)
			{
				CheckIndex = "Check1";
			}
			else if (Check3 <= Check1)
			{
				CheckIndex = "Check3";
			}
		}
		else
		{
			if (Check2 <= Check3)
			{
				CheckIndex = "Check2";
			}
			else
			{
				CheckIndex = "Check3";
			}
		}
	}*/
}

void moveAI(SMapData mapData, SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy)
{
	scanSectorForPlayer(_sChar, _enemy, totalEnemy, indexEnemy);
	compareTiles(_sChar, _enemy, totalEnemy, indexEnemy);
	scanTiles(mapData, _sChar, _enemy, totalEnemy, indexEnemy);
}