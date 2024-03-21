#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Grid/Grid.hpp"

class Game {
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;

	Grid::Grid m_grid;

	struct {
		bool mouseHover = false;
	} ImGuiFlags;

public:
	Game(const sf::VideoMode& videoMode);
	~Game();

	void processImgui();

	void render();
	void update();
	bool init();

	const sf::RenderWindow *window() const { return &m_window; }
};
