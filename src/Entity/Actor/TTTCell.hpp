#pragma once

#include "Actor.hpp"

namespace Entity
{
	class TTTCell : public Actor
	{
	public:
		enum class Faction
		{
			Cross,
			Nought,

			None
		};

		TTTCell(const sf::Vector2i &position,
				const sf::Vector2u &size,
				Faction faction = Faction::None);

		bool isAlly(const TTTCell &tttCell);

		void resetColor() override;

		const Faction faction() const { return m_faction; }

	private:
		Faction m_faction;
	};
}
