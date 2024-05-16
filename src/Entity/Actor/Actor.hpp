#pragma once

#include "../Entity.hpp"

namespace Entity
{
	class Actor : public Entity
	{
	public:
		enum class EType
		{
			tttCell,
			Door,
			Floor,
			Item,
			Wall,

			None
		};

		Actor(const sf::Vector2i &position,
			  const sf::Vector2u &size,
			  EType type);
		Actor(const Entity &entity, EType type);
		Actor(Entity &&entity, EType type);

	private:
		EType m_type;
	};
}
