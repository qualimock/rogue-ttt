#include "Floor.hpp"

#include <iostream>

namespace Entity
{
	Floor::Floor(Actor &&actor)
		: Actor(actor)
	{
		removeTag("solid");
		setColor(sf::Color::Yellow);
	}
}
