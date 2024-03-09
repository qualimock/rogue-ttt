#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Game {
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;

public:
	Game(const sf::VideoMode& videoMode);
	~Game();

	void render();
	void update();
	bool init();

	const sf::RenderWindow *window() const { return &m_window; }
};
