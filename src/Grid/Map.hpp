#pragma once

#include "BaseGrid.hpp"
#include "../Game/Level.hpp"

#include "../Entity/Character/Character.hpp"
#include "../Entity/Actor/Actor.hpp"

namespace Entity
{
	class Player;
}

namespace Grid
{
	class Map : public BaseGrid
	{
		static Map * map;
		std::shared_ptr<Entity::Player> m_player;
		
		std::map<std::string, std::pair<Level, Level>> m_levels;
		std::map<std::string, std::pair<Level, Level>>::iterator m_currentLevel = m_levels.begin();
		std::map<std::string, sf::Vector2i> m_levelIndices;

		// std::shared_ptr<std::pair<std::string, std::pair<Level, Level>>> m_currentLevel;

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
