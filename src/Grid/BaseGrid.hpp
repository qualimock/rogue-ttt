#pragma once

#include "IGrid.hpp"

#include <unordered_map>

#include "../Entity/Actor/Actor.hpp"

namespace Grid
{
	class BaseGrid : public IGrid
	{
		unsigned m_layer;

		unsigned m_cellLayers;

	public:
		BaseGrid(EGridType eGridType,
				 const sf::Vector2i &topLeft,
				 const sf::Vector2i &bottomRight,
				 unsigned layer = 0,
				 unsigned linesOffset = 40);

		BaseGrid(EGridType eGridType,
				 const sf::Vector2u &size,
				 unsigned layer = 0,
				 unsigned linesOffset = 40);

		BaseGrid(EGridType eGridType,
				 const sf::Vector2i &position,
				 const sf::Vector2u &size,
				 unsigned layer = 0,
				 unsigned linesOffset = 40);

		std::map<std::string, Entity::Entity *> m_entities;
		void move(const sf::Vector2i &position) override;
		void resize(const sf::Vector2i &point) override;

		virtual bool clicked(sf::Mouse::Button button,
							 const sf::Vector2i &mousePosition);

		void update() override;
		void renderCells(sf::RenderTarget &target);

		void clear();

		void destroyEntity(Entity::Entity *entity);

		const unsigned layer() const { return m_layer; }

	protected:
		std::pair<sf::Vector2i, sf::Vector2i>
		adjustEntityPosition(const sf::Vector2i &position) const;

		void spawnEntity(std::pair<sf::Vector2i, sf::Vector2i> IndexPosition,
						 Entity::Entity *entity);
		void destroyEntity(const std::string &index);
	};
}
