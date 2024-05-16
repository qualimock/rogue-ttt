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
		std::cout << "MOUSE" << std::endl;		

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

	Entity::Entity * GridManager::moveEvent(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid)
	{
		std::cout << "KEYBOARD" << std::endl;

		sf::Vector2i movement;

		switch(event.key.code)
		{
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			movement = sf::Vector2i(0, -1);
			break;

		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			movement = sf::Vector2i(-1, 0);
			break;

		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			movement = sf::Vector2i(0, 1);
			break;

		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			movement = sf::Vector2i(1, 0);
			break;
		}

		return dynamic_cast<Grid::Map *>(grid)->movePlayer(movement);
	}
}
