#include "GridManager.hpp"

#include <SFML/Window/Event.hpp>

#include "../Grid/BaseGrid.hpp"

#include <iostream>

namespace Grid
{
	void GridManager::processEvent(sf::Event &event, Grid::BaseGrid &grid)
	{
		std::cout << grid.name() << std::endl;
	}
}
