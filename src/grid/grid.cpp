#include "grid.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>

namespace Grid {

	Grid::Grid(const sf::RenderWindow& window, unsigned offset)
		: m_window(window)
		, m_offset(offset)
		, victory(false, Cell::Faction::None)
		, m_sideOffset(m_offset)
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

		colorFactions();
	}

	void Grid::colorFactions() {
		for (auto& cell : m_cells) {
			switch (cell.second.faction()) {
			case Cell::Faction::Cross:
				cell.second.setFillColor(sf::Color::Red);
				break;
			case Cell::Faction::Nought:
				cell.second.setFillColor(sf::Color::Blue);
				break;
			case Cell::Faction::None:
				break;
			}

			if (cell.second.faction() == victory.second) {
				cell.second.setFillColor(sf::Color::Green);
			}
		}
	}

	bool Grid::checkCellNeighbours(const Cells::iterator& cell,
								   const Cells::iterator& first,
								   const Cells::iterator& second)
	{
		return (first != m_cells.end() && second != m_cells.end() &&
				(cell->second.isAlly(first->second) &&
				 cell->second.isAlly(second->second)));
	}

	void Grid::processEvents(const sf::Event &event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePosition((event.mouseButton.x/m_offset)*m_offset,
									   (event.mouseButton.y/m_offset)*m_offset);
			victory.first = false;
			victory.second = Cell::Faction::None;

			for (Cells::iterator it = m_cells.begin(); it != m_cells.end(); ++it) {
				if (it->second.getPosition() == mousePosition) {
					m_cells.erase(it);
					return;
				}
			}

			if (!victory.first){
				Cell::Faction faction;

				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
					faction = Cell::Faction::Cross;
					break;
				case sf::Mouse::Right:
					faction = Cell::Faction::Nought;
					break;
				default:
					break;
				}

				Cell cell(mousePosition, sf::Vector2f(m_offset, m_offset), faction);
				m_cells.emplace(std::make_pair(cell.getPosition(), cell));
			}

			for (Cells::iterator centre = m_cells.begin(); centre != m_cells.end(); ++centre) {
				if (checkCellNeighbours(centre,
										m_cells.find(centre->first + m_sideOffset.top),
										m_cells.find(centre->first + m_sideOffset.bottom)) ||
					checkCellNeighbours(centre,
										m_cells.find(centre->first + m_sideOffset.left),
										m_cells.find(centre->first + m_sideOffset.right)) ||
					checkCellNeighbours(centre,
										m_cells.find(centre->first + m_sideOffset.topRight),
										m_cells.find(centre->first + m_sideOffset.bottomLeft)) ||
					checkCellNeighbours(centre,
										m_cells.find(centre->first + m_sideOffset.topLeft),
										m_cells.find(centre->first + m_sideOffset.bottomRight)))
				{
					victory.first = true;
					victory.second = centre->second.faction();
				}

				if (victory.first) {
					for (auto& cell : m_cells) {
						if (cell.second.faction() == victory.second)
							cell.second.setFillColor(sf::Color::Green);
					}
					break;
				}
			}
		}
	}
}
