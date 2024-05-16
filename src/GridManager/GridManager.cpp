#include "GridManager.hpp"

#include <SFML/Window/Event.hpp>

#include "../Grid/BaseGrid.hpp"
#include "../Grid/CombatGrid.hpp"
#include "../Grid/Map.hpp"

#include <iostream>

namespace Grid
{
	bool GridManager::mouseClicked(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid)
	{
		std::cout << "MOUSE" << std::endl << std::endl;

		switch (grid->type())
		{
		case BaseGrid::EGridType::Combat:
			CombatGrid *p_grid = dynamic_cast<CombatGrid *>(grid);
			if (p_grid)
			{
				return p_grid->clicked(event.mouseButton.button, sf::Mouse::getPosition(window));
			}
			break;
		}
		return false;
	}

	bool GridManager::moveEvent(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid)
	{
		std::cout << "KEYBOARD" << std::endl << std::endl;

		sf::Vector2i movement;

		switch(event.key.code)
		{
		case sf::Keyboard::W:
			movement = sf::Vector2i(0, -1);
			break;

		case sf::Keyboard::A:
			movement = sf::Vector2i(-1, 0);
			break;

		case sf::Keyboard::S:
			movement = sf::Vector2i(0, 1);
			break;

		case sf::Keyboard::D:
			movement = sf::Vector2i(1, 0);
			break;
		}

		return dynamic_cast<Grid::Map *>(grid)->movePlayer(movement);
	}
}
