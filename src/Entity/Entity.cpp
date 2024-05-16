#include "Entity.hpp"

namespace Entity
{
	Entity::Entity(const sf::Vector2i& position,
				   const sf::Vector2u& size)
		: m_shape(sf::Vector2f(size))
		, m_position(position)
		, m_size(size)
		, m_color(sf::Color::White)
	{
		setPosition(position);
		resetColor();
	}

	void Entity::render(sf::RenderTarget &target)
	{
		target.draw(m_shape);
	}

	void Entity::resetColor()
	{
		m_shape.setFillColor(m_color);
	}

	void Entity::setPosition(const sf::Vector2i &position)
	{
		m_position = position;
		m_shape.setPosition(sf::Vector2f(m_position));
	}

	void Entity::setColor(sf::Color color)
	{
		m_shape.setFillColor(color);
	}
}
