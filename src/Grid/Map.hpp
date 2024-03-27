#pragma once

#include "BaseGrid.hpp"

#include <memory>

namespace Grid
{
	class Map : public BaseGrid
	{
		Map(sf::RenderWindow &window);

		static std::unique_ptr<Map> map;

	public:
		~Map();

		static std::unique_ptr<Map>& getMap(sf::RenderWindow &window);

		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;
		Map(Map&&) = delete;
		Map& operator=(Map&&) = delete;

		void processEvent(sf::Event &event) override;
		void move() = delete;
	};
}
