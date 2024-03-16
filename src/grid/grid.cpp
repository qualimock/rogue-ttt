#include "grid.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>

namespace Grid {

	Grid::Grid(const sf::RenderWindow& window, unsigned offset)
		: m_window(window)
		, m_offset(offset)
	{}

	void Grid::update() {
		m_linesAmount = sf::Vector2u(m_window.getSize().x/m_offset,
									 m_window.getSize().y/m_offset);

		while (m_linesAmount.y > m_grid.first.size()) {
			m_grid.first.emplace_back(sf::VertexArray(sf::LinesStrip, 2));
		}
		while (m_linesAmount.y < m_grid.first.size()) {
			m_grid.first.erase(m_grid.first.end());
		}
		while (m_linesAmount.x > m_grid.second.size()) {
			m_grid.second.emplace_back(sf::VertexArray(sf::LinesStrip, 2));
		}
		while (m_linesAmount.x < m_grid.second.size()) {
			m_grid.second.erase(m_grid.second.end());
		}

		// +1 to start from offset instead of 0
		for (unsigned i = 0; i < m_linesAmount.y; ++i) {
			m_grid.first[i][0].position = sf::Vector2f(0, (i+1)*m_offset);
			m_grid.first[i][1].position = sf::Vector2f(m_window.getSize().x, (i+1)*m_offset);
		}

		for (unsigned i = 0; i < m_linesAmount.x; ++i) {
			m_grid.second[i][0].position = sf::Vector2f((i+1)*m_offset, 0);
			m_grid.second[i][1].position = sf::Vector2f((i+1)*m_offset, m_window.getSize().y);
		}
	}

	void Grid::processEvents(const sf::Event &event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePosition((event.mouseButton.x/m_offset)*m_offset,
									   (event.mouseButton.y/m_offset)*m_offset);

			for (Cells::iterator it = m_cells.begin(); it != m_cells.end(); ++it) {
				if (it->getPosition() == mousePosition) {
					m_cells.erase(it);
					return;
				}
			}

			sf::RectangleShape shape(sf::Vector2f(m_offset, m_offset));
			shape.setFillColor(sf::Color::Red);
			shape.move(mousePosition);
			m_cells.emplace_back(shape);
		}
	}
}
