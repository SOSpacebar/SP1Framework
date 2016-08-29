#include "playerDetailsManager.h"

#include <fstream>

void loadFile(PlayerStats &_playerStats)
{
	ifstream playerData ("PlayerData/Data.txt");

	string nameTemp;
	int tempStorage[10];
	string temp;

	//Load the name.
	getline(playerData, temp);
	nameTemp = temp;

	//Load Other Variables.
	for (int i = 0; i < 10; i++)
	{
		if (playerData.eof())
			break;

		getline(playerData, temp);
		tempStorage[i] = atoi(temp.c_str());
	}

	_playerStats.setPlayerStats(nameTemp, tempStorage[0], tempStorage[1], tempStorage[2], tempStorage[3], tempStorage[4], tempStorage[5], tempStorage[6], tempStorage[7], tempStorage[8], tempStorage[9]);
}