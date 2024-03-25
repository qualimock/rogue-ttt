#include "Map.hpp"

namespace Grid
{
	Map::Map(sf::RenderWindow &window)
		: IGrid(window, EGridType::Map, sf::Vector2u(0, 0), window.getSize(), "map", 40)
	{}

	Map::~Map() {}

	void Map::update()
	{
		m_bottomRight = m_window.getSize();
		m_size = m_bottomRight - m_topLeft;
		
		// x horizontal lines
		// y vertical lines
		m_linesAmount = sf::Vector2u(m_size.y/m_offset,
									 m_size.x/m_offset);

		// create lines
		while (m_linesAmount.x > m_horizontalLines.size())
		{
			m_horizontalLines.emplace_back(sf::VertexArray(sf::LinesStrip, 2));
		}
		while (m_linesAmount.x < m_horizontalLines.size())
		{
			m_horizontalLines.erase(m_horizontalLines.end());
		}
		while (m_linesAmount.y > m_verticalLines.size())
		{
			m_verticalLines.emplace_back(sf::VertexArray(sf::LinesStrip, 2));
		}
		while (m_linesAmount.y < m_verticalLines.size())
		{
			m_verticalLines.erase(m_verticalLines.end());
		}

		for (unsigned i = 0; i < m_linesAmount.x; ++i)
		{
			m_horizontalLines[i][0].position = sf::Vector2f(m_topLeft.x, (i+1)*m_offset);
			m_horizontalLines[i][1].position = sf::Vector2f(m_bottomRight.x, (i+1)*m_offset);
		}
		for (unsigned i = 0; i < m_linesAmount.y; ++i)
		{
			m_verticalLines[i][0].position = sf::Vector2f((i+1)*m_offset, m_topLeft.y);
			m_verticalLines[i][1].position = sf::Vector2f((i+1)*m_offset, m_bottomRight.y);
		}
	}

	void Map::processEvents(sf::Event event)
	{
		
	}
}
