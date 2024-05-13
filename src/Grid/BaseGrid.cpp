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
			auto mousePos = sf::Mouse::getPosition(m_window);
			sf::Vector2u relativeMousePos; //Позиция мыши относительно грида
			sf::Vector2u cellIndex; //Номер столбца и строки ячейки в гриде
			sf::Vector2f cellPos; //Координаты ячейки в окне

			relativeMousePos.x = mousePos.x - m_topLeft.x;
			relativeMousePos.y = mousePos.y - m_topLeft.y;
			
			//Игнорирование нажатия мыши вне грида
			if ( relativeMousePos.x < 0 || relativeMousePos.x > m_size.x ||
					relativeMousePos.y < 0 || relativeMousePos.y > m_size.y )
			{
				return;
			}
			
			cellIndex.x = relativeMousePos.x / ( m_offset + 1 );
			cellIndex.y = relativeMousePos.y / ( m_offset + 1 );

			// Нажатие на вертикальную полосу
			if ( relativeMousePos.x % ( m_offset + 1 ) == 0 )
			{
				//Нажатие на пересечение полос
				if ( relativeMousePos.y % ( m_offset + 1 ) == 0 )
				{
					//Проверка углов
					if ( relativeMousePos.x == 0 )
					{
						//Нажатие в левый верхний угол
						/*
						if ( relativeMousePos.y == 0 )
						{
							//Тут всё четко, позиция и так подходит для этого случая	
						}
						*/
						//Нажатие в правый верхний угол
						if ( relativeMousePos.y == ( m_size.y - 1 ) )
						{
							cellIndex.x--;
						}
						//Нажатие на пересечение на левой границе грида
						else
						{
							cellIndex.y--;

							if ( m_cells.contains(cellIndex) )
							{
								cellIndex.y++;
							}
						}
					}
					else if ( relativeMousePos.x == ( m_size.x - 1 ) )
					{
						//Нажатие в левый нижний угол
						if ( relativeMousePos.y == 0 )
						{
							cellIndex.y--;
						}
						//Нажатие в правый нижний угол
						else if ( relativeMousePos.y == ( m_size.y - 1 ) )
						{
							cellIndex.x--;
							cellIndex.y--;
						}
						//Нажатие на пересечение на правой границе грида
						else
						{
							cellIndex.x--;
							cellIndex.y--;

							if ( m_cells.contains(cellIndex) )
							{
								cellIndex.y++;
							}
						}
					}
				}
				//Нажатие на вертикальную полосу
				else
				{
					//Нажатие на вертикальную границу
					if ( relativeMousePos.x == ( m_size.x - 1 ) )
					{
						cellIndex.x--;
					}
					//Нажатие на вертикальную полосу в гриде
					else
					{
						cellIndex.x--;

						if ( m_cells.contains(cellIndex) )
						{
							cellIndex.x++;
						}
					}
				}
			} 
			//Нажатие на горизонтальную полосу
			else if ( relativeMousePos.y % ( m_offset + 1 ) == 0 )
			{
				//Нажатие на горизонтальную границу грида
				if ( relativeMousePos.y == ( m_size.y - 1 ) )
				{
					cellIndex.y--;
				}
				//Нажатие на горизонтальную полосу грида
				else
				{
					cellIndex.y--;

					if ( m_cells.contains(cellIndex) )
					{
						cellIndex.y++;
					}
				}
			} 
			//Нажатие на клетку
			/*
			else
			{
				//Тут победа и тоже всё работает
				cellIndex.x = relativeMousePos.x / ( m_offset + 1 );
				cellIndex.y = relativeMousePos.y / ( m_offset + 1 );
			}
			*/

			cellPos.x = cellIndex.x * ( m_offset + 1 ) + 1;
			cellPos.y = cellIndex.y * ( m_offset + 1 ) + 1;

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
}
