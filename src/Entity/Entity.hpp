#pragma once

#include <SFML/Graphics.hpp>

#include <set>

namespace Entity
{
	class Entity
	{
	public:
		Entity(const sf::Vector2i &position,
			   const sf::Vector2u &size,
			   unsigned layer);

		void setPosition(const sf::Vector2i &position);
		void setColor(sf::Color color);

		void render(sf::RenderTarget &target);

		virtual void resetColor();
		virtual void onInteract() = 0;

		bool operator==(const Entity *entity) const;

		void addTag(const std::string &tag) { m_tags.emplace(tag); }
		void removeTag(const std::string &tag);
		bool hasTag(const std::string &tag) { return m_tags.contains(tag); }

		void setIndex(const sf::Vector2i &index);

		const sf::Vector2i position() const { return m_position; }
		const sf::Vector2u size() const { return m_size; }
		const std::set<std::string> tags() const { return m_tags; }
		const sf::Vector2i index() const { return m_index; }
		const unsigned layer() const { return m_layer; }

	private:
		sf::RectangleShape m_shape;
		std::set<std::string> m_tags;

		sf::Vector2i m_position;
		sf::Vector2u m_size;
		sf::Vector2i m_index;

		unsigned m_layer;

	protected:
		sf::Color m_color;
	};
}
