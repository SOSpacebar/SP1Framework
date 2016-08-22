#include "MapGenerator.h"
#include "ReadMap.h"
#include "game.h"
#include "gameObject.h"
#include "enemyProperties.h"

extern SMapData g_mapData;
extern SGameChar g_sChar;
extern short totalNumObject;

int i = 0;

class MapGenerator
{
public:
	enum Tiles
	{
		Unused = '.',
		Floor = ' ',
		Corridor = ',',
		Wall = (char)219,
		BreakDoor = '+',
		PortalDoor = '-',
		Endpoint = 'E',
		Startpoint = 'S',
		Spike = '^',
		Key = 'K',
		EndKey = 'Q',
		Monster = 'm',
		EnergyBall = '*'
	};

	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

public:
	MapGenerator(int width, int height) :
		_width(width),
		_height(height),
		_tiles(width * height, Unused),
		_rooms(),
		_exit()
	{
	}

	void generate(int maxItems)
	{
		if (!makeRoom(_width / 2, _height / 2, static_cast<Direction>(randomInt(4), true)))
		{
			//unable to make room
			return;
		}

		for (int x = 1; x < maxItems; ++x)
		{
			if (!createItems())
			{
				//unable to create item
				break;
			}
		}

		if (!placeObject(Startpoint))
		{
			//std::cout << "Unable to place up stairs.\n";
			return;
		}

		if (!placeObject(Endpoint))
		{
			//std::cout << "Unable to place down stairs.\n";
			return;
		}

		if (!placeObject(EndKey))
		{
			//std::cout << "Unable to place down stairs.\n";
			return;
		}


		//for (int x = 1; x < 9; ++x)
		//{
		//	if (!placeObject(Spike))
		//	{
		//		//std::cout << "Unable to place down stairs.\n";
		//		break;
		//	}
		//}

		for (int x = 1; x < 9; ++x)
		{
			if (!placeObject(Key))
			{
				//std::cout << "Unable to place down stairs.\n";
				break;
			}
		}

		for (int x = 1; x < 9; ++x)
		{
			if (!placeObject(Monster))
			{
				//std::cout << "Unable to place down stairs.\n";
				break;
			}
		}
		
		for (int x = 1; x < 9; ++x)
		{
			if (!placeObject(EnergyBall))
			{
				//std::cout << "Unable to place down stairs.\n";
				break;
			}
		}

		for (char& tile : _tiles)
		{
			if (tile == Floor || tile == Corridor || tile == Unused)
				tile = ' ';
		}
	}

	void saveToArr() //save the generated map into my mapGrid
	{
		for (int y = 0; y < _height; ++y)
		{
			for (int x = 0; x < _width; ++x)
			{
				if (getTiles(x, y) == 'S')
				{
					g_sChar.m_cLocation.X = x;
					g_sChar.m_cLocation.Y = y + 1;
					g_mapData.mapGrid[y][x] = getTiles(x, y);
				}
				else if (getTiles(x, y) == '*')
				{
					findCoordStart(x, y);
					totalNumObject++;
					g_mapData.mapGrid[y][x] = ' ';
				}
				else if (getTiles(x, y) == 'm')
				{
					enemyCoordStart(x, y, i);
					i++;
					g_mapData.mapGrid[y][x] = ' ';
				}
				else
				{
					g_mapData.mapGrid[y][x] = getTiles(x, y);
				}
			}
		}
	}

private:
	char getTiles(int x, int y) const
	{
		if (x < 0 || y < 0 || x >= _width || y >= _height)
		{
			return Unused;
			//set tiles to unused if hit limits
		}

		return _tiles[x + y * _width];
	}

	void setTiles(int x, int y, char tile)
	{
		_tiles[x + y * _width] = tile;
	}

	bool createItems() //create how many rooms or doors or spikes
	{
		for (int i = 0; i < 1000; ++i)
		{
			if (_exit.empty())
			{
				break;
			}

			// choose a random side of a random room or corridor
			int r = randomInt(_exit.size());
			int x = randomInt(_exit[r].x, _exit[r].x + _exit[r].width - 1);
			int y = randomInt(_exit[r].y, _exit[r].y + _exit[r].height - 1);

			for (int j = 0; j < DirectionCount; ++j)
			{
				if (createItems(x, y, static_cast<Direction>(j)))
				{
					_exit.erase(_exit.begin() + r);
					return true;
				}
			}
		}

		return false;
	}

	bool createItems(int x, int y, Direction dir)
	{
		static const int roomChance = 50;

		int dx = 0;
		int dy = 0;

		if (dir == North)
		{
			dy = 1;
		}
		else if (dir == South)
		{
			dy = -1;
		}
		else if (dir == West)
		{
			dx = 1;
		}
		else if (dir == East)
		{
			dx = -1;
		}

		if (getTiles(x + dx, y + dy) != Floor && getTiles(x + dx, y + dy) != Corridor)
		{
			return false;
		}

		if (randomInt(100) < roomChance)
		{
			if (makeRoom(x, y, dir))
			{
				//create breakable door
				setTiles(x, y, PortalDoor);

				return true;
			}
		}

		else
		{
			if (makeCorridor(x, y, dir))
			{
				if (getTiles(x + dx, y + dy) == Floor)
				{
					//create breakable door
					setTiles(x, y, BreakDoor);
				}
				else
				{
					setTiles(x, y, Corridor);
					return true;
				}
			}

			return false;
		}
	}

