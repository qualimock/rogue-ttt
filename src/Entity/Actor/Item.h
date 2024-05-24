#pragma once

#include "Actor.hpp"

namespace Entity
{
	class Item: public Actor
	{
	public:
		Item(Actor&& actor);

		void onInteract() override;
	};
}
