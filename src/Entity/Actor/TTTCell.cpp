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
		sf::Texture texture;
		switch(m_faction)
		{
		case Faction::Cross:
			switch (rand() % 3) {
			case 0:
				texture.loadFromFile("res/Sprites/Actors/X1.png");
				break;
			case 1:
				texture.loadFromFile("res/Sprites/Actors/X2.png");
				break;
			case 2:
				texture.loadFromFile("res/Sprites/Actors/X3.png");
				break;
			}
			setTexture(texture);
			break;

		case Faction::Nought:
			switch (rand() % 3) {
			case 0:
				texture.loadFromFile("res/Sprites/Actors/O1.png");
				break;
			case 1:
				texture.loadFromFile("res/Sprites/Actors/O2.png");
				break;
			case 2:
				texture.loadFromFile("res/Sprites/Actors/O3.png");
				break;
			}
			setTexture(texture);
			break;

		case Faction::None:
			m_color = sf::Color::Transparent;
			break;
		}

		this->setColor(m_color);
	}
}
