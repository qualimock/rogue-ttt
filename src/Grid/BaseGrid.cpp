#include "BaseGrid.hpp"

namespace Grid
{
	BaseGrid::BaseGrid(sf::RenderWindow &window,
					   EGridType eGridType,
					   const std::string &name,
					   const sf::Vector2i &topLeft,
					   const sf::Vector2i &bottomRight,
					   unsigned linesOffset)
		: IGrid(window, eGridType, topLeft, bottomRight, linesOffset)
		, m_name(name)
	{}

	void BaseGrid::processEvent(sf::Event &event)
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
