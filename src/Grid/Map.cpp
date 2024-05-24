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
		: BaseGrid(EGridType::Map, sf::Vector2u(520, 480))
	{
		auto levels = ResourceManager::get_levels();

		for (unsigned levelCounter = 0; levelCounter < levels.first; ++levelCounter)
		{
			auto level = Level(levels.second.second.first[levelCounter]);
			auto floor = Level(levels.second.second.second[levelCounter]);
			auto index = levels.second.first[levelCounter];

			m_levelIndices.emplace(std::to_string(levelCounter), index);
			m_levels.emplace(std::to_string(levelCounter), std::make_pair(level, floor));
		}

		m_player = std::make_shared<Entity::Player>(Entity::Character("player",
																	  sf::Vector2i(m_size.x / 2, m_size.y / 2 + 100),
																	  cellSize(), 2,
																	  Entity::Character::EType::Player));

		sf::Texture texture;
		if (!texture.loadFromFile("res/Sprites/Characters/Player.png"))
		{
			std::cerr << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
		}
		m_player->setTexture(texture);

		m_currentLevel = m_levels.find("0");
		loadLevel(0);
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
					player->interact(foundEntity);
			}
		}
		else
		{
			if (foundEntity == nullptr)
			{
				sf::Vector2i levelIndex = m_levelIndices.at(m_currentLevel->first) + indexOffset;

				std::string nextLevelName;
				for (auto &index : m_levelIndices)
				{
					if (levelIndex == index.second)
					{
						nextLevelName = index.first;
						break;
					}
				}

				auto nextLevel = m_levels.find(nextLevelName);
				if (nextLevel == m_levels.end())
				{
					return nullptr;
				}

				std::cout << nextLevel->first << std::endl;
					
				if (nextLevel != m_levels.end()){
					m_currentLevel = nextLevel;
					for (unsigned i = 0; i < m_levels.size(); ++i)
					{
						if (m_levelIndices.find(m_currentLevel->first) != m_levelIndices.end())
						{
							loadLevel(i);
							break;
						}
					}
					
					sf::Vector2i movementIndex = player->index(); //куда игрок пойдет

					if (player->index().x + indexOffset.x < 0)
					{
						movementIndex.x = m_cellsAmount.x;
					}
					else if (player->index().x + indexOffset.x > m_cellsAmount.x)
					{
						movementIndex.x = 0;
					}

					if (player->index().y + indexOffset.y < 0)
					{
						movementIndex.y = m_cellsAmount.y;
					}
					else if (player->index().y + indexOffset.y > m_cellsAmount.y)
					{
						movementIndex.y = 0;	
					}

					player->setIndex(movementIndex);
					std::cout << movementIndex.x << ":" << movementIndex.y << std::endl;
					player->setPosition(sf::Vector2i(movementIndex.x * m_offset, movementIndex.y * m_offset));

				}
			}

			return nullptr;
		}
	
		return foundEntity;
	}

	void Map::loadLevel(unsigned levelIndex)
	{
		clear();

		for (auto &entity : m_currentLevel->second.first.entities())
		{
			spawnEntity(entity->position(), entity);
		}

		for (auto &entity : m_currentLevel->second.second.entities())
		{
			spawnEntity(entity->position(), entity);
		}

		spawnEntity(m_player->position(), m_player);
	}
}
