#pragma once

#include <SFML/Graphics.hpp>

#include <set>

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

		Cell(const sf::Vector2f& position,
			 const sf::Vector2f& size,
			 Faction faction = None);
		~Cell() = default;

		bool isAlly(const Cell& cell);

		const Faction faction() const { return m_faction; }

		void addTag(const std::string &tag) { m_tags.emplace(tag); }
		bool hasTag(const std::string &tag) { return m_tags.contains(tag); }

		void draw(sf::RenderWindow &window);

	private:
		std::set<std::string> m_tags;

		Faction m_faction;

		sf::Color m_color;
	};
}
