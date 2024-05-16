#pragma once

#include "../Entity.hpp"

namespace Entity
{
	class Character : public Entity
	{
	public:
		enum class EType
		{
			Player,
			NPC,
			Enemy,

			None
		};

		Character(const sf::Vector2i &position,
				  const sf::Vector2u &size,
				  EType type);
		Character(const Entity &entity, EType type);
		Character(Entity &&entity, EType type);

		void move(const sf::Vector2i &offset);

		void interact(const Entity &target);

	private:
		EType m_type;
	};
}
