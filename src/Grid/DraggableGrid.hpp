#pragma once

#include "BaseGrid.hpp"

namespace Grid
{
	class DraggableGrid : public BaseGrid
	{
		bool m_draggable;
	public:
		DraggableGrid(EGridType eGridType,
					  const sf::Vector2i &topLeft,
					  const sf::Vector2i &bottomRight,
					  unsigned linesOffset,
					  bool draggable);

		sf::Vector2i m_dragPoint;
		bool m_isDragged;

		void drag(const sf::Vector2i &position);
	};
}
