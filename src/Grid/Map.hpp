#pragma once

#include "BaseGrid.hpp"
#include "Level.hpp"

#include "../Entity/Character/Character.hpp"
#include "../Entity/Actor/Actor.hpp"

namespace Entity
{
	class Character;
}

namespace Grid
{
	class Map : public BaseGrid
	{
		static Map * map;
		
		std::map<sf::Vector2i, Level> m_levels;
		std::map<sf::Vector2i, Level>::iterator currentLevel = m_levels.begin();

		void loadLevel(Level &level);

		Map();

	public:
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

		static Map * getMap();

		void move() = delete;

		void placeCharacter(const sf::Vector2i &position, Entity::Character::EType type);
		void placeActor(const sf::Vector2i &position, Entity::Actor::EType type);

		Entity::Entity * movePlayer(const sf::Vector2i &indexOffset);

	};
}
