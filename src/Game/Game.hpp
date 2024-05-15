#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

#include "../Grid/BaseGrid.hpp"

class Game
{
public:
	enum class EGameState
	{
		Exploring,
		InCombat,

		None
	};

	Game(const sf::VideoMode& videoMode);
	~Game();

	void processImgui();

	void render();
	void update();
	bool init();

	const sf::RenderWindow *window() const { return &m_window; }

private:	
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;

	std::vector<Grid::BaseGrid *> m_grids;

	std::vector<bool> m_visibleImGuiWindows;

	EGameState m_gameState;

	struct
	{
		bool mouseHover = false;
	} ImGuiFlags;

	void onMouseClick(sf::Event &event);
	void onKeyPressed(sf::Event &event);
};
