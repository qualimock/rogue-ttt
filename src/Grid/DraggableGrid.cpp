#include "DraggableGrid.hpp"

#include <iostream>

namespace Grid
{
	DraggableGrid::DraggableGrid(EGridType eGridType,
								 const sf::Vector2i &topLeft,
								 const sf::Vector2i &bottomRight,
								 unsigned linesOffset,
								 bool draggable)
		: BaseGrid(eGridType, topLeft, bottomRight, 0, linesOffset)
		, m_draggable(draggable)
		, m_isDragged(false)
	{}

	void DraggableGrid::drag(const sf::Vector2i &position)
	{
		m_isDragged = (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
					   position.x > m_topLeft.x &&
					   position.x < m_bottomRight.x &&
					   position.y > m_topLeft.y &&
					   position.y < m_bottomRight.y);

		if (!m_isDragged)
		{
			m_dragPoint = position - sf::Vector2i(m_topLeft);
		}

		if (m_draggable && m_isDragged)
		{
			move(position - m_dragPoint);
		}
	}
}
