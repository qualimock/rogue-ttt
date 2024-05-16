#include "CombatGrid.hpp"

#include <iostream>

namespace Grid
{
	CombatGrid::CombatGrid(const std::string &name,
						   const sf::Vector2i &topLeft,
						   const sf::Vector2i &bottomRight,
						   unsigned layer,
						   unsigned linesOffset)
		: BaseGrid(name, EGridType::Combat, topLeft, bottomRight, layer, linesOffset)
	{}

	Entity::TTTCell::Faction CombatGrid::checkNeighbors(const std::pair<sf::Vector2i, Entity::Entity *> &origin,
														const sf::Vector2i &n1Offset,
														const sf::Vector2i &n2Offset)
	{
		auto n1 = m_entities.find(origin.first + n1Offset);
		auto n2 = m_entities.find(origin.first + n2Offset);
		Entity::TTTCell::Faction neighboursFaction = Entity::TTTCell::Faction::None;

		if (n1 != m_entities.end() && n2 != m_entities.end())
		{
			if (dynamic_cast<Entity::TTTCell *>(n1->second)->faction() ==
				dynamic_cast<Entity::TTTCell *>(n2->second)->faction())
			{
				neighboursFaction = dynamic_cast<Entity::TTTCell *>(n1->second)->faction();
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
			if (checkNeighbors(entity, sf::Vector2i(1, 1), sf::Vector2i(-1, -1)) != Entity::TTTCell::Faction::None)
			{
				std::cout << "ORIGIN" << std::endl;
				std::cout << entity.first.x << ":" << entity.first.y << std::endl;
				std::cout << "URDL" << std::endl;
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}

			if	(checkNeighbors(entity, sf::Vector2i(-1, 1), sf::Vector2i(1, -1)) != Entity::TTTCell::Faction::None)
			{
				std::cout << "ORIGIN" << std::endl;
				std::cout << entity.first.x << ":" << entity.first.y << std::endl;
				std::cout << "ULDR" << std::endl;
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}

			if (checkNeighbors(entity, sf::Vector2i(0, 1), sf::Vector2i(0, -1)) != Entity::TTTCell::Faction::None)
			{
				std::cout << "ORIGIN" << std::endl;
				std::cout << entity.first.x << ":" << entity.first.y << std::endl;
				std::cout << "UCDC" << std::endl;
				return dynamic_cast<Entity::TTTCell *>(entity.second)->faction();
			}

			if(checkNeighbors(entity, sf::Vector2i(1, 0), sf::Vector2i(-1, 0)) != Entity::TTTCell::Faction::None)
			{
				std::cout << "ORIGIN" << std::endl;
				std::cout << entity.first.x << ":" << entity.first.y << std::endl;
				std::cout << "CRCL" << std::endl;
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
			destroyEntity(cellIndexPosition.first);
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
			return true;
		}

		return false;
	}
}
