#pragma once

#include "BaseGrid.hpp"

#include "../Entity/Entity.hpp"
#include "../Entity/Character/Character.hpp"

namespace Entity
{
	class Character;
}

namespace Grid
{
	class Map : public BaseGrid
	{
		static Map * map;

		Map();

	public:
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

		static Map * getMap();

		void move() = delete;

		void placeCharacter(const sf::Vector2i &position, Entity::Character::EType type);
		void placeActor(const sf::Vector2i &position, Entity::Actor *actor);

		Entity::Entity * movePlayer(const sf::Vector2i &indexOffset);
	};
}
