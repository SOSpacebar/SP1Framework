#ifndef _HEADERINCLUDES_H
#define _HEADERINCLUDES_H

#include <iostream>
#include <string>
#include "game.h"
#pragma once

typedef struct SMapData
{
	char mapGrid[150][150];
} SMapData;

typedef struct objectStruct
{
	string o_ID;
	int o_speed;
	COORD o_location;
	bool o_reset;
} objectStruct;

#endif