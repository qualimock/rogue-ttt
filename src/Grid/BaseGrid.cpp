#include "BaseGrid.hpp"

namespace Grid
{
	BaseGrid::BaseGrid(sf::RenderWindow &window,
					   EGridType eGridType,
					   const std::string &name,
					   const sf::Vector2i &topLeft,
					   const sf::Vector2i &bottomRight,
					   unsigned linesOffset)
		: IGrid(window, eGridType, topLeft, bottomRight, linesOffset)
		, m_name(name)
	{}

	void BaseGrid::processEvent(sf::Event &event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
			sf::Vector2i relativeMousePos; //Позиция мыши относительно грида
			sf::Vector2i cellIndex; //Номер столбца и строки ячейки в гриде
			sf::Vector2f cellPos; //Координаты ячейки в окне

			relativeMousePos.x = mousePos.x - m_topLeft.x;
			relativeMousePos.y = mousePos.y - m_topLeft.y;
			
			//Игнорирование нажатия мыши вне грида
			if ( relativeMousePos.x < 0 || relativeMousePos.x > m_size.x ||
					relativeMousePos.y < 0 || relativeMousePos.y > m_size.y )
			{
				return;
			}
			
			cellIndex.x = relativeMousePos.x / ( m_offset + 1 ) - 1;
			cellIndex.y = relativeMousePos.y / ( m_offset + 1 ) - 1;
			
			//Нажатие на вертикальную полосу
			if ( ( m_size.x - 1 ) % relativeMousePos.x == 0 )
			{
				//Нажатие на пересечение полос
				if ( ( m_size.y - 1 ) % relativeMousePos.y == 0 )
				{
					if ( m_cells.contains(cellIndex) || cellIndex.x < 0 || cellIndex.x > ( m_size.x - 1 ) % m_offset )
					{
						cellIndex.x++;
					}
					
					if ( m_cells.contains(cellIndex) || cellIndex.y < 0 || cellIndex.y > ( m_size.y - 1 ) % m_offset )
					{
						cellIndex.y++;
					}
				}

				cellIndex.y++;

				if ( m_cells.contains(cellIndex) || cellIndex.x < 0 || cellIndex.x > ( m_size.x - 1 ) % m_offset )
				{
					cellIndex.x++;
				}

			}
			//Нажатие на горизонтальную полосу
			else if ( ( m_size.y - 1 ) % relativeMousePos.y == 0 )
			{
				cellIndex.x++;

				if ( m_cells.contains(cellIndex) || cellIndex.y < 0 || cellIndex.y > ( m_size.y - 1 ) % m_offset )
				{
					cellIndex.y++;
				}

			}
			//Нажатие на клетку
			else
			{
				cellIndex.x++;
				cellIndex.y++;
			}

			cellPos.x = cellIndex.x * ( m_offset ) - relativeMousePos.x + mousePos.x;
			cellPos.y = cellIndex.y * ( m_offset ) - relativeMousePos.y + mousePos.y;

			m_cells.emplace( cellIndex, Cell(cellPos, sf::Vector2f(m_offset, m_offset), Cell::Faction::None));
		}
	}

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

	void BaseGrid::drawCells(sf::RenderWindow &window)
	{
		for(auto cell : m_cells){
			cell.second.draw(window);
		}
	}
}
