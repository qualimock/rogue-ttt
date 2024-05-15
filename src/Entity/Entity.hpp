#pragma once

#include <SFML/Graphics.hpp>

#include <set>

namespace Entity
{
	class Entity : public sf::RectangleShape
	{
	public:
		Entity(const sf::Vector2i &position,
			   const sf::Vector2u &size);

		void render(sf::RenderTarget &target);

		virtual void resetColor();

		void addTag(const std::string &tag) { m_tags.emplace(tag); }
		bool hasTag(const std::string &tag) { return m_tags.contains(tag); }

	private:		
		std::set<std::string> m_tags;

		sf::Vector2i m_pos;
		sf::Vector2i m_size;


	protected:
		sf::Color m_color;
	};
}
