#pragma once

#include "Character.hpp"

namespace Entity
{
	class Player : public Character
	{
	public:
		Player(Character &&character);

		void onInteract() override {};
	};
}
