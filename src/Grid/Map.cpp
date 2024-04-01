#include "Map.hpp"

#include <iostream>

namespace Grid
{
	std::unique_ptr<Map> Map::map = nullptr;

	Map::Map(sf::RenderWindow &window)
		: BaseGrid(window, EGridType::Map, "map", sf::Vector2i(0, 0), sf::Vector2i(window.getSize()), 40)
	{}

	std::unique_ptr<Map>& Map::getMap(sf::RenderWindow &window)
	{
		if (map == nullptr)
		{
			map.reset(new Map(window));
		}
		return map;
	}

	Map::~Map() {}

	void Map::processEvent(sf::Event &event)
	{
		
	}
}
