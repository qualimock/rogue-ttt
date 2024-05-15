#include "BaseGrid.hpp"

#include <cmath>

namespace Grid
{
	BaseGrid::BaseGrid(const std::string &name,
					   EGridType eGridType,
					   const sf::Vector2i &topLeft,
					   const sf::Vector2i &bottomRight,
					   unsigned layer,
					   unsigned linesOffset)
		: IGrid(eGridType, topLeft, bottomRight, linesOffset)
		, m_name(name)
		, m_layer(layer)
	{}

	void BaseGrid::move(const sf::Vector2i &position)
	{
		m_topLeft = position;
		m_bottomRight = position + sf::Vector2i(m_size);
	}

	void BaseGrid::resize(const sf::Vector2i &point)
	{
		m_bottomRight = point;
		m_size = sf::Vector2u(m_bottomRight - m_topLeft);
		m_linesAmount = sf::Vector2u(m_size.y/m_offset,  // horizontal lines
									 m_size.x/m_offset); // vertical lines
	}

	std::pair<sf::Vector2i, sf::Vector2i> BaseGrid::adjustClickPosition(const sf::Vector2i &position) const
	{
		sf::Vector2i cellIndex; // cell index in grid
		sf::Vector2i cellPosition; // cell position in window
		sf::Vector2i relativePosition; // position relative to the grid
					
		relativePosition.x = position.x - m_topLeft.x;
		relativePosition.y = position.y - m_topLeft.y;

		cellIndex.x = relativePosition.x / ( m_offset + 1 ) - 1;
		cellIndex.y = relativePosition.y / ( m_offset + 1 ) - 1;

		// vertical line click
		if ( (m_size.x - 1) % position.x == 0 )
		{
			// crossing lines click
			if ( (m_size.y - 1) % position.y == 0 )
			{
				if ( m_cells.contains(cellIndex) || cellIndex.x < 0 || cellIndex.x > (m_size.x - 1) % m_offset )
				{
					cellIndex.x++;
				}
					
				if ( m_cells.contains(cellIndex) || cellIndex.y < 0 || cellIndex.y > (m_size.y - 1) % m_offset )
				{
					cellIndex.y++;
				}
			}

			cellIndex.y++;

			if ( m_cells.contains(cellIndex) || cellIndex.x < 0 || cellIndex.x > (m_size.x - 1) % m_offset )
			{
				cellIndex.x++;
			}

		}
		// horizontal line click
		else if ( (m_size.y - 1) % position.y == 0 )
		{
			cellIndex.x++;

			if ( m_cells.contains(cellIndex) || cellIndex.y < 0 || cellIndex.y > (m_size.y - 1) % m_offset )
			{
				cellIndex.y++;
			}

		}
		// cell click
		else
		{
			cellIndex.x++;
			cellIndex.y++;
		}

		cellPosition.x = cellIndex.x * ( m_offset ) - relativePosition.x + position.x;
		cellPosition.y = cellIndex.y * ( m_offset ) - relativePosition.y + position.y;

		return std::make_pair(cellIndex, cellPosition);
	}

	void BaseGrid::clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition)
	{
		auto cellIndexPosition = adjustClickPosition(mousePosition);

		switch (type())
		{
		case IGrid::EGridType::Map:
			break;

		case IGrid::EGridType::Combat:
			switch (button)
			{
			case sf::Mouse::Left:
				if (!m_complete)
					spawnCell(cellIndexPosition, Cell::Faction::Nought);
				break;

			case sf::Mouse::Right:
				destroyCell(cellIndexPosition.first);
				break;
			}
			break;

		case IGrid::EGridType::Interaction:
			break;

		case IGrid::EGridType::Storage:
			break;
		}
	}

	void BaseGrid::spawnCell(std::pair<sf::Vector2i, sf::Vector2i> IndexPosition,
							 Cell::Faction faction)
	{
		if (m_cells.find(IndexPosition.first) == m_cells.end())
		{
			m_cells.emplace
			(
				IndexPosition.first,
				Cell(IndexPosition.second, sf::Vector2u(m_offset, m_offset), faction)
			);
		}
	}

	void BaseGrid::destroyCell(const sf::Vector2i &index)
	{
		if (m_cells.find(index) != m_cells.end())
		{
			m_cells.erase(index);
		}
	}

	void BaseGrid::renderCells(sf::RenderTarget &target)
	{
		for(auto &cell : m_cells){
			cell.second.render(target);
		}
	}

	void BaseGrid::clear()
	{
		m_cells.clear();
	}

	void BaseGrid::checkIfComplete()
	{
		unsigned neighbourCounter;
		for (auto &cell : m_cells)
		{
			if (m_cells.find(cell.first + sf::Vector2i(1, 1)) != m_cells.end() ^
				m_cells.find(cell.first + sf::Vector2i(-1, -1)) != m_cells.end())
			{
				neighbourCounter++;

				if (m_cells.find(cell.first + sf::Vector2i(-1, -1)) != m_cells.end() ^
					m_cells.find(cell.first + sf::Vector2i(1, 1)) != m_cells.end())
					neighbourCounter++;
			}
			
			

			if (neighbourCounter == 2)
			{
				m_complete = true;
			}
			else
			{
				m_complete = false;
			}
		}
	}
}
