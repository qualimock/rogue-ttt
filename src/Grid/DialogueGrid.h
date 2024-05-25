#pragma once

#include "BaseGrid.hpp"

#include "../Entity/Actor/DialogueCell.hpp"

namespace Grid
{
	class DialogueGrid : public BaseGrid
	{
	public:
		DialogueGrid(BaseGrid&& grid);

		void update() override;

		bool clicked(sf::Mouse::Button button, const sf::Vector2i& mousePosition) override;

		void AddOption(Entity::DialogueCell::Type type, int index);
	};
}
