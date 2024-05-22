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
			WoodenFloor,
			None
		};

		void onInteract() override;

		Actor(const sf::Vector2i &position,
			  const sf::Vector2u &size,
			  unsigned layer,
			  EType type);
		Actor(const Entity &entity, EType type);
		Actor(Entity &&entity, EType type);

		const EType type() const { return m_type; }

	private:
		EType m_type;

		void init();
	};
}
