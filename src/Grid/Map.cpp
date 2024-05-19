#include "Map.hpp"

#include <iostream>

#include "../Entity/Character/Player.hpp"
#include "../Entity/Actor/Wall.hpp"
#include "../Entity/Actor/Door.hpp"


namespace Grid
{
	Map * Map::map = nullptr;

	Map::Map()
		: BaseGrid(EGridType::Map, sf::Vector2u(640, 480))
	{
		placeCharacter(sf::Vector2i(m_size.x / 2, m_size.y / 2), Entity::Character::EType::Player);
		placeCharacter(sf::Vector2i(100, 100), Entity::Character::EType::Enemy);
		placeActor(sf::Vector2i(200, 200), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(240, 200), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(280, 200), Entity::Actor::EType::Door);
		placeActor(sf::Vector2i(320, 200), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(360, 200), Entity::Actor::EType::Wall);
	}

	Map * Map::getMap()
	{
		if (map == nullptr)
		{
			return new Map();
		}
		else
		{
			return std::move(map);
		}
	}

	void Map::placeCharacter(const sf::Vector2i &position, Entity::Character::EType type)
	{
		std::cout << "PLACE" << std::endl;

		Entity::Entity *entity = nullptr;

		switch (type)
		{
		case Entity::Character::EType::Player:
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

			entity = new Entity::Player(Entity::Character(position, cellSize(), type));
			entity->addTag("player");
			break;
		}

		case Entity::Character::EType::Enemy:
		{
			std::cout << "ENEMY" << std::endl;

			entity = new Entity::Character(position, cellSize(), type);
			entity->addTag("enemy");
			break;
		}

		case Entity::Character::EType::NPC:
		{
			std::cout << "NPC" << std::endl;
			break;
		}

		case Entity::Character::EType::None:
		{
			std::cerr << "ATTEMPT TO SPAWN A 'NONE' CHARACTER" << std::endl;
			throw std::exception();
		}
		}

		spawnEntity(adjustEntityPosition(position), entity);
	}

	void Map::placeActor(const sf::Vector2i &position, Entity::Actor::EType type)
	{
		std::cout << "PLACE" << std::endl;

		Entity::Entity *entity = nullptr;

		switch (type)
		{
		case Entity::Actor::EType::Wall:
		{
			std::cout << "WALL" << std::endl;

			entity = new Entity::Wall(Entity::Actor(position, cellSize(), type));
			entity->addTag("wall");
			break;
		}
		case Entity::Actor::EType::Door:
		{
			std::cout << "DOOR" << std::endl;

			entity = new Entity::Door(Entity::Actor(position, cellSize(), type));
			entity->addTag("door");
			break;
		}
		}

		spawnEntity(adjustEntityPosition(position), entity);
	}

	Entity::Entity * Map::movePlayer(const sf::Vector2i &indexOffset)
	{
		auto player = dynamic_cast<Entity::Player *>(m_entities.at("0"));
		Entity::Entity* foundEntity = nullptr;

		for (auto &entity : m_entities)
		{
			if (entity.second->index() == player->index() + indexOffset)
			{
				foundEntity = entity.second;
				break;
			}
		}

		bool canMove =
			((player->index().x + indexOffset.x) >= 0) &&
			((player->index().x + indexOffset.x) <= m_cellsAmount.x) &&
			((player->index().y + indexOffset.y) >= 0) &&
			((player->index().y + indexOffset.y) <= m_cellsAmount.y);

		if (canMove)
		{
			if (foundEntity == nullptr || !foundEntity->hasTag("solid"))
			{
				std::cout << "PLAYER" << std::endl;
				std::cout << "MOVE" << std::endl;

				player->setIndex(player->index() + indexOffset);
				player->move(sf::Vector2i(indexOffset.x*m_offset, indexOffset.y*m_offset));
			}
			else
			{
				player->interact(foundEntity);
			}
		}
		return foundEntity;
	}
}
