#include "GridManager.hpp"

#include <SFML/Window/Event.hpp>

#include "../Grid/BaseGrid.hpp"
#include "../Grid/CombatGrid.hpp"

#include <iostream>

namespace Grid
{
	void GridManager::processEvent(sf::Event &event, BaseGrid *grid) {}

	void GridManager::mouseClicked(sf::RenderWindow &window, sf::Event &event, BaseGrid *grid)
	{
		std::cout << "EVENT" << std::endl;

		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			std::cout << "MOUSE" << std::endl;

			switch (grid->type())
			{
			case BaseGrid::EGridType::Combat:
				CombatGrid *p_grid = dynamic_cast<CombatGrid *>(grid);
				if (p_grid)
				{
					p_grid->clicked(event.mouseButton.button, sf::Mouse::getPosition(window));
				}
				break;
			}

			break;
		}

		std::cout << std::endl;
	}
}
