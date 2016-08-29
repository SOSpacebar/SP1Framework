#include "playerDetailsManager.h"

#include <fstream>

void saveFile(PlayerStats &_playerStats)
{

	//Save Files
	ofstream savefile("PlayerData/Data.txt");

	string tempSaveStorage[7];

	tempSaveStorage[0] = to_string(_playerStats.getPlayerLevel());
	tempSaveStorage[1] = to_string(_playerStats.getPlayerExp());
	tempSaveStorage[2] = to_string(_playerStats.getPlayerHealth());
	tempSaveStorage[3] = to_string(_playerStats.getPlayerMaxHealth());
	tempSaveStorage[4] = to_string(_playerStats.getPlayerAttack());
	tempSaveStorage[5] = to_string(_playerStats.getPlayerStr());
	tempSaveStorage[6] = to_string(_playerStats.getPlayerCon());


	for (int i = 0; i < 7; i++)
	{
		if (savefile.eof())
			break;

		savefile << tempSaveStorage[i] << endl;
	}
}