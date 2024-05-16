#pragma once

#include <memory>

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

		static void mouseClicked(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid);
		static void keyPressed(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid);
	};
}
