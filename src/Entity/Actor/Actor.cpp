#include "Actor.hpp"

#include <iostream>

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
		addTag("solid");
	}

	void Actor::onInteract()
	{
		std::cout
			<< "ACTOR" << std::endl
			<< "POSITION" << std::endl
			<< position().x << ":" << position().y << std::endl
			<< "SIZE" << std::endl
			<< size().x << ":" << size().y <<
		std::endl;
	}
}
