#pragma once

#include "BaseGrid.hpp"

namespace Grid
{
	class DraggableGrid : public BaseGrid
	{
		bool m_draggable;
	public:
		DraggableGrid(sf::RenderWindow &window,
					  EGridType eGridType,
					  const std::string &name,
					  const sf::Vector2i &topLeft,
					  const sf::Vector2i &bottomRight,
					  unsigned linesOffset,
					  bool draggable);

		sf::Vector2i m_dragPoint;
		bool m_isDragged;

		void processEvent(sf::Event &event) override;
	};
}
