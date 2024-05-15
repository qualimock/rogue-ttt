#pragma once

#include <SFML/Graphics.hpp>

#include <set>

namespace Entity
{
	class Entity
	{
	public:
		Entity(const sf::Vector2i &position,
			   const sf::Vector2u &size);

		void setPosition(const sf::Vector2i &position);
		void setColor(sf::Color color);

		void render(sf::RenderTarget &target);

		virtual void resetColor();

		void addTag(const std::string &tag) { m_tags.emplace(tag); }
		bool hasTag(const std::string &tag) { return m_tags.contains(tag); }

		const sf::Vector2i position() const { return m_position; }
		const sf::Vector2u size() const { return m_size; }

	private:
		sf::RectangleShape m_shape;
		std::set<std::string> m_tags;

		sf::Vector2i m_position;
		sf::Vector2u m_size;

	protected:
		sf::Color m_color;
	};
}
