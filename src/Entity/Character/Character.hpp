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

		void interact(Entity *target);

		void onInteract() override;

		const EType type() const { return m_type; }

	private:
		EType m_type;

		void init();
	};
}
