#include "Entity.hpp"

namespace Entity
{
	Entity::Entity(const sf::Vector2i& position,
				   const sf::Vector2u& size)
		: sf::RectangleShape(sf::Vector2f(size))
		, m_color(sf::Color::White)
	{
		this->move(sf::Vector2f(position));

		resetColor();
	}

	void Entity::render(sf::RenderTarget &target)
	{
		target.draw(*this);
	}

	void Entity::resetColor()
	{
		this->setFillColor(m_color);
	}
}
