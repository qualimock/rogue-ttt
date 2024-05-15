#pragma once

#include "BaseGrid.hpp"

#include "../Entity/Actor/TTTCell.hpp"

namespace Grid
{
	class CombatGrid : public BaseGrid
	{
		Entity::TTTCell::Faction checkNeighbors(
			const std::pair<sf::Vector2i, Entity::Entity *> &origin,
			const sf::Vector2i &n1Offset,
			const sf::Vector2i &n2Offset);

	public:
		CombatGrid(const std::string &name,
				   const sf::Vector2i &topLeft,
				   const sf::Vector2i &bottomRight,
				   unsigned layer,
				   unsigned linesOffset);

		void clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition) override;

		Entity::TTTCell::Faction getWinner();
	};
}
