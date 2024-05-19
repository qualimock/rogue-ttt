#include "CombatGrid.hpp"

#include <iostream>

namespace Grid
{
	CombatGrid::CombatGrid(BaseGrid &&grid)
		: BaseGrid(grid)
	{}

	Entity::TTTCell::Faction CombatGrid::checkNeighbors(const std::pair<sf::Vector2i, Entity::Entity *> &origin,
														const sf::Vector2i &n1Offset,
														const sf::Vector2i &n2Offset)
	{
		Entity::Entity *n1 = nullptr;
		Entity::Entity *n2 = nullptr;

		for (auto &entity : m_entities)
		{
			if (entity.second->index() == origin.first + n1Offset)
			{
				n1 = entity.second;
			}
			if (entity.second->index() == origin.first + n2Offset)
			{
				n2 = entity.second;
			}
		}

		Entity::TTTCell::Faction neighboursFaction = Entity::TTTCell::Faction::None;

		if (n1 && n2)
		{
			if (dynamic_cast<Entity::TTTCell *>(n1)->faction() ==
				dynamic_cast<Entity::TTTCell *>(n2)->faction())
			{
				neighboursFaction = dynamic_cast<Entity::TTTCell *>(n1)->faction();
			}

			if (neighboursFaction == dynamic_cast<Entity::TTTCell *>(origin.second)->faction())
			{
				return dynamic_cast<Entity::TTTCell *>(origin.second)->faction();
			}
		}

		return Entity::TTTCell::Faction::None;
	}

	Entity::TTTCell::Faction CombatGrid::getWinner()
	{
		for (auto &entity : m_entities)
		{
			if (checkNeighbors(std::make_pair(entity.second->index(), entity.second),
							   sf::Vector2i(1, 1), sf::Vector2i(-1, -1)) != Entity::TTTCell::Faction::None)
			{
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}

			if	(checkNeighbors(std::make_pair(entity.second->index(), entity.second),
								sf::Vector2i(-1, 1), sf::Vector2i(1, -1)) != Entity::TTTCell::Faction::None)
			{
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}

			if (checkNeighbors(std::make_pair(entity.second->index(), entity.second),
							   sf::Vector2i(0, 1), sf::Vector2i(0, -1)) != Entity::TTTCell::Faction::None)
			{
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}

			if(checkNeighbors(std::make_pair(entity.second->index(), entity.second),
							  sf::Vector2i(1, 0), sf::Vector2i(-1, 0)) != Entity::TTTCell::Faction::None)
			{
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}
		}

		return Entity::TTTCell::Faction::None;
	}

	bool CombatGrid::clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition)
	{
		auto cellIndexPosition = adjustEntityPosition(mousePosition);
		Entity::TTTCell::Faction clickFaction;
		Entity::TTTCell::Faction winnerFaction;

		std::cout << "COMBAT" << std::endl;

		std::cout << position().x << ":" << position().y << std::endl;

		switch (button)
		{
		case sf::Mouse::Left:
			clickFaction = Entity::TTTCell::Faction::Cross;
			break;

		case sf::Mouse::Right:
			clickFaction = Entity::TTTCell::Faction::Nought;
			break;

		case sf::Mouse::Middle:
			for (auto &entity : m_entities)
			{
				if (entity.second->index() == cellIndexPosition.first)
				{
					destroyEntity(entity.first);
					break;
				}
			}

			if (getWinner() == Entity::TTTCell::Faction::None)
			{
				for (auto &cell : m_entities)
				{
					dynamic_cast<Entity::TTTCell *>(cell.second)->resetColor();
				}
			}
			return false;
		}

		winnerFaction = getWinner();
		if (winnerFaction == Entity::TTTCell::Faction::None)
		{
			auto newCell = new Entity::TTTCell(cellIndexPosition.second,
											   sf::Vector2u(m_offset, m_offset),
											   clickFaction);
			spawnEntity(cellIndexPosition, newCell);
		}
		winnerFaction = getWinner();

		if (winnerFaction != Entity::TTTCell::Faction::None)
		{
			for (auto &cell : m_entities)
			{
				if (dynamic_cast<Entity::TTTCell *>(cell.second)->faction() == winnerFaction)
				{
					cell.second->setColor(sf::Color::White);
				}
			}
			m_entities.clear();
			return true;
		}

		return false;
	}
}