	bool makeRoom(int x, int y, Direction dir, bool firstRoom = false)
	{
		//define fixed room size
		static const int minRoomSize = 3;
		static const int maxRoomSize = 10;

		//create a random room size within the fixed sized
		Rect room;
		room.width = randomInt(minRoomSize, maxRoomSize);
		room.height = randomInt(minRoomSize, maxRoomSize);

		if (dir == North)
		{
			room.x = x - room.width / 2;
			room.y = y - room.height;
		}

		else if (dir == South)
		{
			room.x = x - room.width / 2;
			room.y = y + 1;
		}

		else if (dir == West)
		{
			room.x = x - room.width;
			room.y = y - room.height / 2;
		}

		else if (dir == East)
		{
			room.x = x + 1;
			room.y = y - room.height / 2;
		}

		if (placeRect(room, Floor))
		{
			_rooms.emplace_back(room);

			if (dir != South || firstRoom) // north side
				_exit.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
			if (dir != North || firstRoom) // south side
				_exit.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
			if (dir != East || firstRoom) // west side
				_exit.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
			if (dir != West || firstRoom) // east side
				_exit.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

			return true;
		}

		return false;
	}

	bool makeCorridor(int x, int y, Direction dir)
	{
		static const int minCorridorLength = 3;
		static const int maxCorridorLength = 10;

		Rect corridor;
		corridor.x = x;
		corridor.y = y;

		if (randomBool()) // horizontal corridor
		{
			corridor.width = randomInt(minCorridorLength, maxCorridorLength);
			corridor.height = 2;

			if (dir == North)
			{
				corridor.y = y - 1;

				if (randomBool()) // west
					corridor.x = x - corridor.width + 1;
			}

			else if (dir == South)
			{
				corridor.y = y + 1;

				if (randomBool()) // west
					corridor.x = x - corridor.width + 1;
			}

			else if (dir == West)
				corridor.x = x - corridor.width;

			else if (dir == East)
				corridor.x = x + 1;
		}

		else // vertical corridor
		{
			corridor.width = 2;
			corridor.height = randomInt(minCorridorLength, maxCorridorLength);

			if (dir == North)
				corridor.y = y - corridor.height;

			else if (dir == South)
				corridor.y = y + 1;

			else if (dir == West)
			{
				corridor.x = x - 1;

				if (randomBool()) // north
					corridor.y = y - corridor.height + 1;
			}

			else if (dir == East)
			{
				corridor.x = x + 1;

				if (randomBool()) // north
					corridor.y = y - corridor.height + 1;
			}
		}

		if (placeRect(corridor, Corridor))
		{
			if (dir != South && corridor.width != 1) // north side
				_exit.emplace_back(Rect{ corridor.x, corridor.y - 1, corridor.width, 1 });
			if (dir != North && corridor.width != 1) // south side
				_exit.emplace_back(Rect{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
			if (dir != East && corridor.height != 1) // west side
				_exit.emplace_back(Rect{ corridor.x - 1, corridor.y, 1, corridor.height });
			if (dir != West && corridor.height != 1) // east side
				_exit.emplace_back(Rect{ corridor.x + corridor.width, corridor.y, 1, corridor.height });

			return true;
		}

		return false;
	}

	bool placeRect(const Rect& rect, char tile)
	{
		if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > _width - 1 || rect.y + rect.height > _height - 1)
			return false;

		for (int y = rect.y; y < rect.y + rect.height; ++y)
			for (int x = rect.x; x < rect.x + rect.width; ++x)
			{
				if (getTiles(x, y) != Unused)
					return false; // the area already used
			}

		for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
			for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
			{
				if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
					setTiles(x, y, Wall);
				else
					setTiles(x, y, tile);
			}

		return true;
	}

	bool placeObject(char tile)
	{
		if (_rooms.empty())
			return false;

		int r = randomInt(_rooms.size()); // choose a random room
		int x = randomInt(_rooms[r].x + 1, _rooms[r].x + _rooms[r].width - 2);
		int y = randomInt(_rooms[r].y + 1, _rooms[r].y + _rooms[r].height - 2);

		if (getTiles(x, y) == Floor)
		{
			setTiles(x, y, tile);

			// place one object in one room (optional)
			_rooms.erase(_rooms.begin() + r);

			return true;
		}
		
		if (getTiles(x, y) == PortalDoor)
		{
			setTiles(x, y, Key);

			// place one object in one room (optional)
			_rooms.erase(_rooms.begin() + r);

			return true;
		}
		return false;
	}

private:
	int _width, _height;
	std::vector<char> _tiles;
	std::vector<Rect> _rooms; // rooms for place stairs or monsters
	std::vector<Rect> _exit; // 4 sides of rooms or corridors
};

void returnMap()
{
	MapGenerator map(115, 35);
	map.generate(200);
	map.saveToArr();
}