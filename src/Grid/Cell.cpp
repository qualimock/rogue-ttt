#include "Cell.hpp"

namespace Grid {
	Cell::Cell(const sf::Vector2f& position,
			   const sf::Vector2f& size,
			   Faction faction)
		: sf::RectangleShape(size)
		, m_faction(faction)
	{
		this->move(position);
	}

	bool Cell::isAlly(const Cell& cell) {
		return (m_faction == cell.faction());
	}
}
