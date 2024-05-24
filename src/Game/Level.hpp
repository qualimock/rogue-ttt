#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>

namespace Entity
{
	class Entity;
}

class Level
{
	sf::Vector2i m_size;
	sf::Vector2u m_cellSize;
	std::vector<std::shared_ptr<Entity::Entity>> m_levelEntities;

public:
	Level(const std::vector<std::string> &levelDescription);

	const std::vector<std::shared_ptr<Entity::Entity>> &entities() const;
	const sf::Vector2i size() const { return m_size; }
};
