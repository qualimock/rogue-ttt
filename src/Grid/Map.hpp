#pragma once

#include "IGrid.hpp"

namespace Grid
{
	class Map : public IGrid
	{
	public:
		Map(sf::RenderWindow &window);
		~Map();

		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;
		Map& operator=(Map&&) = delete;
		Map(Map&&) = delete;

		void processEvents(sf::Event event) override;
		void update() override;
	};
}
