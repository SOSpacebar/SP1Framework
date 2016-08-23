#include "PathfindingAI.h"

extern Console g_Console;

Sectors CheckSector;
int SectorIndex[8];

short prevCoordX[8];
short prevCoordY[8];
float CheckWithinRadius = 9;

//COORD DirectionArray[8];

void scanSectorForPlayer(SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy)
{
	double MagitudeDist;

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

	SectorIndex[indexEnemy] = 0;
}

void scanTiles(SMapData mapData, SGameChar _sChar, enemyStruct _enemy[], int totalEnemy, int indexEnemy)
{
	double MagitudeDist;
	MagitudeDist = sqrt(((_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)*(_sChar.m_cLocation.X - _enemy[indexEnemy].e_location.X)) + ((_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)*(_sChar.m_cLocation.Y - _enemy[indexEnemy].e_location.Y)));

	if (MagitudeDist <= CheckWithinRadius)
	{
		if (CheckSector == Up)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 2][_enemy[indexEnemy].e_location.X] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 2][_enemy[indexEnemy].e_location.X] != '-') &&
				(_enemy[indexEnemy].e_location.Y - 1 != prevCoordY[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.Y--;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = UpRight;
			}
		}

		if (CheckSector == UpRight)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 2][_enemy[indexEnemy].e_location.X + 1] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 2][_enemy[indexEnemy].e_location.X + 1] != '-') &&
				(_enemy[indexEnemy].e_location.Y - 1 != prevCoordY[indexEnemy]) &&
				(_enemy[indexEnemy].e_location.X + 1 != prevCoordX[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.Y--;
				_enemy[indexEnemy].e_location.X++;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = Right;
			}
		}

		if (CheckSector == Right)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 1][_enemy[indexEnemy].e_location.X + 1] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 1][_enemy[indexEnemy].e_location.X + 1] != '-') &&
				(_enemy[indexEnemy].e_location.X + 1 != prevCoordX[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.X++;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = BtmRight;
			}
		}

		if (CheckSector == BtmRight)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y][_enemy[indexEnemy].e_location.X + 1] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y][_enemy[indexEnemy].e_location.X + 1] != '-') &&
				(_enemy[indexEnemy].e_location.X + 1 != prevCoordX[indexEnemy]) &&
				(_enemy[indexEnemy].e_location.Y + 1 != prevCoordY[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.X++;
				_enemy[indexEnemy].e_location.Y++;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = Down;
			}
		}

		if (CheckSector == Down)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y][_enemy[indexEnemy].e_location.X] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y][_enemy[indexEnemy].e_location.X] != '-') &&
				(_enemy[indexEnemy].e_location.Y + 1 != prevCoordY[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.Y++;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = BtmLeft;
			}
		}

		if (CheckSector == BtmLeft)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y][_enemy[indexEnemy].e_location.X - 1] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y][_enemy[indexEnemy].e_location.X - 1] != '-') &&
				(_enemy[indexEnemy].e_location.X - 1 != prevCoordX[indexEnemy]) &&
				(_enemy[indexEnemy].e_location.Y + 1 != prevCoordY[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.Y++;
				_enemy[indexEnemy].e_location.X--;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = Left;
			}
		}

		if (CheckSector == Left)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 1][_enemy[indexEnemy].e_location.X - 1] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 1][_enemy[indexEnemy].e_location.X - 1] != '-') &&
				(_enemy[indexEnemy].e_location.X - 1) != prevCoordX[indexEnemy])
			{
				_enemy[indexEnemy].e_location.X--;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = UpLeft;
			}
		}

		if (CheckSector == UpLeft)
		{
			if ((mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 2][_enemy[indexEnemy].e_location.X - 1] != (char)219) &&
				(mapData.mapGrid[_enemy[indexEnemy].e_location.Y - 2][_enemy[indexEnemy].e_location.X - 1] != '-') &&
				(_enemy[indexEnemy].e_location.X - 1 != prevCoordX[indexEnemy]) &&
				(_enemy[indexEnemy].e_location.Y - 1 != prevCoordY[indexEnemy]))
			{
				_enemy[indexEnemy].e_location.X--;
				_enemy[indexEnemy].e_location.Y--;
				prevCoordX[indexEnemy] = _enemy[indexEnemy].e_location.X;
				prevCoordY[indexEnemy] = _enemy[indexEnemy].e_location.Y;
			}
			else
			{
				if (SectorIndex[indexEnemy] == 8)
				{
					SectorIndex[indexEnemy] = 0;
					prevCoordX[indexEnemy] = 0;
					prevCoordY[indexEnemy] = 0;
					return;
				}
				SectorIndex[indexEnemy]++;
				CheckSector = Up;
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
	//compareTiles(_sChar, _enemy, totalEnemy, indexEnemy);
	scanTiles(mapData, _sChar, _enemy, totalEnemy, indexEnemy);
}