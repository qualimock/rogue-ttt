#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <map>
#include <vector>
#include <memory>
#include <string>

#include "../Grid/BaseGrid.hpp"

class Game
{
	typedef std::pair<std::string, Grid::BaseGrid *> GridPair;

public:
	enum class EGameState
	{
		Exploring,
		InCombat,
		Interacting,

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

	std::map<std::string, Grid::BaseGrid *> m_grids;

	std::map<std::string, bool> m_visibleImGuiWindows;

	EGameState m_gameState;

	std::shared_ptr<Entity::Entity> m_currentlyInteractedEntity = nullptr;
	
	struct
	{
		bool mouseHover = false;
	} ImGuiFlags;

	void onMouseClick(sf::Event &event);
	void onKeyPressed(sf::Event &event);
};
