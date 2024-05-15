#pragma once

#include <SFML/Graphics.hpp>

#include <set>

namespace Grid 
{
	class Entity
	{
		private:
			std::set<std::string> m_tags;

			sf::Vector2i m_pos;
			sf::Vector2i m_size;
		public:
			virtual void draw(sf::RenderWindow &window) = 0;

			void addTag(const std::string &tag) { m_tags.emplace(tag); }
			bool hasTag(const std::string &tag) { return m_tags.contains(tag); }
	};
}
