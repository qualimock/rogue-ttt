#pragma once

#include "BaseGrid.hpp"

namespace Grid
{
	class CombatGrid : public BaseGrid
	{
		Cell::Faction checkNeighbors(const std::pair<sf::Vector2i, Cell> &origin,
									 const sf::Vector2i &n1Offset,
									 const sf::Vector2i &n2Offset);

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
