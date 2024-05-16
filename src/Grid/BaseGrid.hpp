#pragma once

#include "IGrid.hpp"

#include <unordered_map>

#include "../Entity/Actor/Actor.hpp"


namespace std
{
	template <class T>
    struct hash<sf::Vector2<T>>
    {
        std::size_t operator()(const sf::Vector2<T>& v) const
        {
            using std::hash;

            std::size_t tmp0 = hash<T>()(v.x);
            std::size_t tmp1 = hash<T>()(v.y);

            tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
			return tmp0;
         }
    };
}


namespace Grid
{
	class BaseGrid : public IGrid
	{
		unsigned m_layer;
		std::string m_name;

	public:
		BaseGrid(const std::string &name,
				 EGridType eGridType,
				 const sf::Vector2i &topLeft,
				 const sf::Vector2i &bottomRight,
				 unsigned layer = 0,
				 unsigned linesOffset = 40);

		std::unordered_map<sf::Vector2i, Entity::Entity *> m_entities;
		void move(const sf::Vector2i &position) override;
		void resize(const sf::Vector2i &point) override;

		virtual bool clicked(sf::Mouse::Button button,
							 const sf::Vector2i &mousePosition);

		void renderCells(sf::RenderTarget &target);

		void clear();

		void destroyEntity(Entity::Entity *entity);

		const std::string name() const { return m_name; }
		const unsigned layer() const { return m_layer; }

	protected:
		std::pair<sf::Vector2i, sf::Vector2i>
		adjustEntityPosition(const sf::Vector2i &position) const;

		void spawnEntity(std::pair<sf::Vector2i, sf::Vector2i> IndexPosition,
						 Entity::Entity *entity);
		void destroyEntity(const sf::Vector2i &index);
	};
}
