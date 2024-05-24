#include "BaseGrid.hpp"

#include <iostream>
#include <cmath>

namespace Grid
{
	BaseGrid::BaseGrid(EGridType eGridType,
					   const sf::Vector2i &topLeft,
					   const sf::Vector2i &bottomRight,
					   unsigned layer,
					   unsigned linesOffset)
		: IGrid(eGridType, topLeft, bottomRight, linesOffset)
		, m_layer(layer)
		, m_cellLayers(0)
	{}

	BaseGrid::BaseGrid(EGridType eGridType,
					   const sf::Vector2u &size,
					   unsigned layer,
					   unsigned linesOffset)
		: IGrid(eGridType, sf::Vector2i(0, 0), sf::Vector2i(size), linesOffset)
		, m_layer(layer)
		, m_cellLayers(0)
	{}

	BaseGrid::BaseGrid(EGridType eGridType,
					   const sf::Vector2i &position,
					   const sf::Vector2u &size,
					   unsigned layer,
					   unsigned linesOffset)
		: IGrid(eGridType, position, position+sf::Vector2i(size), linesOffset)
		, m_layer(layer)
		, m_cellLayers(0)
	{}

	void BaseGrid::move(const sf::Vector2i &position)
	{
		m_topLeft = position;
		m_bottomRight = position + sf::Vector2i(m_size);

		for (auto &entity : m_entities)
		{
			entity.second->setPosition(m_topLeft + sf::Vector2i(m_offset * entity.second->index().x,
																m_offset * entity.second->index().y));
		}
	}

	void BaseGrid::resize(const sf::Vector2i &point)
	{
		m_bottomRight = point;
		m_size = sf::Vector2u(m_bottomRight - m_topLeft);

		update();
	}

	std::pair<sf::Vector2i, sf::Vector2i> BaseGrid::adjustEntityPosition(const sf::Vector2i &position) const
	{
		sf::Vector2i entityIndex; // entity index in grid
		sf::Vector2i entityPosition; // entity position in window
		sf::Vector2i relativePosition; // position relative to the grid

		relativePosition.x = position.x - m_topLeft.x;
		relativePosition.y = position.y - m_topLeft.y;

		entityIndex.x = relativePosition.x / m_offset + 1 - 1;
		entityIndex.y = relativePosition.y / m_offset + 1 - 1;

		// vertical line click
		// if ( position.x != 0 && position.y != 0 )
		// {
			// if ( (m_size.x - 1) % position.x == 0 )
			// {
			// 	// crossing lines click
			// 	if ( (m_size.y - 1) % position.y == 0 )
			// 	{
			// 		for (auto &entity : m_entities)
			// 		{
			// 			if ( entity.second->index() == entityIndex || entityIndex.x < 0 || entityIndex.x > (m_size.x - 1) % m_offset )
			// 			{
			// 				entityIndex.x++;
			// 			}

			// 			if ( entity.second->index() == entityIndex || entityIndex.y < 0 || entityIndex.y > (m_size.y - 1) % m_offset )
			// 			{
			// 				entityIndex.y++;
			// 			}
			// 		}
			// 	}

			// 	entityIndex.y++;

			// 	for (auto &entity : m_entities)
			// 	{
			// 		if ( entity.second->index() == entityIndex || entityIndex.x < 0 || entityIndex.x > (m_size.x - 1) % m_offset )
			// 		{
			// 			entityIndex.x++;
			// 		}
			// 	}
			// }
			// // horizontal line click
			// else if ( (m_size.y - 1) % position.y == 0 )
			// {
			// 	entityIndex.x++;

			// 	for (auto &entity : m_entities)
			// 	{
			// 		if ( entity.second->index() == entityIndex || entityIndex.y < 0 || entityIndex.y > (m_size.y - 1) % m_offset )
			// 		{
			// 			entityIndex.y++;
			// 		}
			// 	}
			// }
			// // entity click
			// else
			// {
			// 	entityIndex.x++;
			// 	entityIndex.y++;
			// }
		// }

		entityPosition.x = entityIndex.x * ( m_offset ) - relativePosition.x + position.x;
		entityPosition.y = entityIndex.y * ( m_offset ) - relativePosition.y + position.y;

		return std::make_pair(entityIndex, entityPosition);
	}

	bool BaseGrid::clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition)
	{
		return false;
	}

	void BaseGrid::spawnEntity(const sf::Vector2i &position, std::shared_ptr<Entity::Entity> entity)
	{
		if (!entity)
		{
			std::cerr << "CANNOT SPAWN NULLPTR" << std::endl;
			return;
		}

		unsigned repeats = 0;

		for (auto &cell : m_entities)
		{
			if (m_entities.find(entity->name() + std::to_string(repeats)) != m_entities.end())
			{
				repeats++;
			}
		}

		auto IndexPosition = adjustEntityPosition(position);

		entity->setPosition(IndexPosition.second);
		entity->setIndex(IndexPosition.first);
			
		entity->addTag(entity->name());

		m_entities.emplace(entity->name() + std::to_string(repeats), entity);

		std::cout << "SPAWNED" << std::endl;
		std::cout << IndexPosition.first.x << ":" << IndexPosition.first.y << std::endl;
	}

	void BaseGrid::destroyEntity(const std::string &index)
	{
		if (m_entities.find(index) != m_entities.end())
		{
			m_entities.erase(index);
		}
	}

	void BaseGrid::destroyEntity(std::shared_ptr<Entity::Entity> entity)
	{
		for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			if (it->second == entity)
			{
				m_entities.erase(it);
				return;
			}
		}
	}

	void BaseGrid::update()
	{
		IGrid::update();

		for (auto &entity : m_entities)
		{
			if (entity.second->layer() > m_cellLayers)
			{
				m_cellLayers = entity.second->layer();
			}
		}
	}

	void BaseGrid::renderCells(sf::RenderTarget &target)
	{
		for (unsigned i = 0; i < m_cellLayers+1; ++i)
		{
			for(auto &entity : m_entities)
			{
				if (entity.second->layer() == i)
				{
					entity.second->render(target);
				}
			}
		}
	}

	void BaseGrid::clear()
	{
		m_entities.clear();
	}
}
