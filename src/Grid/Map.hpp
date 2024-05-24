#pragma once

#include "BaseGrid.hpp"
#include "../Game/Level.hpp"

#include "../Entity/Character/Character.hpp"
#include "../Entity/Actor/Actor.hpp"


namespace Grid
{
	class Map : public BaseGrid
	{
		static Map * map;
		
		std::map<std::string, Level> m_levels;
		std::map<std::string, Level>::iterator currentLevel = m_levels.begin();

		Map();

	public:
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;

		static Map * getMap();

		void move() = delete;

		void loadLevel(unsigned levelIndex);

		std::shared_ptr<Entity::Entity> movePlayer(const sf::Vector2i &indexOffset);
	};
}
