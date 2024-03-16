#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../grid/grid.hpp"

class Game {
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;

	Grid::Grid m_grid;

public:
	Game(const sf::VideoMode& videoMode);
	~Game();

	void render();
	void update();
	bool init();

	const sf::RenderWindow *window() const { return &m_window; }
};
