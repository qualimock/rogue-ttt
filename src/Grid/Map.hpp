#pragma once

#include "IGrid.hpp"

#include <memory>

namespace Grid
{
	class Map : public IGrid
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

		void processEvents(sf::Event event) override;
		void update() override;
	};
}
