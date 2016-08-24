#ifndef _MAPGENERATOR_H
#define _MAPGENERATOR_H

#include <random>
#include <vector>
#include <iostream>
#include "game.h"

namespace
{
	std::random_device rand;
	std::mt19937 twist(rand());

	int randomInt(int exclusiveMax)
	{
		std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
		return dist(twist);
	}

	int randomInt(int min, int max)
	{
		std::uniform_int_distribution<> dist(0, max - min);
		return dist(twist) + min;
	}

	bool randomBool(double probability = 0.5)
	{
		std::bernoulli_distribution dist(probability);
		return dist(twist);
	}
}

struct Rect
{
	int x, y;
	int width, height;
};

void returnMap();

#endif