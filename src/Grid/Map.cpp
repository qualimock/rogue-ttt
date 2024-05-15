#include "Map.hpp"

#include <iostream>

namespace Grid
{
	Map::Map()
		: BaseGrid("map", EGridType::Map, sf::Vector2i(0, 0), sf::Vector2i(640, 480), 0, 40)
	{
		placeCharacter(sf::Vector2i(m_size.x / 2, m_size.y / 2), Entity::Character::EType::Player);
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

		switch (type)
		{
		case Entity::Character::EType::Player:
			std::cout << "PLAYER" << std::endl;

			spawnEntity
			(
				adjustEntityPosition(position),
				new Entity::Character
				(
					position,
					sf::Vector2u(m_offset, m_offset),
					Entity::Character::EType::Player
				)
			);
			break;

		case Entity::Character::EType::Enemy:
			std::cout << "ENEMY" << std::endl;
			break;

		case Entity::Character::EType::NPC:
			std::cout << "NPC" << std::endl;
			break;

		case Entity::Character::EType::None:
			std::cout << "NONE" << std::endl;
			break;
		}
	}

	void Map::placeActor(const sf::Vector2i &position, Entity::Actor *actor)
	{}
}
