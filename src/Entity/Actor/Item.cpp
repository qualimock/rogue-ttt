#include "Item.h"

namespace Entity
{
	Item::Item(Actor&& actor)
		: Actor(actor)
	{
		setColor(sf::Color::Red);
		ItemType = Type::Type1;
	}

	void Item::onInteract()
	{
		removeTag("solid");
	}
}
