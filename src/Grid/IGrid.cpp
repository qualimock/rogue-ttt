#include "IGrid.hpp"

#include <iostream>

namespace Grid
{
	IGrid::IGrid(sf::RenderWindow &window,
				 EGridType gridType,
				 const sf::Vector2u &topLeft,
				 const sf::Vector2u &bottomRight,
				 const std::string &name,
				 unsigned linesOffset)
		: m_window(window)
		, m_topLeft(topLeft)
		, m_bottomRight(bottomRight)
		, m_name(name)
		, m_offset(linesOffset)
		, m_size(bottomRight - topLeft)
	{}

	IGrid::~IGrid() {}

	void IGrid::draw()
	{
		for (auto &line : m_horizontalLines)
		{
			m_window.draw(line);
		}
		for (auto &line : m_verticalLines)
		{
			m_window.draw(line);
		}
	}

	void IGrid::move(const sf::Vector2u &position)
	{
		m_topLeft = position;
		m_bottomRight = position + m_size;
	}
}
