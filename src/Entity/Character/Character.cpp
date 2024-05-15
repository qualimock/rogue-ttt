#include "Character.hpp"

#include <iostream>

namespace Entity
{
	Character::Character(const sf::Vector2i &position,
						 const sf::Vector2u &size,
						 EType type)
		: Entity(position, size)
		, m_type(type)
	{}

	Character::Character(const Entity &entity, EType type)
		: Entity(entity)
		, m_type(type)
	{}

	Character::Character(Entity &&entity, EType type)
		: Entity(entity)
		, m_type(type)
	{}

	void Character::move(const sf::Vector2i &position)
	{
		setPosition(position);
	}

	void Character::interact(const Entity &target)
	{
		std::cout << "INTERACTION" << std::endl;
	}
}
