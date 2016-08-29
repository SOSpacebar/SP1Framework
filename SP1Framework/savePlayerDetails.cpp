#include "playerDetailsManager.h"

#include <fstream>

void saveFile(PlayerStats &_playerStats)
{

	//Save Files
	ofstream savefile("PlayerData/Data.txt");

	string tempSaveStorage[11];

	//Getting each variable in the game.
	tempSaveStorage[0] = _playerStats.getPlayerName();
	tempSaveStorage[1] = to_string(_playerStats.getPlayerLevel());
	tempSaveStorage[2] = to_string(_playerStats.getPlayerExp());
	tempSaveStorage[3] = to_string(_playerStats.getPlayerNextLvlExp());
	tempSaveStorage[4] = to_string(_playerStats.getPlayerHealth());
	tempSaveStorage[5] = to_string(_playerStats.getPlayerMaxHealth());
	tempSaveStorage[6] = to_string(_playerStats.getPlayerAttack());
	tempSaveStorage[7] = to_string(_playerStats.getPlayerStr());
	tempSaveStorage[8] = to_string(_playerStats.getPlayerCon());
	tempSaveStorage[9] = to_string(_playerStats.getPlayerInt());
	tempSaveStorage[10] = to_string(_playerStats.getPlayerStatPoints());

	//Storing it into a text file.
	for (int i = 0; i < 11; i++)
	{
		if (savefile.eof())
			break;

		savefile << tempSaveStorage[i] << endl;
	}
}