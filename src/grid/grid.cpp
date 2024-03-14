#include "grid.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

namespace Grid {

	Grid::Grid(const sf::RenderWindow& window, unsigned offset) {
		m_linesAmount.x = window.getSize().x / offset;
		m_linesAmount.y = window.getSize().y / offset;

		ImGui::LabelText(std::to_string(m_linesAmount.y).c_str(), "Horizontal");
		ImGui::LabelText(std::to_string(m_linesAmount.x).c_str(), "Vertical");

		for (unsigned i = 0; i < m_linesAmount.y; ++i) {
			m_horizontalLines.push_back(sf::VertexArray(sf::LinesStrip, 2));
		}

		for (unsigned i = 0; i < m_linesAmount.x; ++i) {
			m_verticalLines.push_back(sf::VertexArray(sf::LinesStrip, 2));
		}

		// +1 to start from offset instead of 0
		for (unsigned i = 0; i < m_linesAmount.y; ++i) {
			m_horizontalLines[i][0].position = sf::Vector2f(0, (i+1)*offset);
			m_horizontalLines[i][1].position = sf::Vector2f(window.getSize().x, (i+1)*offset);
		}

		for (unsigned i = 0; i < m_linesAmount.x; ++i) {
			m_verticalLines[i][0].position = sf::Vector2f((i+1)*offset, 0);
			m_verticalLines[i][1].position = sf::Vector2f((i+1)*offset, window.getSize().y);
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
