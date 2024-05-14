#pragma once

#include "IGrid.hpp"

#include <unordered_map>

#include "Cell/Cell.hpp"

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
	public:
		BaseGrid(sf::RenderWindow &window,
				 EGridType eGridType,
				 const std::string &name,
				 const sf::Vector2i &topLeft,
				 const sf::Vector2i &bottomRight,
				 unsigned linesOffset = 40);

		void processEvent(sf::Event &event) override;

		void move(const sf::Vector2i &position) override;
		void resize(const sf::Vector2i &point) override;

		void setBorder(const IGrid &grid);
		void setBorder(sf::RenderWindow &window);

		void drawCells(sf::RenderWindow &window);

		const std::string name() const { return m_name; }
		//const std::unordered_map<sf::Vector2i, Cell>& getCells() const { return m_cells; };

	protected:
		std::string m_name;
	private:
		std::unordered_map<sf::Vector2i, Cell> m_cells;
	};
}
