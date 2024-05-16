#include "BaseGrid.hpp"

#include <iostream>
#include <cmath>

namespace Grid
{
	BaseGrid::BaseGrid(const std::string &name,
					   EGridType eGridType,
					   const sf::Vector2i &topLeft,
					   const sf::Vector2i &bottomRight,
					   unsigned layer,
					   unsigned linesOffset)
		: IGrid(eGridType, topLeft, bottomRight, linesOffset)
		, m_name(name)
		, m_layer(layer)
	{}

	void BaseGrid::move(const sf::Vector2i &position)
	{
		m_topLeft = position;
		m_bottomRight = position + sf::Vector2i(m_size);

		for (auto &entity : m_entities)
		{
			entity.second->setPosition(m_topLeft + sf::Vector2i(m_offset * entity.first.x, m_offset * entity.first.y));
		}
	}

	void BaseGrid::resize(const sf::Vector2i &point)
	{
		m_bottomRight = point;
		m_size = sf::Vector2u(m_bottomRight - m_topLeft);
		m_linesAmount = sf::Vector2u(m_size.y/m_offset,  // horizontal lines
									 m_size.x/m_offset); // vertical lines
		m_cellsAmount = sf::Vector2u(m_linesAmount.y-1, m_linesAmount.x-1);

	}

	std::pair<sf::Vector2i, sf::Vector2i> BaseGrid::adjustEntityPosition(const sf::Vector2i &position) const
	{
		sf::Vector2i entityIndex; // entity index in grid
		sf::Vector2i entityPosition; // entity position in window
		sf::Vector2i relativePosition; // position relative to the grid
					
		relativePosition.x = position.x - m_topLeft.x;
		relativePosition.y = position.y - m_topLeft.y;

		entityIndex.x = relativePosition.x / ( m_offset + 1 ) - 1;
		entityIndex.y = relativePosition.y / ( m_offset + 1 ) - 1;

		// vertical line click
		if ( (m_size.x - 1) % position.x == 0 )
		{
			// crossing lines click
			if ( (m_size.y - 1) % position.y == 0 )
			{
				if ( m_entities.contains(entityIndex) || entityIndex.x < 0 || entityIndex.x > (m_size.x - 1) % m_offset )
				{
					entityIndex.x++;
				}
					
				if ( m_entities.contains(entityIndex) || entityIndex.y < 0 || entityIndex.y > (m_size.y - 1) % m_offset )
				{
					entityIndex.y++;
				}
			}

			entityIndex.y++;

			if ( m_entities.contains(entityIndex) || entityIndex.x < 0 || entityIndex.x > (m_size.x - 1) % m_offset )
			{
				entityIndex.x++;
			}

		}
		// horizontal line click
		else if ( (m_size.y - 1) % position.y == 0 )
		{
			entityIndex.x++;

			if ( m_entities.contains(entityIndex) || entityIndex.y < 0 || entityIndex.y > (m_size.y - 1) % m_offset )
			{
				entityIndex.y++;
			}

		}
		// entity click
		else
		{
			entityIndex.x++;
			entityIndex.y++;
		}

		entityPosition.x = entityIndex.x * ( m_offset ) - relativePosition.x + position.x;
		entityPosition.y = entityIndex.y * ( m_offset ) - relativePosition.y + position.y;

		return std::make_pair(entityIndex, entityPosition);
	}

	bool BaseGrid::clicked(sf::Mouse::Button button, const sf::Vector2i &mousePosition)
	{
		return false;
	}

	void BaseGrid::spawnEntity(std::pair<sf::Vector2i, sf::Vector2i> IndexPosition,
							   Entity::Entity *entity)
	{
		if (m_entities.find(IndexPosition.first) == m_entities.end())
		{
			entity->setPosition(IndexPosition.second);
			m_entities.emplace
			(
				IndexPosition.first,
				entity
			);

			std::cout << "SPAWNED" << std::endl;
			std::cout << IndexPosition.first.x << ":" << IndexPosition.first.y << std::endl;
		}
	}

	void BaseGrid::destroyEntity(const sf::Vector2i &index)
	{
		if (m_entities.find(index) != m_entities.end())
		{
			m_entities.erase(index);
		}
	}

	void BaseGrid::renderCells(sf::RenderTarget &target)
	{
		for(auto &cell : m_entities){
			cell.second->render(target);
		}
	}

	void BaseGrid::clear()
	{
		m_entities.clear();
	}
}
