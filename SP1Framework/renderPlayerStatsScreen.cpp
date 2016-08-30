#include "renderPlayerStatsScreen.h"

void renderPlayerStatsScreen(Console &g_Console, PlayerStats &getPlayerStats, Inventory &_inventory, Equipment &equip)
{
	_inventory.debugPrint(equip, _inventory);

	COORD c = g_Console.getConsoleSize();
	c.X = 0;
	c.Y = 2;
	
	g_Console.writeToBuffer(c, "======================================================Player Stats======================================================", 0x03);
	c.Y += 2;
	c.X = 50;
	g_Console.writeToBuffer(c, "Name : " + getPlayerStats.getPlayerName(), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Level : " + std::to_string(getPlayerStats.getPlayerLevel()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Experience: " + std::to_string(getPlayerStats.getPlayerExp()) + "/" + std::to_string(getPlayerStats.getPlayerNextLvlExp()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Health: " + std::to_string(getPlayerStats.getPlayerHealth()) + "/" + std::to_string(getPlayerStats.getPlayerMaxHealth()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Mana: " + std::to_string(getPlayerStats.getPlayerMana()) + "/" + std::to_string(getPlayerStats.getPlayerMaxMana()), 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Attack: " + std::to_string(getPlayerStats.getPlayerAttack()), 0x03);
	c.Y += 1;
	if (getPlayerStats.getPlayerStatPoints() < 1)
	{
		g_Console.writeToBuffer(c, "Strenght: " + std::to_string(getPlayerStats.getPlayerStr()), 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, "Constitution: " + std::to_string(getPlayerStats.getPlayerCon()), 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, "Intelligence: " + std::to_string(getPlayerStats.getPlayerInt()), 0x03);
		c.Y += 1;
	}
	else
	{
		g_Console.writeToBuffer(c, "Strenght: " + std::to_string(getPlayerStats.getPlayerStr()) + "+", 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, "Constitution: " + std::to_string(getPlayerStats.getPlayerCon()) + "+", 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, "Intelligence: " + std::to_string(getPlayerStats.getPlayerInt()) + "+", 0x03);
		c.Y += 1;
	}
	g_Console.writeToBuffer(c, "Stats Point: " + std::to_string(getPlayerStats.getPlayerStatPoints()), 0x03);
}