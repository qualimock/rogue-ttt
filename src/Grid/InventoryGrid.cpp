#include "InventoryGrid.h"

#include <iostream>

namespace Grid
{
	InventoryGrid::InventoryGrid(BaseGrid&& grid)
		: BaseGrid(grid) {
		Occupied = 0;
	}

	void InventoryGrid::AddItem(Entity::Entity* entity) {
		Occupied++;
		spawnEntity(adjustEntityPosition(position() + sf::Vector2i(Occupied % 3 * 40, Occupied / 3 * 40)),entity);
	}
}