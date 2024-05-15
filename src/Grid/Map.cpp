#include "Map.hpp"

#include <iostream>

namespace Grid
{
	Map::Map()
		: BaseGrid("map", EGridType::Map, sf::Vector2i(0, 0), sf::Vector2i(100, 100), 0, 40)
	{}

	Map& Map::getMap()
	{
		static Map instance;
		return instance;
	}

	Map* Map::getMapPointer()
	{
		static Map instance;
		return &instance;
	}
}
