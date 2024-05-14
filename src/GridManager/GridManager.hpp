#pragma once

#include <memory>

namespace sf {
	class Event;
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

		static void processEvent(sf::Event &event, std::unique_ptr<IGrid>::pointer grid);
		static void processEvent(sf::Event &event, BaseGrid &grid);
	};
}
