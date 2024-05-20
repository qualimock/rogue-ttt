#pragma once

#include "BaseGrid.hpp"

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

		Map();

	public:
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

		static Map * getMap();

		void move() = delete;

		void resize(const sf::Vector2i &point) override;

		void placeCharacter(const sf::Vector2i &position, Entity::Character::EType type);
		void placeActor(const sf::Vector2i &position, Entity::Actor::EType type);

		Entity::Entity * movePlayer(const sf::Vector2i &indexOffset);
	};
}
