#pragma once

#include "BaseGrid.hpp"

#include "../Entity/Actor/TTTCell.hpp"

namespace Grid
{
	class CombatGrid : public BaseGrid
	{
		Entity::TTTCell::Faction checkNeighbors(
			const std::pair<sf::Vector2i, std::shared_ptr<Entity::Entity>> &origin,
			const sf::Vector2i &n1Offset,
			const sf::Vector2i &n2Offset);

	public:
		CombatGrid(BaseGrid &&grid);

		bool clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition) override;

		Entity::TTTCell::Faction getWinner();

		void AI_Move();

		bool IsOccupied(std::pair<sf::Vector2i, sf::Vector2i> pos);

		int UsedCells;
	};
}
