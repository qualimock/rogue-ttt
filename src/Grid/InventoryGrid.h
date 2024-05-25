#pragma once
#include "../Entity/Actor/Item.h"

#include "BaseGrid.hpp"

namespace Grid
{
	class InventoryGrid : public BaseGrid
	{
	public:
		InventoryGrid(BaseGrid&& grid);

		void AddItem(std::shared_ptr<Entity::Entity> entity);

		void RemoveItem(Entity::Item::Type type);

		int Occupied;
	};
}
