#include "Item.h"

namespace Entity
{
	Item::Item(Actor&& actor)
		: Actor(actor)
	{
		addTag("item");
		setColor(sf::Color::Red);
	}

	void Item::onInteract()
	{
		removeTag("solid");
	}
}
