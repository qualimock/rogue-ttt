#include "Entity.hpp"

namespace Entity
{
	Entity::Entity(const std::string &name,
				   const sf::Vector2i& position,
				   const sf::Vector2u& size,
				   unsigned layer)
		: m_name(name)
		, m_shape(sf::Vector2f(size))
		, m_position(position)
		, m_size(size)
		, m_color(sf::Color::White)
		, m_index(0, 0)
		, m_layer(layer)
	{
		setPosition(position);
		resetColor();
	}

	bool Entity::operator==(const std::shared_ptr<Entity> entity) const
	{
		if (m_tags == entity->tags())
			return true;

		return false;
	}

	void Entity::removeTag(const std::string &tag)
	{
		m_tags.erase(tag);
	}

	void Entity::render(sf::RenderTarget &target)
	{
		target.draw(m_sprite);
		// target.draw(m_shape);
	}

	void Entity::resetColor()
	{
		m_shape.setFillColor(m_color);
	}

	void Entity::setPosition(const sf::Vector2i &position)
	{
		m_position = position;
		m_shape.setPosition(sf::Vector2f(m_position));
		m_sprite.setPosition(sf::Vector2f(m_position));
	}

	void Entity::setColor(sf::Color color)
	{
		m_shape.setFillColor(color);
	}

	void Entity::setTexture(const sf::Texture texture)
	{
		m_texture = texture;
		m_sprite.setTexture(m_texture);
	}

	void Entity::setIndex(const sf::Vector2i &index)
	{
		m_index = index;
	}
}
