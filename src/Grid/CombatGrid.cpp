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

	Cell::Faction CombatGrid::getWinner()
	{
		for (auto &cell : m_cells)
		{
			if ((m_cells.find(cell.first + sf::Vector2i(1, 1)) != m_cells.end() &&
				 m_cells.find(cell.first + sf::Vector2i(-1, -1)) != m_cells.end())
				||
				(m_cells.find(cell.first + sf::Vector2i(1, -1)) != m_cells.end() &&
				 m_cells.find(cell.first + sf::Vector2i(-1, 1)) != m_cells.end())
				||
				(m_cells.find(cell.first + sf::Vector2i(0, 1)) != m_cells.end() &&
				 m_cells.find(cell.first + sf::Vector2i(0, -1)) != m_cells.end())
				||
				(m_cells.find(cell.first + sf::Vector2i(1, 0)) != m_cells.end() &&
				 m_cells.find(cell.first + sf::Vector2i(-1, 0)) != m_cells.end())
				)
			{
				return cell.second.faction();
			}
		}

		return Cell::Faction::None;
	}

	void CombatGrid::clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition)
	{
		auto cellIndexPosition = adjustClickPosition(mousePosition);
		Cell::Faction clickFaction;
		Cell::Faction winnerFaction;

		std::cout << "COMBAT" << std::endl;

		std::cout << position().x << ":" << position().y << std::endl;

		switch (button)
		{
		case sf::Mouse::Left:
			clickFaction = Cell::Faction::Cross;
			break;

		case sf::Mouse::Right:
			clickFaction = Cell::Faction::Nought;
			break;

		case sf::Mouse::Middle:
			destroyCell(cellIndexPosition.first);
			if (getWinner() == Cell::None)
			{
				for (auto &cell : m_cells)
				{
					cell.second.resetColor();
				}
			}
			return;
		}

		winnerFaction = getWinner();
		if (winnerFaction == Cell::None)
		{
			spawnCell(cellIndexPosition, clickFaction);
		}
		winnerFaction = getWinner();

		if (winnerFaction != Cell::None)
		{
			for (auto &cell : m_cells)
			{
				if (cell.second.faction() == winnerFaction)
				{
					cell.second.setFillColor(sf::Color::White);
				}
			}
		}
	}
}
