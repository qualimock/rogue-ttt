#include "Cell.hpp"

namespace Grid
{
	Cell::Cell(const sf::Vector2i& position,
			   const sf::Vector2u& size,
			   Faction faction)
		: sf::RectangleShape(sf::Vector2f(size))
		, m_faction(faction)
	{
		this->move(sf::Vector2f(position));

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

	void Cell::render(sf::RenderTarget &target)
	{
		target.draw(*this);
	}
}
