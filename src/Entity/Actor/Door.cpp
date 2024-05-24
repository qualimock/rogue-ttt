#include "Door.hpp"

namespace Entity
{
	Door::Door(Actor &&actor)
		: Actor(actor)
	{
		m_opened = false;
		setColor(sf::Color::Red);
	}

	void Door::onInteract()
	{
		m_opened = !m_opened;

		if (m_opened)
		{
			setColor(sf::Color::Green);
			sf::Texture texture;
			texture.loadFromFile("res/Sprites/Actors/DoorOpen.png");
			setTexture(texture);
			removeTag("solid");
			return;
		}

		setColor(sf::Color::Red);
		addTag("solid");
	}
}
