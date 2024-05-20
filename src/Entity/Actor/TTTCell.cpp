#include "TTTCell.hpp"

namespace Entity
{
	TTTCell::TTTCell(const sf::Vector2i &position,
					 const sf::Vector2u &size,
					 Faction faction)
		: Actor(position, size, 0, EType::tttCell)
		, m_faction(faction)
	{
		resetColor();
	}

	bool TTTCell::isAlly(const TTTCell &tttCell)
	{
		return (m_faction == tttCell.faction());
	}

	void TTTCell::resetColor()
	{
		switch(m_faction)
		{
		case Faction::Cross:
			m_color = sf::Color::Red;
			break;

		case Faction::Nought:
			m_color = sf::Color::Cyan;
			break;

		case Faction::None:
			m_color = sf::Color::Transparent;
			break;
		}

		this->setColor(m_color);
	}
}
