#include "WoodenFloor.hpp"

#include <iostream>

namespace Entity
{
	WoodenFloor::WoodenFloor(Actor &&actor)
		: Actor(actor)
	{
		removeTag("solid");
		setColor(sf::Color::Yellow);
	}
}
