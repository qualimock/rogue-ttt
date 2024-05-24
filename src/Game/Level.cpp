#include "Level.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "../Entity/Character/Player.hpp"
#include "../Entity/Actor/Wall.hpp"
#include "../Entity/Actor/Door.hpp"
#include "../Entity/Actor/Floor.hpp"
#include "../Entity/Actor/Item.h"

std::shared_ptr<Entity::Entity> create_entity_from_description(const char description,
												const sf::Vector2i &position,
												const sf::Vector2u &size)
{
	switch (description)
	{
	case 'P':
		return std::make_shared<Entity::Player>(Entity::Character("player", position, size, 2, Entity::Character::EType::Player));
	case 'W':
		return std::make_shared<Entity::Wall>(Entity::Actor("wall", position, size, 1, Entity::Actor::EType::Wall));
	case 'D':
		return std::make_shared<Entity::Door>(Entity::Actor("door", position, size, 1, Entity::Actor::EType::Door));
	case 'I':
		return std::make_shared<Entity::Item>(Entity::Actor("item", position, size, 1, Entity::Actor::EType::Item));
	case 'F':
		return std::make_shared<Entity::Floor>(Entity::Actor("floor", position, size, 0, Entity::Actor::EType::Floor));
	case ' ':
		return nullptr;
	default:
		std::cerr << "ERROR::LEVEL::create_game_object_from_description: Unknown game object description: " << description << std::endl;
	}

	return nullptr;
}

Level::Level(const std::vector<std::string> &levelDescription)
	: m_cellSize(40, 40)
{
	if (levelDescription.empty())
	{
		std::cerr << "ERROR::LEVEL::Level: Empty level description!" << std::endl;
		return;
	}

	m_size = sf::Vector2i(levelDescription[0].length(), levelDescription.size());

	sf::Vector2i offset = sf::Vector2i(0, 0);
	for (const std::string &currentRow : levelDescription)
	{
		offset.x = 0;
		for (const char currentElement : currentRow)
		{
			auto entity = create_entity_from_description(currentElement, offset, m_cellSize);
			if (entity)
				m_levelEntities.emplace_back(entity);

			offset.x += m_cellSize.x;
		}

		offset.y += m_cellSize.y;
	}
}

const std::vector<std::shared_ptr<Entity::Entity>> &Level::entities() const
{
	return m_levelEntities;
}
