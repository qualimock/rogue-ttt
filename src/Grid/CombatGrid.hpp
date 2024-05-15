#pragma once

#include "BaseGrid.hpp"

namespace Grid
{
	class CombatGrid : public BaseGrid
	{
	public:
		CombatGrid(const std::string &name,
				   const sf::Vector2i &topLeft,
				   const sf::Vector2i &bottomRight,
				   unsigned layer,
				   unsigned linesOffset);

		void clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition) override;

		Cell::Faction getWinner();
	};
}
