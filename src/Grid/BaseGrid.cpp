#include "BaseGrid.hpp"

namespace Grid
{
	BaseGrid::BaseGrid(sf::RenderWindow &window,
					   EGridType eGridType,
					   const std::string &name,
					   const sf::Vector2u &topLeft,
					   const sf::Vector2u &bottomRight,
					   unsigned linesOffset)
		: IGrid(window, eGridType, topLeft, bottomRight, linesOffset)
		, m_name(name)
	{}

	void BaseGrid::move(const sf::Vector2u &position)
	{
		m_topLeft = position;
		m_bottomRight = position + m_size;
	}

	void BaseGrid::resize(const sf::Vector2u &point)
	{
		m_bottomRight = point;
		m_size = m_bottomRight - m_topLeft;
		m_linesAmount = sf::Vector2u(m_size.y/m_offset,  // horizontal lines
									 m_size.x/m_offset); // vertical lines
	}
}
