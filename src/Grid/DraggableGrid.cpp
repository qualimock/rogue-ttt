#include "DraggableGrid.hpp"

#include <iostream>

namespace Grid
{
	DraggableGrid::DraggableGrid(sf::RenderWindow &window,
								 EGridType eGridType,
								 const std::string &name,
								 const sf::Vector2i &topLeft,
								 const sf::Vector2i &bottomRight,
								 unsigned linesOffset,
								 bool draggable)
		: BaseGrid(window, eGridType, name, topLeft, bottomRight, linesOffset)
		, m_draggable(draggable)
		, m_isDragged(false)
	{}

	void DraggableGrid::processEvent(sf::Event &event)
	{
		if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i mousePosition(event.mouseMove.x, event.mouseMove.y);
			m_isDragged = (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
						   mousePosition.x > m_topLeft.x &&
						   mousePosition.x < m_bottomRight.x &&
						   mousePosition.y > m_topLeft.y &&
						   mousePosition.y < m_bottomRight.y);

			if (!m_isDragged)
			{
				m_dragPoint = mousePosition - sf::Vector2i(m_topLeft);
			}

			if (m_draggable && m_isDragged)
			{
				move(mousePosition - m_dragPoint);
			}
		}
	}
}
