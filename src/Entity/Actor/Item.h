#pragma once

#include "Actor.hpp"

namespace Entity
{
	class Item: public Actor
	{
	public:

		enum class Type
		{
			Type1,
			Type2,
			Type3
		};

		Item(Actor&& actor);

		Item(const sf::Vector2i& position,
			const sf::Vector2u& size);

		void onInteract() override;

		Type ItemType;
	};
}
