#pragma once

#include "Actor.hpp"

namespace Entity
{
	class DialogueCell : public Actor
	{
	public:
		enum class Type
		{
			Exit,
			Trade,
			Talk,
			None
		};

		DialogueCell(const sf::Vector2i &position,
				const sf::Vector2u &size,
			Type faction = Type::None);

		bool inDialogue;

		void update();

		bool SelectDialogue();

		void setSprite();

	private:
		Type m_type;
	};
}
