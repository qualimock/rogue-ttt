#include "Cell.hpp"

namespace Grid
{
	Cell::Cell(const sf::Vector2f& position,
			   const sf::Vector2f& size,
			   Faction faction)
		: sf::RectangleShape(size)
		, m_faction(faction)
	{
		this->move(position);

		switch(m_faction)
		{
		case Cross:
			m_color = sf::Color::Red;
			break;

		case Nought:
			m_color = sf::Color::Cyan;
			break;

		case None:
			m_color = sf::Color::Transparent;
			break;
		}

		this->setFillColor(m_color);
	}

	bool Cell::isAlly(const Cell& cell)
	{
		return (m_faction == cell.faction());
	}
}
