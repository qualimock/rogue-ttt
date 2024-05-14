#pragma once

#include "BaseGrid.hpp"

#include <memory>

namespace Grid
{
	class Map : public BaseGrid
	{
		Map();

		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

	public:
		static Map& getMap();

		void move() = delete;
	};
}
