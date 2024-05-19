#include "Actor.hpp"

namespace Entity
{
	Actor::Actor(const sf::Vector2i &position,
				 const sf::Vector2u &size,
				 EType type)
		: Entity(position, size)
		, m_type(type)
	{
		init();
	}

	Actor::Actor(const Entity &entity, EType type)
		: Entity(entity)
		, m_type(type)
	{
		init();
	}

	Actor::Actor(Entity &&entity, EType type)
		: Entity(entity)
		, m_type(type)
	{
		init();
	}

	void Actor::init()
	{
		setColor(sf::Color::Magenta);
	}
}
