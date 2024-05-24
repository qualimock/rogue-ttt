#pragma once

#pragma once

#include "BaseGrid.hpp"

namespace Grid
{
	class InventoryGrid : public BaseGrid
	{
	public:
		InventoryGrid(BaseGrid&& grid);

		void AddItem(std::shared_ptr<Entity::Entity> entity);

		int Occupied;
	};
}
