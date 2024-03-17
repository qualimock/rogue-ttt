#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

namespace std
{
    template <class T>
    struct hash<sf::Vector2<T>>
    {
        std::size_t operator()(const sf::Vector2<T>& v) const
        {
            using std::hash;

            // Compute individual hash values for first
            // and second. Combine them using the Boost-func

            std::size_t tmp0 = hash<T>()(v.x);
            std::size_t tmp1 = hash<T>()(v.y);

            tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
			return tmp0;
         }
    };
}

namespace Grid {
	typedef std::vector<sf::VertexArray> Lines;
	typedef std::unordered_map<sf::Vector2f, sf::RectangleShape> Cells;

	class Grid {
		const sf::RenderWindow &m_window;

		unsigned m_offset;

		sf::Vector2u m_linesAmount;

		std::pair<Lines, Lines> m_grid;

		Cells m_cells;

		struct SideOffset {
			SideOffset(int offset)
				: topLeft(-offset, -offset)
				, top(0, -offset)
				, topRight(offset, -offset)
				, right(offset, 0)
				, bottomRight(offset, offset)
				, bottom(0, offset)
				, bottomLeft(-offset, offset)
				, left(-offset, 0) {}

			sf::Vector2f topLeft;
			sf::Vector2f top;
			sf::Vector2f topRight;
			sf::Vector2f right;
			sf::Vector2f bottomRight;
			sf::Vector2f bottom;
			sf::Vector2f bottomLeft;
			sf::Vector2f left;
		};

		SideOffset m_sideOffset;

	public:
		Grid(const sf::RenderWindow&, unsigned = 40);
		~Grid() = default;

		void update();

		void processEvents(const sf::Event &event);

		Cells cells() { return m_cells; }
		std::pair<Lines, Lines> grid() { return m_grid; }
		Lines horizontal() { return m_grid.first; }
		Lines vertical() { return  m_grid.second; }
	};
}
