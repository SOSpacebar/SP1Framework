#include "renderPlayerStatsScreen.h"

void renderPlayerStatsScreen(Console &g_Console, PlayerStats getPlayerStats)
{
	//char screen[150][150];

	COORD c = g_Console.getConsoleSize();
	c.X = c.X/2 - 9;
	c.Y = c.Y/3;

	//int level = 0, exp = 0, health = 0, maxHealth = 0, atk = 0, str = 0, con = 0;
	
	g_Console.writeToBuffer(c, "     Player Stats    ", 0x03);
	c.Y += 2;
	g_Console.writeToBuffer(c, "Level : " + std::to_string(getPlayerStats.getPlayerLevel()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Experience: " + std::to_string(getPlayerStats.getPlayerExp()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Health: " + std::to_string(getPlayerStats.getPlayerHealth()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Max Health: " + std::to_string(getPlayerStats.getPlayerMaxHealth()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Attack: " + std::to_string(getPlayerStats.getPlayerAttack()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Strenght: " + std::to_string(getPlayerStats.getPlayerStr()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Constitution: " + std::to_string(getPlayerStats.getPlayerCon()), 0x03);
	c.Y += 1;


	/*for (int y = 0; y < 150; y++)
	{
		for (int x = 0; x < 150; x++)
		{

		}
	}*/



}