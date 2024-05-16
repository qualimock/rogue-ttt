#include "Character.hpp"

#include <iostream>

namespace Entity
{
	Character::Character(const sf::Vector2i &position,
						 const sf::Vector2u &size,
						 EType type)
		: Entity(position, size)
		, m_type(type)
	{
		switch(type)
		{
		case EType::Player:
			setColor(sf::Color::White);
			break;

		case EType::Enemy:
			setColor(sf::Color::Red);
			break;

		case EType::NPC:
			setColor(sf::Color::Yellow);
			break;

		case EType::None:
			setColor(sf::Color::Magenta);
			break;
		}
	}

	Character::Character(const Entity &entity, EType type)
		: Entity(entity)
		, m_type(type)
	{}

	Character::Character(Entity &&entity, EType type)
		: Entity(entity)
		, m_type(type)
	{}

	void Character::move(const sf::Vector2i &offset)
	{
		setPosition(position() + offset);
	}

	void Character::interact(Entity *target)
	{
		std::cout << "INTERACTION" << std::endl;

		switch (m_type)
		{
		case EType::Enemy:
			std::cout << "ENEMY" << std::endl;
			break;

		case EType::NPC:
			std::cout << "NPC" << std::endl;
		}
	}
}
