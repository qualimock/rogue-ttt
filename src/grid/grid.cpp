#include "grid.hpp"

namespace Grid {

	Grid::Grid(const sf::RenderWindow& window, unsigned offset) {

		m_horizontalAmount = window.getSize().y / offset;
		m_verticalAmount = window.getSize().x / offset;

		for (unsigned i = 0; i < m_horizontalAmount; ++i) {
			m_horizontalLines.push_back(sf::VertexArray(sf::LinesStrip, 2));
		}

		for (unsigned i = 0; i < m_verticalAmount; ++i) {
			m_verticalLines.push_back(sf::VertexArray(sf::LinesStrip, 2));
		}

		for (unsigned i = 1; i < m_horizontalAmount; ++i) {
			m_horizontalLines[i][0].position = sf::Vector2f(0, i*offset);
			m_horizontalLines[i][1].position = sf::Vector2f(window.getSize().x, i*offset);
		}

		for (unsigned i = 1; i < m_verticalAmount; ++i) {
			m_verticalLines[i][0].position = sf::Vector2f(i*offset, 0);
			m_verticalLines[i][1].position = sf::Vector2f(i*offset, window.getSize().y);
		}
	}

	Lines Grid::grid() {
		Lines lines;
		for (auto &line : m_verticalLines) {
			lines.push_back(std::move(line));
		}
		for (auto &line : m_horizontalLines) {
			lines.push_back(std::move(line));
		}

		return lines;
	}

}
