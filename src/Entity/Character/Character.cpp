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
		init();
	}

	Character::Character(const Entity &entity, EType type)
		: Entity(entity)
		, m_type(type)
	{
		init();
	}

	Character::Character(Entity &&entity, EType type)
		: Entity(entity)
		, m_type(type)
	{
		init();
	}

	void Character::init()
	{
		switch(m_type)
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
		addTag("solid");
	}

	void Character::move(const sf::Vector2i &offset)
	{
		setPosition(position() + offset);
	}

	void Character::interact(Entity *target)
	{
		std::cout << "INTERACTION" << std::endl;

		target->onInteract();
	}

	void Character::onInteract()
	{
		std::cout
			<< "CHARACTER" << std::endl
			<< "POSITION" << std::endl
			<< position().x << ":" << position().y << std::endl
			<< "SIZE" << std::endl
			<< size().x << ":" << size().y <<
		std::endl;
	}
}
