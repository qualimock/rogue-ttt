#include "GridManager.hpp"

#include <SFML/Window/Event.hpp>

#include "../Grid/BaseGrid.hpp"

#include <iostream>

namespace Grid
{
	void GridManager::processEvent(sf::Event &event, BaseGrid &grid) {}

	void GridManager::mouseClicked(sf::RenderWindow &window, sf::Event &event, BaseGrid &grid)
	{
		std::cout << "EVENT" << std::endl;
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			auto button = event.mouseButton.button;
			sf::Vector2i position = sf::Mouse::getPosition(window);
			std::cout << "MOUSE" << std::endl;

			grid.clicked(button, position);

			break;
		}

		std::cout << std::endl;
	}
}
