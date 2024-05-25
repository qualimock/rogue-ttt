#include "InventoryGrid.h"

#include <iostream>

namespace Grid
{
	InventoryGrid::InventoryGrid(BaseGrid&& grid)
		: BaseGrid(grid) {
		Occupied = 0;
	}

	void InventoryGrid::AddItem(std::shared_ptr<Entity::Entity> entity) {
		spawnEntity(adjustEntityPosition(position() + sf::Vector2i(Occupied % 3 * 40, Occupied / 3 * 40)).second, entity);
		Occupied++;
	}

	void InventoryGrid::RemoveItem(Entity::Item::Type type) {
		for (auto& entity : m_entities)
		{
			if (dynamic_cast<Entity::Item*>(entity.second.get())->ItemType == type)
			{
				destroyEntity(entity.second);
				break;
			}
		}
	}
}
