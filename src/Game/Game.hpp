#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

#include "../Grid/Map.hpp"

class Game
{
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;

	Grid::Map m_map;

	struct
	{
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
