#pragma once

#include <memory>

#include "../Game/Game.hpp"

namespace sf {
	class Event;
	class RenderWindow;
}

namespace Grid
{
	class IGrid;
	class BaseGrid;

	class GridManager
	{

	public:
		GridManager() = delete;
		GridManager(const GridManager&) = delete;
		GridManager& operator=(const GridManager&) = delete;
		GridManager(GridManager&&) = delete;
		GridManager& operator=(GridManager&&) = delete;

		~GridManager() = default;

		static bool mouseClicked(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid);
		static bool moveEvent(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid);
	};
}
