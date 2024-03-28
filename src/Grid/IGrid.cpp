#include "IGrid.hpp"

#include <iostream>

namespace Grid
{
	IGrid::IGrid(sf::RenderWindow &window,
				 EGridType gridType,
				 const sf::Vector2u &topLeft,
				 const sf::Vector2u &bottomRight,
				 unsigned linesOffset)
		: m_window(window)
		, m_topLeft(topLeft)
		, m_bottomRight(bottomRight)
		, m_offset(linesOffset)
		, m_size(bottomRight - topLeft)
		, m_type(gridType)
	{
		m_linesAmount = sf::Vector2u(m_size.y/m_offset,  // horizontal lines
									 m_size.x/m_offset); // vertical lines 
	}

	IGrid::~IGrid() {}

	void IGrid::update()
	{
		// create lines
		while (m_linesAmount.x > m_horizontalLines.size())
		{
			m_horizontalLines.emplace_back(sf::VertexArray(sf::Lines, 2));
		}
		while (m_linesAmount.x < m_horizontalLines.size())
		{
			m_horizontalLines.erase(m_horizontalLines.end());
		}
		while (m_linesAmount.y > m_verticalLines.size())
		{
			m_verticalLines.emplace_back(sf::VertexArray(sf::Lines, 2));
		}
		while (m_linesAmount.y < m_verticalLines.size())
		{
			m_verticalLines.erase(m_verticalLines.end());
		}

		for (unsigned i = 0; i < m_linesAmount.x; ++i)
		{
			m_horizontalLines[i][0].position = sf::Vector2f(m_topLeft.x, m_topLeft.y+(i+1)*m_offset);
			m_horizontalLines[i][1].position = sf::Vector2f(m_bottomRight.x, m_topLeft.y+(i+1)*m_offset);
		}
		for (unsigned i = 0; i < m_linesAmount.y; ++i)
		{
			m_verticalLines[i][0].position = sf::Vector2f(m_topLeft.x+(i+1)*m_offset, m_topLeft.y);
			m_verticalLines[i][1].position = sf::Vector2f(m_topLeft.x+(i+1)*m_offset, m_bottomRight.y);
		}
	}

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
}
