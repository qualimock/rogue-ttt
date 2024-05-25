#include "DialogueGrid.h"

#include <iostream>

namespace Grid
{
	DialogueGrid::DialogueGrid(BaseGrid&& grid)
		: BaseGrid(grid) {
		AddOption(Entity::DialogueCell::Type::Exit, 1);
		AddOption(Entity::DialogueCell::Type::Talk, 0);
	}

	bool DialogueGrid::clicked(sf::Mouse::Button button, const sf::Vector2i& mousePosition)
	{

		std::cout << "DIALOGUE" << std::endl;

		std::cout << position().x << ":" << position().y << std::endl;

		auto cellIndexPosition = adjustEntityPosition(mousePosition);

		switch (button)
		{
		case sf::Mouse::Left:
			for (auto& entity : m_entities)
			{
				if (entity.second->index() == cellIndexPosition.first)
				{
					Entity::DialogueCell* selection = dynamic_cast<Entity::DialogueCell*>(entity.second.get());
					if (selection->SelectDialogue()) {
						return true;
					}
					break;
				}
			}
		}
		return false;
	}

	void DialogueGrid::update() {
		IGrid::update();

		for (auto& entity : m_entities)
		{
			Entity::DialogueCell* cell = dynamic_cast<Entity::DialogueCell*>(entity.second.get());
			cell->update();
		}
	}

	void DialogueGrid::AddOption(Entity::DialogueCell::Type type,int index) {
		auto newCell = std::make_shared<Entity::DialogueCell>((position() + sf::Vector2i(index % 3 * 40, index / 3 * 40)),
			sf::Vector2u(m_offset, m_offset),
			type);
		spawnEntity(adjustEntityPosition(position() + sf::Vector2i(index % 3 * 40, index / 3 * 40)).second, newCell);
	}
}
