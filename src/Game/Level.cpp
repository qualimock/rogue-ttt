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
	sf::Texture texture;
	switch (description)
	{
	case 'P':
	{
		auto player = std::make_shared<Entity::Player>(Entity::Character("player", position, size, 2, Entity::Character::EType::Player));
		if (!texture.loadFromFile("res/Sprites/Characters/Player.png"))
		{
			std::cerr << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
		}
		player->setTexture(texture);
		return player;
	}
	case 'E':
	{
		auto enemy = std::make_shared<Entity::Character>("enemy", position, size, 2, Entity::Character::EType::Enemy);
		if (!texture.loadFromFile("res/Sprites/Characters/Enemy.png"))
		{
			std::cerr << "FAILED TO LOAD ENEMY TEXTURE" << std::endl;
		}
		enemy->setTexture(texture);
		return enemy;
	}
	case 'W':
	{
		auto wall = std::make_shared<Entity::Wall>(Entity::Actor("wall", position, size, 1, Entity::Actor::EType::Wall));
		if (!texture.loadFromFile("res/Sprites/Actors/Wall.png"))
		{
			std::cerr << "FAILED TO LOAD WALL TEXTURE" << std::endl;
		}
		wall->setTexture(texture);
		return wall;
	}
	case 'D':
	{
		auto door = std::make_shared<Entity::Door>(Entity::Actor("door", position, size, 2, Entity::Actor::EType::Door));
		if (!texture.loadFromFile("res/Sprites/Actors/Door.png"))
		{
			std::cerr << "FAILED TO LOAD DOOR TEXTURE" << std::endl;
		}
		door->setTexture(texture);
		return door;
	}
	case 'F':
	{
		auto floor = std::make_shared<Entity::Floor>(Entity::Actor("floor", position, size, 1, Entity::Actor::EType::Floor));
		if (!texture.loadFromFile("res/Sprites/Background/Grass2.png"))
		{
			std::cerr << "FAILED TO LOAD FLOOR TEXTURE" << std::endl;
		}
		floor->setTexture(texture);
		return floor;
	}
	case 'I':
	{
		auto item = std::make_shared<Entity::Item>(Entity::Actor("item", position, size, 1, Entity::Actor::EType::Item));
		if (!texture.loadFromFile("res/Sprites/Actors/Item.png"))
		{
			std::cerr << "FAILED TO LOAD ITEM TEXTURE" << std::endl;
		}
		item->setTexture(texture);
		return item;
	}
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
