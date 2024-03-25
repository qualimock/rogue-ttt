#pragma once

#include <SFML/Graphics.hpp>

namespace Grid
{
	class Cell : public sf::RectangleShape
	{
	public:
		enum Faction
		{
			Cross,
			Nought,
			None
		};

	private:
		Faction m_faction;

	public:
		Cell(const sf::Vector2f& position,
			 const sf::Vector2f& size,
			 Faction faction);
		~Cell() = default;

		bool isAlly(const Cell& cell);

		const Faction faction() const { return m_faction; }
	};
}
