#include "playerDetailsManager.h"

#include <fstream>

void loadFile(PlayerStats &_playerStats)
{
	ifstream playerData ("PlayerData/Data.txt");

	int tempStorage[7];
	string temp;

	for (int i = 0; i < 7; i++)
	{
		if (playerData.eof())
			break;

		getline(playerData, temp);
		tempStorage[i] = atoi(temp.c_str());
	}

	_playerStats.setPlayerStats(tempStorage[0], tempStorage[1], tempStorage[2], tempStorage[3], tempStorage[4], tempStorage[5], tempStorage[6]);
}