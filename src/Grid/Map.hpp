#pragma once

#include "BaseGrid.hpp"

#include "../Entity/Entity.hpp"
#include "../Entity/Character/Character.hpp"

#include <memory>

namespace Entity
{
	class Character;
}

namespace Grid
{
	class Map : public BaseGrid
	{
		Map();

		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

	public:
		static Map& getMap();
		static Map* getMapPointer();

		void move() = delete;

		void placeCharacter(const sf::Vector2i &position, Entity::Character::EType type);
		void placeActor(const sf::Vector2i &position, Entity::Actor *actor);
	};
}
