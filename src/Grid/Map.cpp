#include "Map.hpp"

#include <iostream>

#include "../Entity/Character/Player.hpp"
#include "../Entity/Actor/Wall.hpp"
#include "../Entity/Actor/Door.hpp"
#include "../Entity/Actor/Item.h"
#include "../Entity/Actor/Floor.hpp"
#include "../Entity/Actor/WoodenFloor.hpp"

#include "../Resources/ResourceManager.hpp"

namespace Grid
{
	Map * Map::map = nullptr;

	Map::Map()
		: BaseGrid(EGridType::Map, sf::Vector2u(520, 520))
	{
		/*
		placeCharacter(sf::Vector2i(280, 480), Entity::Character::EType::Player);
		placeActor(sf::Vector2i(280, 480), Entity::Actor::EType::Floor);
		placeCharacter(sf::Vector2i(280, 80), Entity::Character::EType::Enemy);
		placeActor(sf::Vector2i(280, 80), Entity::Actor::EType::WoodenFloor);

		placeActor(sf::Vector2i(360, 80), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(200, 80), Entity::Actor::EType::Wall);

		placeActor(sf::Vector2i(360, 160), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(200, 160), Entity::Actor::EType::Wall);

		placeActor(sf::Vector2i(360, 120), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(200, 120), Entity::Actor::EType::Wall);


		placeActor(sf::Vector2i(200, 40), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(240, 40), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(280, 40), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(320, 40), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(360, 40), Entity::Actor::EType::Wall);

		
		placeActor(sf::Vector2i(200, 200), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(240, 200), Entity::Actor::EType::Wall);
		
		placeActor(sf::Vector2i(280, 200), Entity::Actor::EType::Door);
		placeActor(sf::Vector2i(280, 200), Entity::Actor::EType::WoodenFloor);
		placeActor(sf::Vector2i(320, 200), Entity::Actor::EType::Wall);
		placeActor(sf::Vector2i(360, 200), Entity::Actor::EType::Wall);


		for (unsigned y = 1; y < 14; y++)
		{
			for (unsigned x = 1; x < 14; x++)
			{
				bool occupied = false;
				for (auto& entity : m_entities)
				{
					if (entity.second->index() == sf::Vector2i(x-1, y-1))
					{
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					if ((x > 4) && (x < 10) && (y < 5)) {
						placeActor(sf::Vector2i(x * m_offset, y * m_offset), Entity::Actor::EType::WoodenFloor);
					}
					else {
						placeActor(sf::Vector2i(x * m_offset, y * m_offset), Entity::Actor::EType::Floor);
					}
				}
			}
		}

		placeActor(sf::Vector2i(440, 240), Entity::Actor::EType::Item);
		placeActor(sf::Vector2i(480, 240), Entity::Actor::EType::Item);
		*/
		// loadLevel(currentLevel->second);
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

	// void Map::placeCharacter(const sf::Vector2i &position, Entity::Character::EType type)
	// {
	// 	std::cout << "PLACE" << std::endl;
	// 	sf::Texture texture;
	// 	Entity::Entity *entity = nullptr;

	// 	switch (type)
	// 	{
	// 	case Entity::Character::EType::Player:
	// 	{
	// 		for (auto &entity : m_entities)
	// 		{
	// 			if (entity.second->hasTag("player"))
	// 			{
	// 				std::cout << "PLAYER ALREADY EXISTS" << std::endl;
	// 			}
	// 			return;
	// 		}

	// 		std::cout << "PLAYER" << std::endl;

	// 		entity = new Entity::Player(Entity::Character(position, cellSize(), 1, type));
	// 		if (!texture.loadFromFile("res/Sprites/Characters/Player.png", sf::IntRect(0, 0, 40, 40)))
	// 		{
	// 			std::cerr << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
	// 		}

	// 		entity = new Entity::Player(Entity::Character(position, cellSize(), 2, type));
	// 		entity->setTexture(texture);
	// 		entity->addTag("player");
	// 		break;
	// 	}

	// 	case Entity::Character::EType::Enemy:
	// 	{
	// 		std::cout << "ENEMY" << std::endl;
	// 		entity = new Entity::Character(position, cellSize(), 1, type);
	// 		if (!texture.loadFromFile("res/Sprites/Characters/Enemy.png"))
	// 		{
	// 			std::cerr << "FAILED TO LOAD WALL" << std::endl;
	// 		}

	// 		entity = new Entity::Character(position, cellSize(), 2, type);
	// 		entity->setTexture(texture);
	// 		entity->addTag("enemy");
	// 		break;
	// 	}

	// 	case Entity::Character::EType::NPC:
	// 	{
	// 		std::cout << "NPC" << std::endl;
	// 		break;
	// 	}

	// 	case Entity::Character::EType::None:
	// 	{
	// 		std::cerr << "ATTEMPT TO SPAWN A 'NONE' CHARACTER" << std::endl;
	// 		throw std::exception();
	// 	}
	// 	}

	// 	spawnEntity(adjustEntityPosition(position), entity);
	// }

	// void Map::placeActor(const sf::Vector2i &position, Entity::Actor::EType type)
	// {
	// 	std::cout << "PLACE" << std::endl;
	// 	sf::Texture texture;
	// 	Entity::Entity *entity = nullptr;

	// 	switch (type)
	// 	{
	// 	case Entity::Actor::EType::Wall:
	// 	{
	// 		std::cout << "WALL" << std::endl;
	// 		if (!texture.loadFromFile("res/Sprites/Actors/Wall.png"))
	// 		{
	// 			std::cerr << "FAILED TO LOAD WALL" << std::endl;
	// 		}

	// 		entity = new Entity::Wall(Entity::Actor(position, cellSize(), 2, type));
	// 		entity->setTexture(texture);
	// 		entity->addTag("wall");
	// 		break;
	// 	}
	// 	case Entity::Actor::EType::Door:
	// 	{
	// 		std::cout << "DOOR" << std::endl;
	// 		if (!texture.loadFromFile("res/Sprites/Actors/Door.png"))
	// 		{
	// 			std::cerr << "FAILED TO LOAD DOOR" << std::endl;
	// 		}
	// 		entity = new Entity::Door(Entity::Actor(position, cellSize(), 1, type));
	// 		entity->setTexture(texture);
	// 		entity->addTag("door");
	// 		break;
	// 	}
	// 	case Entity::Actor::EType::Item:
	// 	{
	// 		std::cout << "ITEM" << std::endl;
	// 		if (!texture.loadFromFile("res/Sprites/Actors/Item.png"))
	// 		{
	// 			std::cerr << "FAILED TO LOAD ITEM" << std::endl;
	// 		}
	// 		entity = new Entity::Item(Entity::Actor(position, cellSize(), 1, type));
	// 		entity->setTexture(texture);
	// 		entity->addTag("item");
	// 		break;
	// 	}
	// 	case Entity::Actor::EType::Floor:
	// 	{
	// 		std::cout << "FLOOR" << std::endl;

	// 		if (!texture.loadFromFile("res/Sprites/Background/Grass.png"))
	// 		{
	// 			std::cerr << "FAILED TO LOAD GRASS" << std::endl;
	// 		}
	// 		if (rand() % 5 == 0) {
	// 			texture.loadFromFile("res/Sprites/Background/Grass2.png");
	// 		}
	// 		entity = new Entity::Floor(Entity::Actor(position, cellSize(), 0, type));
	// 		entity->setTexture(texture);
	// 		entity->addTag("floor");
	// 		break;
	// 	}
	// 	case Entity::Actor::EType::WoodenFloor:
	// 	{
	// 		std::cout << "FLOOR" << std::endl;

	// 		if (!texture.loadFromFile("res/Sprites/Background/WoodFloor.png"))
	// 		{
	// 			std::cerr << "FAILED TO LOAD GRASS" << std::endl;
	// 		}

	// 		entity = new Entity::WoodenFloor(Entity::Actor(position, cellSize(), 0, type));
	// 		entity->setTexture(texture);
	// 		entity->addTag("floor");
	// 		break;
	// 	}
	// 	}
	// 	spawnEntity(adjustEntityPosition(position), entity);
	// }

	std::shared_ptr<Entity::Entity> Map::movePlayer(const sf::Vector2i &indexOffset)
	{
		auto player = std::dynamic_pointer_cast<Entity::Player>(m_entities.at("player0"));
		std::shared_ptr<Entity::Entity> foundEntity = nullptr;

		for (auto &entity : m_entities)
		{
			if (entity.second->hasTag("floor"))
			{
				continue;
			}

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
				// if (foundEntity == nullptr)
				// {
				// 	sf::Vector2i levelIndex = currentLevel->first + indexOffset;

				// 	//тут надо выгрузить старый уровень
					
				// 	auto nextLevel = m_levels.find(levelIndex);
					
				// 	if (nextLevel != m_levels.end()){
				// 		currentLevel = nextLevel;
				// 		loadLevel(currentLevel->second);
					
				// 		sf::Vector2i movementIndex = player->index(); //куда игрок пойдет

				// 		if (player->index().x + indexOffset.x < 0)
				// 		{
				// 			movementIndex.x = m_cellsAmount.x - 1;
				// 		}
				// 		else 
				// 		{
				// 			movementIndex.x = 0;
				// 		}

				// 		if (player->index().y + indexOffset.y < 0)
				// 		{
				// 			movementIndex.y = m_cellsAmount.y - 1;
				// 		}
				// 		else 
				// 		{
				// 			movementIndex.y = 0;	
				// 		}

				// 		player->setIndex(movementIndex);
				// 		player->setPosition(sf::Vector2i(movementIndex.x * m_offset, movementIndex.y * m_offset));
				// 	}
				// }
				// else
				// {
					player->interact(foundEntity);
				// }
			}
		}
	
		return foundEntity;
	}

	void Map::loadLevel(unsigned levelIndex)
	{
		auto level = Level(ResourceManager::get_levels()[levelIndex]);
		auto floor = Level(ResourceManager::get_levels()[levelIndex+1]);
		for (auto &entity : level.entities())
		{
			spawnEntity(entity->position(), entity);
		}
		for (auto &entity : floor.entities())
		{
			spawnEntity(entity->position(), entity);
		}
	    m_levels.emplace("0", level);
	}
}
