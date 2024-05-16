#include "Map.hpp"

#include <iostream>

namespace Grid
{
	Map::Map()
		: BaseGrid("map", EGridType::Map, sf::Vector2i(0, 0), sf::Vector2i(640, 480), 0, 40)
	{
		placeCharacter(sf::Vector2i(m_size.x / 2, m_size.y / 2), Entity::Character::EType::Player);
		placeCharacter(sf::Vector2i(100, 100), Entity::Character::EType::Enemy);
	}

	Map& Map::getMap()
	{
		static Map instance;
		return instance;
	}

	Map* Map::getMapPointer()
	{
		static Map instance;
		return &instance;
	}


	void Map::placeCharacter(const sf::Vector2i &position, Entity::Character::EType type)
	{
		std::cout << "PLACE" << std::endl;

		if (type == Entity::Character::EType::Player)
		{
			for (auto &entity : m_entities)
			{
				if (entity.second->hasTag("player"))
				{
					std::cout << "PLAYER ALREADY EXISTS" << std::endl;
				}
				return;
			}

			std::cout << "PLAYER" << std::endl;
			auto player = new Entity::Character(position,
												sf::Vector2u(m_offset, m_offset),
												Entity::Character::EType::Player);
			player->addTag("player");
			spawnEntity(adjustEntityPosition(position), player);
		}

		if (type == Entity::Character::EType::Enemy)
		{
			std::cout << "ENEMY" << std::endl;
			auto enemy = new Entity::Character(position,
											   sf::Vector2u(m_offset, m_offset),
											   Entity::Character::EType::Enemy);
			enemy->addTag("enemy");
			spawnEntity(adjustEntityPosition(position), enemy);
		}

		if (type == Entity::Character::EType::NPC)
			std::cout << "NPC" << std::endl;

		if (type == Entity::Character::EType::None)
			std::cout << "NONE" << std::endl;
	}

	void Map::placeActor(const sf::Vector2i &position, Entity::Actor *actor)
	{}

	bool Map::movePlayer(const sf::Vector2i &indexOffset)
	{
		for (auto &entity : m_entities)
		{
			if (m_entities.find(entity.first + indexOffset) == m_entities.end() && entity.second->hasTag("player"))
			{
				auto player = m_entities.extract(entity.first);

				player.key() = player.key() + indexOffset;

				dynamic_cast<Entity::Character *>(player.mapped())->move(sf::Vector2i(indexOffset.x*m_offset,
																					  indexOffset.y*m_offset));

				m_entities.insert(std::move(player));

				return true;
			}
		}

		return false;
	}
}
