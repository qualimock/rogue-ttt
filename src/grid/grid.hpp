#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Grid {
	typedef std::vector<sf::VertexArray> Lines;

	class Grid {
		sf::Vector2u m_linesAmount;
		sf::Vector2u m_cellsAmount;

		Lines m_horizontalLines;
		Lines m_verticalLines;
		std::pair<Lines, Lines> m_grid;


	public:
		Grid(const sf::RenderWindow&, unsigned = 40);
		~Grid() = default;

		Lines grid();
		Lines horizontal() { return m_horizontalLines; }
		Lines vertical() { return  m_verticalLines; }
	};
}
