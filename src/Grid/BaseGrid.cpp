#include "BaseGrid.hpp"

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
	}

	void BaseGrid::resize(const sf::Vector2i &point)
	{
		m_bottomRight = point;
		m_size = sf::Vector2u(m_bottomRight - m_topLeft);
		m_linesAmount = sf::Vector2u(m_size.y/m_offset,  // horizontal lines
									 m_size.x/m_offset); // vertical lines
	}
}
