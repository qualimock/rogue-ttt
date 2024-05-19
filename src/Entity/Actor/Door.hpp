#pragma once

#include "Actor.hpp"

namespace Entity
{
	class Door : public Actor
	{
		bool m_opened;

	public:
		Door(Actor &&actor);

		void onInteract() override;
	};
}
