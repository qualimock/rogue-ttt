#pragma once

#include "Actor.hpp"

namespace Entity
{
	class Floor : public Actor
	{
	public:
		Floor(Actor &&actor);

		void onInteract() override {}
	};
}
