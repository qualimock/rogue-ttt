#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Grid {
	typedef std::vector<sf::VertexArray> Lines;
	typedef std::vector<sf::RectangleShape> Cells;

	class Grid {
		const sf::RenderWindow &m_window;

		unsigned m_offset;

		sf::Vector2u m_linesAmount;

		std::pair<Lines, Lines> m_grid;

		Cells m_cells;

	public:
		Grid(const sf::RenderWindow&, unsigned = 40);
		~Grid() = default;

		void update();

		void processEvents(const sf::Event &event);

		Cells cells() { return m_cells; }
		std::pair<Lines, Lines> grid() { return m_grid; }
		Lines horizontal() { return m_grid.first; }
		Lines vertical() { return  m_grid.second; }
	};
}
