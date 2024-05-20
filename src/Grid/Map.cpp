#include "Map.hpp"

#include <iostream>

#include "../Entity/Character/Player.hpp"

#include "../Entity/Actor/Wall.hpp"
#include "../Entity/Actor/Door.hpp"
#include "../Entity/Actor/Floor.hpp"

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
		
		for (unsigned y = 1; y < m_cellsAmount.y+2; y++)
		{
			for (unsigned x = 1; x < m_cellsAmount.x-3; x++)
			{
				placeActor(sf::Vector2i(x*m_offset, y*m_offset), Entity::Actor::EType::Floor);
			}
		}
	}

	void Map::resize(const sf::Vector2i &point)
	{
		BaseGrid::resize(point);

		// for (auto &entity : m_entities)
		// {
		// 	if (entity.second->hasTag("floor"))
		// 	{
		// 		m_entities.erase(entity.first);
		// 	}
		// }
		// for (unsigned y = 40; y < m_cellsAmount.y * 40; y += 40)
		// {
		// 	for (unsigned x = 40; x < m_cellsAmount.x * 40; x += 40)
		// 	{
		// 		// std::cout << x << ":" << y << std::endl;
		// 		placeActor(sf::Vector2i(x, y), Entity::Actor::EType::Floor);
		// 	}
		// }
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

		sf::Texture texture;
		sf::Sprite sprite;

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

			if (!texture.loadFromFile("res/PixelTexturePack/Rocks/ICEYROCKS.png"))
			{
				std::cerr << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
			}
			sprite.setTexture(texture);

			entity = new Entity::Player(Entity::Character(position, cellSize(), 2, type));
			entity->setSprite(sprite);
			entity->addTag("player");
			break;
		}

		case Entity::Character::EType::Enemy:
		{
			std::cout << "ENEMY" << std::endl;

			if (!texture.loadFromFile("res/PixelTexturePack/Rocks/GOLDROCKS.png"))
			{
				std::cerr << "FAILED TO LOAD WALL" << std::endl;
			}
			sprite.setTexture(texture);

			entity = new Entity::Character(position, cellSize(), 2, type);
			entity->setSprite(sprite);
			entity->addTag("enemy");
			break;
		}

		case Entity::Character::EType::NPC:
		{
			std::cout << "NPC" << std::endl;

			if (!texture.loadFromFile("res/PixelTexturePack/Bricks/REDBRICKS.png"))
			{
				std::cerr << "FAILED TO LOAD WALL" << std::endl;
			}
			sprite.setTexture(texture);

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

		sf::Texture texture;
		sf::Sprite sprite;

		switch (type)
		{
		case Entity::Actor::EType::Wall:
		{
			std::cout << "WALL" << std::endl;

			if (!texture.loadFromFile("res/PixelTexturePack/Bricks/REDBRICKS.png"))
			{
				std::cerr << "FAILED TO LOAD WALL" << std::endl;
			}
			sprite.setTexture(texture);

			entity = new Entity::Wall(Entity::Actor(position, cellSize(), 2, type));
			entity->setSprite(sprite);
			entity->addTag("wall");
			break;
		}
		case Entity::Actor::EType::Door:
		{
			std::cout << "DOOR" << std::endl;
			if (!texture.loadFromFile("res/PixelTexturePack/Doors/SPOOKYDOOR.png"))
			{
				std::cerr << "FAILED TO LOAD DOOR" << std::endl;
			}
			sprite.setTexture(texture);

			entity = new Entity::Door(Entity::Actor(position, cellSize(), 1, type));
			entity->setSprite(sprite);
			entity->addTag("door");
			break;
		}
		case Entity::Actor::EType::Floor:
		{
			std::cout << "FLOOR" << std::endl;

			// if (!texture.loadFromFile("res/PixelTexturePack/Elements/TALLGRASS.png"))
			// {
			// 	std::cerr << "FAILED TO LOAD GRASS" << std::endl;
			// }
			// sprite.setTexture(texture);

			entity = new Entity::Floor(Entity::Actor(position, cellSize(), 0, type));
			entity->setSprite(sprite);
			entity->addTag("floor");
			break;
		}
		}

		spawnEntity(adjustEntityPosition(position), entity);
	}

	Entity::Entity * Map::movePlayer(const sf::Vector2i &indexOffset)
	{
		auto player = dynamic_cast<Entity::Player *>(m_entities.at("0"));
		if (!player->hasTag("player"))
		{
			std::cerr << "PLAYER HAS NON-ZERO INDEX" << std::endl;
			return nullptr;
		}

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
