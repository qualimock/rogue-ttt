#include "Wall.hpp"

#include <iostream>

namespace Entity
{
	Wall::Wall(Actor &&actor)
		: Actor(actor)
	{
		setColor(sf::Color::Magenta);
	}

	void Wall::onInteract()
	{
		std::cout << "Just wall" << std::endl;
	}
}
