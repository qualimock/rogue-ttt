#pragma once

#include "Actor.hpp"

namespace Entity
{
	class Wall : public Actor
	{
	public:
		Wall(Actor &&actor);

		void onInteract() override;
	};
}
