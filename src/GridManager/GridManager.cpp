#include "GridManager.hpp"

#include <SFML/Window/Event.hpp>

#include "../Grid/IGrid.hpp"

namespace Grid
{
	void GridManager::processEvent(sf::Event &event,
								   std::unique_ptr<IGrid>::pointer grid)
	{
		grid->processEvent(event);
	}

	void GridManager::processEvent(sf::Event &event, IGrid &grid)
	{
		grid.processEvent(event);
	}
}
