#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Grid {
	typedef std::vector<sf::VertexArray> Lines;

	class Grid {
		unsigned m_horizontalAmount = 0;
		unsigned m_verticalAmount = 0;

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
